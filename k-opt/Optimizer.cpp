#include "Optimizer.h"

void Optimizer::find_best()
{
    m_best = SearchState();
    update_grid_radii();
    for (primitives::depth_t depth{0}; depth < primitives::DepthEnd; ++depth)
    {
        const auto& map = m_depth_map.get_nodes(depth);
        if (map.size() == 0)
        {
            break;
        }
        for (const auto& hash_node_pair : map)
        {
            const auto hash = hash_node_pair.first;
            const auto node = hash_node_pair.second;
            find_best(depth, hash, node);
        }
    }
}

void Optimizer::find_best(primitives::depth_t depth, quadtree::depth_map::transform::hash_t node_hash, const quadtree::QuadtreeNode* node)
{
    const auto sr = compute_search_range(depth, node_hash);
    const auto full_nodes = full_search_nodes(sr);
    const auto partial_nodes = partial_search_nodes(sr);
    auto it = node->segments().cbegin();
    while (it != node->segments().cend())
    {
        m_current = SearchState(*it);
        find_best(node, ++it);
        for (const auto partial_node : partial_nodes)
        {
            find_best_children(partial_node);
        }
        for (const auto full_node : full_nodes)
        {
            find_best(full_node);
        }
    }
}

void Optimizer::find_best(const quadtree::QuadtreeNode* node)
{
    find_best(node, node->segments().cbegin());
}
void Optimizer::find_best(const quadtree::QuadtreeNode* node, quadtree::QuadtreeNode::SegmentContainer::const_iterator it)
{
    while (it != node->segments().cend())
    {
        if (not m_current.valid(*it))
        {
            ++it;
            continue;
        }
        m_current.push_back(*it);
        if (m_current.size() == m_k)
        {
            check_best();
            ++it;
        }
        else
        {
            find_best(node, ++it);
        }
        m_current.pop_back();
    }
    find_best_children(node);
}
void Optimizer::find_best_children(const quadtree::QuadtreeNode* node)
{
    for (const auto& unique_ptr : node->children())
    {
        if (unique_ptr)
        {
            find_best(unique_ptr.get());
        }
    }
}

Optimizer::SearchRange Optimizer::compute_search_range(primitives::depth_t depth, quadtree::depth_map::transform::hash_t center_node_hash) const
{
    // Searchable nodes meet the following criteria:
    //  1. Same depth.
    //  2. For fully searched nodes, higher node hash value.
    //  3. For partially searched nodes (only children), lower node hash values.
    //  4. Within a certain distance.
    // Assumes higher x-coordinate always gives higher node hash.
    SearchRange sr;
    sr.cx = quadtree::depth_map::transform::x(center_node_hash);
    sr.cy = quadtree::depth_map::transform::y(center_node_hash);
    sr.xmin = std::max(0, sr.cx - m_xradius[depth] - 1);
    sr.ymin = std::max(0, sr.cy - m_yradius[depth] - 1);
    primitives::grid_t grid_dim = 1 << depth;
    sr.xend = std::min(grid_dim, sr.cx + m_xradius[depth] + 1);
    sr.yend = std::min(grid_dim, sr.cy + m_yradius[depth] + 1);
    return sr;
}

std::vector<quadtree::QuadtreeNode*> Optimizer::partial_search_nodes(const SearchRange& sr) const
{
    std::vector<quadtree::QuadtreeNode*> nodes;
    for (int x{sr.xmin}; x < sr.cx; ++x)
    {
        for (int y{sr.ymin}; y < sr.yend; ++y)
        {
            find_and_add_node(sr.depth, x, y, nodes);
        }
    }
    for (int y{sr.ymin}; y < sr.cy; ++y)
    {
        find_and_add_node(sr.depth, sr.cx, y, nodes);
    }
    return nodes;
}
std::vector<quadtree::QuadtreeNode*> Optimizer::full_search_nodes(const SearchRange& sr) const
{
    std::vector<quadtree::QuadtreeNode*> nodes;
    for (int y{sr.cy + 1}; y < sr.yend; ++y)
    {
        find_and_add_node(sr.depth, sr.cx, y, nodes);
    }
    for (int x{sr.cx + 1}; x < sr.xend; ++x)
    {
        for (int y{sr.ymin}; y < sr.yend; ++y)
        {
            find_and_add_node(sr.depth, x, y, nodes);
        }
    }
    return nodes;
}
void Optimizer::find_and_add_node(primitives::depth_t depth
    , primitives::grid_t grid_x, primitives::grid_t grid_y
    , std::vector<quadtree::QuadtreeNode*>& nodes) const
{
    auto hash = quadtree::depth_map::transform::hash_grid_coord(grid_x, grid_y);
    const auto it = m_depth_map.get_nodes(depth).find(hash);
    if (it != m_depth_map.get_nodes(depth).end())
    {
        nodes.push_back(it->second);
    }
}

void Optimizer::check_best()
{
    // TODO: implement for m_k > 2.
    // TODO: logarithmic distance table.
    const auto& s = m_current.segments;
    auto& ns = m_current.new_segments;
    ns.clear();
    ns.push_back({s[0].a, s[1].a, m_dt.compute_length(s[0].a, s[1].a)});
    if (ns[0].length >= m_current.length)
    {
        return;
    }
    ns.push_back({s[0].b, s[1].b, m_dt.compute_length(s[0].b, s[1].b)});
    auto new_length = ns[0].length + ns[1].length;
    if (new_length >= m_current.length)
    {
        return;
    }
    m_current.improvement = m_current.length - new_length;
    // Using >= or > below can make a difference in results!
    // It is possible to get multiple swap configurations with the same improvement.
    // All are qualitatively equivalent choices, but still can lead to divergence in later results.
    // The configuration chosen depends on the search path.
    // If >, the first configuration will be kept.
    // If >=, the last configuration will be chosen.
    if (m_current.improvement >= m_best.improvement)
    {
        m_best = m_current;
    }
}

void Optimizer::iterate()
{
    int segments{0};
    uint64_t length{0};
    for (int i{0}; i < primitives::MaxTreeDepth; ++i)
    {
        const auto& map = m_depth_map.get_nodes(i);
        std::cout << "depth " << i << " nodes: " << map.size() << std::endl;
        for (const auto& pair : map)
        {
            const auto node = pair.second;
            segments += node->segments().size();
            for (const auto& s : node->segments())
            {
                length += s.length;
            }
        }
    }
    std::cout << m_depth_map.get_nodes(0).begin()->second->total_segment_count() << std::endl;
    std::cout << segments << std::endl;
    std::cout << length << std::endl;
}

void Optimizer::update_grid_radii()
{
    std::fill(m_xradius.begin(), m_xradius.end(), 0);
    std::fill(m_yradius.begin(), m_yradius.end(), 0);
    KContainer kc(m_k);
    for (primitives::depth_t i{0}; i < primitives::DepthEnd; ++i)
    {
        auto depth = primitives::DepthEnd - 1 - i;
        insert_max_lengths(kc, depth);
        const auto sum = kc.sum();
        if (sum > 0)
        {
            m_xradius[depth] = std::ceil(sum / m_domain.xdim(depth));
            m_yradius[depth] = std::ceil(sum / m_domain.ydim(depth));
        }
    }
}

void Optimizer::insert_max_lengths(KContainer& kc, primitives::depth_t depth) const
{
    if (m_length_table.lengths(depth).size() == 0)
    {
        return;
    }
    for (auto it = m_length_table.lengths(depth).crbegin(); it != m_length_table.lengths(depth).crend(); ++it)
    {
        if (not kc.insert(*it))
        {
            return;
        }
    }
}

#include "Optimizer.h"

void Optimizer::find_best()
{
    m_best = SearchState();
    update_grid_radii();
    for (int depth{0}; depth < primitives::MaxTreeDepth; ++depth)
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

void Optimizer::find_best(int depth, quadtree::depth_map::transform::hash_t node_hash, const quadtree::QuadtreeNode* node)
{
    const auto searchable_nodes = gather_searchable_nodes(depth, node_hash);
    auto it = node->segments().cbegin();
    while (it != node->segments().cend())
    {
        m_current = SearchState(*it);
        find_best(node, ++it);
        for (const auto searchable_node : searchable_nodes)
        {
            find_best(searchable_node);
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
    for (const auto& unique_ptr : node->children())
    {
        if (unique_ptr)
        {
            find_best(unique_ptr.get());
        }
    }
}

std::vector<quadtree::QuadtreeNode*> Optimizer::gather_searchable_nodes(int depth, quadtree::depth_map::transform::hash_t center_node_hash) const
{
    // Searchable nodes meet the following criteria:
    //  1. Same depth.
    //  2. Higher node hash value.
    //  3. Within a certain distance.
    // Assumes higher x-coordinate always gives higher node hash.
    std::vector<quadtree::QuadtreeNode*> searchable_nodes;
    int cx = quadtree::depth_map::transform::x(center_node_hash);
    int cy = quadtree::depth_map::transform::y(center_node_hash);
    int grid_dim = 1 << depth;
    int max_d = grid_dim; // TODO: calculate for maximum admissible new edge length.
    int y_min = std::max(0, cy - max_d);
    int x_end = std::min(grid_dim, cx + max_d);
    int y_end = std::min(grid_dim, cy + max_d);
    for (int x{cx}; x < x_end; ++x)
    {
        for (int y{y_min}; y < y_end; ++y)
        {
            auto hash = quadtree::depth_map::transform::hash_grid_coord(x, y);
            if (hash <= center_node_hash)
            {
                continue;
            }
            const auto it = m_depth_map.get_nodes(depth).find(hash);
            if (it == m_depth_map.get_nodes(depth).end())
            {
                continue;
            }
            searchable_nodes.push_back(it->second);
        }
    }
    return searchable_nodes;
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
    if (m_current.improvement > m_best.improvement)
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
    for (primitives::depth_t depth{primitives::MaxTreeDepth - 1}; i >= 0; --i)
    {
        const auto& lengths = m_length_table.lengths(depth);
        insert_max_lengths(kc, lengths);
        const auto sum = kc.sum();
        if (sum > 0)
        {
            m_xradius[depth] = std::ceil(sum / m_domain.xdim(depth));
            m_yradius[depth] = std::ceil(sum / m_domain.ydim(depth));
        }
    }
}

void Optimizer::insert_max_lengths(KContainer& kc, const std::multiset<length_t>& lengths) const
{
    if (lengths.size() == 0)
    {
        return;
    }
    for (auto it = lengths.crbegin(); it < lengths.crend(); ++it)
    {
        if (not kc.insert(length))
        {
            return;
        }
    }
}

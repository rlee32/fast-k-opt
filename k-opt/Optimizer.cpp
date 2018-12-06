#include "Optimizer.h"

void Optimizer::find_best()
{
    m_calls = 0;
    m_best = SearchState();
    update_grid_radii();
    for (primitives::depth_t depth{0}; depth < primitives::DepthEnd; ++depth)
    {
        //std::cout << "depth: " << depth << std::endl;
        const auto& map = m_depth_map.get_nodes(depth);
        if (map.size() == 0)
        {
            break;
        }
        //std::cout << "map size: " << map.size() << std::endl;
        for (const auto& hash_node_pair : map)
        {
            const auto hash = hash_node_pair.first;
            const auto node = hash_node_pair.second;
            //std::cout << "hash: " << hash << std::endl;
            //std::cout << "grid x, y: " << quadtree::depth_map::transform::x(hash) << ", " << quadtree::depth_map::transform::y(hash) << std::endl;
            find_best(depth, hash, node);
        }
    }
    std::cout << m_k << "-opt checks: " << m_calls << std::endl;
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
    sr.depth = depth;
    sr.center_node_hash = center_node_hash;
    sr.cx = quadtree::depth_map::transform::unhash_x(center_node_hash);
    sr.cy = quadtree::depth_map::transform::unhash_y(center_node_hash);
    primitives::grid_t dx = std::ceil(m_radius[depth] / m_domain.xdim(depth));
    primitives::grid_t dy = std::ceil(m_radius[depth] / m_domain.ydim(depth));
    sr.xmin = std::max(0, sr.cx - dx - 1);
    sr.ymin = std::max(0, sr.cy - dy - 1);
    //sr.xmin = 0;
    //sr.ymin = 0;
    primitives::grid_t grid_dim = 1 << depth;
    sr.xend = std::min(grid_dim, sr.cx + dx + 1);
    sr.yend = std::min(grid_dim, sr.cy + dy + 1);
    //sr.xend = grid_dim;
    //sr.yend = grid_dim;
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
    switch (m_k)
    {
        case 2:
        {
            check_best_2opt();
        } break;
        case 3:
        {
            check_best_3opt();
        } break;
        default:
        {
        } break;
    }
}

void Optimizer::check_best_3opt()
{
    // TODO
    ++m_calls;
    auto& new_segments = m_current.new_segments;
    if (new_segments.size() != 3)
    {
        new_segments.resize(3);
    }
    const auto& s1 = m_current.segments[0];
    const auto& s2 = m_current.segments[1];
    const auto& s3 = m_current.segments[2];
	auto edge_1a2a = m_dt.compute_length(s1.a, s2.a);
	auto edge_1b3a = m_dt.compute_length(s1.b, s3.a);
	auto edge_2b3b = m_dt.compute_length(s2.b, s3.b);
	auto new_length = edge_1a2a + edge_1b3a + edge_2b3b;
    auto minimum_length = m_current.length;
    if (new_length < m_current.length)
    {
        minimum_length = new_length;
        new_segments[0] = {s1.a, s2.a, edge_1a2a};
        new_segments[1] = {s1.b, s3.a, edge_1b3a};
        new_segments[2] = {s2.b, s3.b, edge_2b3b};
    }
	auto edge_1a2b = m_dt.compute_length(s1.a, s2.b);
	auto edge_2a3b = m_dt.compute_length(s2.a, s3.b);
	new_length = edge_1a2b + edge_1b3a + edge_2a3b;
    if (new_length < minimum_length)
    {
        minimum_length = new_length;
        new_segments[0] = {s1.a, s2.b, edge_1a2b};
        new_segments[1] = {s1.b, s3.a, edge_1b3a};
        new_segments[2] = {s2.a, s3.b, edge_2a3b};
    }
	auto edge_1b3b = m_dt.compute_length(s1.b, s3.b);
	auto edge_2a3a = m_dt.compute_length(s2.a, s3.a);
	new_length = edge_1a2b + edge_1b3b + edge_2a3a;
    if (new_length < minimum_length)
    {
        minimum_length = new_length;
        new_segments[0] = {s1.a, s2.b, edge_1a2b};
        new_segments[1] = {s1.b, s3.b, edge_1b3b};
        new_segments[2] = {s2.a, s3.a, edge_2a3a};
    }
	auto edge_1a3a = m_dt.compute_length(s1.a, s3.a);
	auto edge_1b2b = m_dt.compute_length(s1.b, s2.b);
	new_length = edge_1a3a + edge_1b2b + edge_2a3b;
    if (new_length < minimum_length)
    {
        minimum_length = new_length;
        new_segments[0] = {s1.a, s3.a, edge_1a3a};
        new_segments[1] = {s1.b, s2.b, edge_1b2b};
        new_segments[2] = {s2.a, s3.b, edge_2a3b};
    }
    if (minimum_length >= m_current.length)
    {
        return;
    }
    m_current.improvement = m_current.length - minimum_length;
    if (m_current.improvement >= m_best.improvement)
    {
        m_best = m_current;
    }
}

void Optimizer::check_best_2opt()
{
    ++m_calls;
    // TODO: logarithmic distance table.
    const auto& s = m_current.segments;
    /*
    std::cout << "2-opt check:\n";
    std::cout << s[0] << std::endl;
    std::cout << s[1] << std::endl;
    */
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

void Optimizer::traverse_tree()
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
    std::cout << "Total segments tallied by root node: " << m_depth_map.get_nodes(0).begin()->second->total_segment_count() << std::endl;
    std::cout << "Total segments recounted by traversing tree: " << segments << std::endl;
    std::cout << "Total tour length recalculated by traversing tree: " << length << std::endl;
}

void Optimizer::update_grid_radii()
{
    std::fill(m_radius.begin(), m_radius.end(), 0);
    KContainer kc(m_k);
    for (primitives::depth_t i{0}; i < primitives::DepthEnd; ++i)
    {
        auto depth = primitives::DepthEnd - 1 - i;
        insert_max_lengths(kc, depth);
        const auto sum = kc.sum();
        m_radius[depth] = sum;
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

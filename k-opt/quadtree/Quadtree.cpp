#include "Quadtree.h"

namespace quadtree {

void Quadtree::insert(Segment s, const std::vector<primitives::morton_key_t>& keys)
{
    const auto insertion_path = morton_keys::segment_insertion_path(keys[s.min()], keys[s.max()]);
    QuadtreeNode* segment_destination{&m_root};
    uint32_t depth{0}, x{0}, y{0};
    for (auto quadrant : insertion_path)
    {
        ++depth;
        x <<= 1;
        x += depth_map::transform::x(quadrant);
        y <<= 1;
        y += depth_map::transform::y(quadrant);
        auto child = segment_destination->child(quadrant);
        if (not child)
        {
            segment_destination->create_child(quadrant);
            child = segment_destination->child(quadrant);
            m_depth_map.add_node(depth, x, y, child);
        }
        segment_destination = child;
    }
    segment_destination->insert(s);
    m_segment_lengths.insert(s.length);
}
void Quadtree::erase(Segment s, const std::vector<primitives::morton_key_t>& keys)
{
    auto insertion_path = morton_keys::segment_insertion_path(keys[s.min()], keys[s.max()]);
    QuadtreeNode* segment_destination{&m_root};
    QuadtreeNode* parent{nullptr};
    uint32_t depth{0}, x{0}, y{0};
    for (auto quadrant : insertion_path)
    {
        ++depth;
        x <<= 1;
        x += depth_map::transform::x(quadrant);
        y <<= 1;
        y += depth_map::transform::y(quadrant);
        parent = segment_destination;
        segment_destination = segment_destination->child(quadrant);
    }
    auto remaining = segment_destination->erase(s);
    while (parent and remaining == 0)
    {
        auto quadrant = insertion_path.back();
        insertion_path.pop_back();
        m_depth_map.remove_node(depth, x, y);
        parent->reset(quadrant);
        remaining = parent->total_segment_count();
        parent = parent->parent();
        x -= depth_map::transform::x(quadrant);
        x >>= 1;
        y -= depth_map::transform::y(quadrant);
        y >>= 1;
        --depth;
    }
    m_segment_lengths.erase(s.length);
}

void Quadtree::iterate()
{
    int segments{0};
    uint64_t length{0};
    for (int i{0}; i < morton_keys::MaxTreeDepth; ++i)
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
    std::cout << m_root.total_segment_count() << std::endl;
    std::cout << segments << std::endl;
    std::cout << length << std::endl;
}

void Quadtree::find_best()
{
    for (int depth{0}; depth < morton_keys::MaxTreeDepth; ++depth)
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
void Quadtree::find_best(int depth, depth_map::transform::hash_t node_hash, const QuadtreeNode* node)
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
void Quadtree::find_best(const QuadtreeNode* node)
{
    find_best(node, node->segments().cbegin());
}
void Quadtree::find_best(const QuadtreeNode* node, QuadtreeNode::SegmentContainer::const_iterator it)
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
            compare_best();
            ++it;
        }
        else
        {
            find_best(node, ++it);
        }
        m_current.pop_back();
    }
}

std::vector<QuadtreeNode*> Quadtree::gather_searchable_nodes(int depth, depth_map::transform::hash_t center_node_hash) const
{
    // Searchable nodes meet the following criteria:
    //  1. Same depth.
    //  2. Higher node hash value.
    //  3. Within a certain distance.
    // Assumes higher x-coordinate always gives higher node hash.
    std::vector<QuadtreeNode*> searchable_nodes;
    int cx = depth_map::transform::x(center_node_hash);
    int cy = depth_map::transform::y(center_node_hash);
    int grid_dim = 1 << depth;
    int max_d = grid_dim; // TODO: calculate for maximum admissible new edge length.
    int y_min = std::max(0, cy - max_d);
    int x_end = std::min(grid_dim, cx + max_d);
    int y_end = std::min(grid_dim, cy + max_d);
    for (int x{cx}; x < x_end; ++x)
    {
        for (int y{y_min}; y < y_end; ++y)
        {
            auto hash = depth_map::transform::hash_grid_coord(x, y);
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

void Quadtree::compare_best()
{
    // TODO: implement checking all swaps available for m_k > 2.
    // currently only for m_k == 2.
}

} // namespace quadtree

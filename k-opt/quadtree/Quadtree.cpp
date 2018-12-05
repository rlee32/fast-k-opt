#include "Quadtree.h"

namespace quadtree {

void Quadtree::insert(Segment s)
{
    const auto insertion_path = morton_keys::segment_insertion_path(m_morton_keys[s.min()], m_morton_keys[s.max()]);
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
void Quadtree::erase(Segment s)
{
    auto insertion_path = morton_keys::segment_insertion_path(m_morton_keys[s.min()], m_morton_keys[s.max()]);
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

} // namespace quadtree

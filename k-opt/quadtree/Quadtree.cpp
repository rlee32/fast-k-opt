#include "Quadtree.h"

namespace quadtree {

void Quadtree::insert(Segment s)
{
    const auto insertion_path = morton_keys::segment_insertion_path(m_morton_keys[s.min()], m_morton_keys[s.max()]);
    QuadtreeNode* segment_destination{&m_root};
    uint32_t depth{0}, x{0}, y{0};
    //std::cout << s << std::endl;
    for (const auto& quadrant : insertion_path)
    {
        //std::cout << quadrant << std::endl;
        ++depth;
        x <<= 1;
        x += depth_map::transform::quadrant_x(quadrant);
        y <<= 1;
        y += depth_map::transform::quadrant_y(quadrant);
        auto child = segment_destination->child(quadrant);
        if (not child)
        {
            segment_destination->create_child(quadrant);
            child = segment_destination->child(quadrant);
            //std::cout << "grid insertion: " << x << ", " << y << std::endl;
            //std::cout << "unhashed"
            m_depth_map.add_node(depth, x, y, child);
        }
        segment_destination = child;
    }
    segment_destination->insert(s);
    m_length_table.insert(depth, s.length);
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
        x += depth_map::transform::quadrant_x(quadrant);
        y <<= 1;
        y += depth_map::transform::quadrant_y(quadrant);
        parent = segment_destination;
        segment_destination = segment_destination->child(quadrant);
    }
    auto remaining = segment_destination->erase(s);
    if (not m_length_table.erase_one(depth, s.length))
    {
        std::cout << __func__ << ": ERROR: could not find length in length table!\n"
            << "\tdepth, length: " << depth << ", " << s.length << "\n";
    }
    while (parent and remaining == 0)
    {
        auto quadrant = insertion_path.back();
        insertion_path.pop_back();
        m_depth_map.remove_node(depth, x, y);
        parent->reset(quadrant);
        remaining = parent->total_segment_count();
        parent = parent->parent();
        x -= depth_map::transform::quadrant_x(quadrant);
        x >>= 1;
        y -= depth_map::transform::quadrant_y(quadrant);
        y >>= 1;
        --depth;
    }
}

} // namespace quadtree

#include "Quadtree.h"

namespace quadtree {

void Quadtree::insert(Segment s, const std::vector<primitives::quadrant_t>& insertion_path)
{
    QuadtreeNode* segment_destination{&m_root};
    for (auto quadrant : insertion_path)
    {
        auto child = segment_destination->child(quadrant);
        if (not child)
        {
            segment_destination->create_child(quadrant);
            child = segment_destination->child(quadrant);
        }
        segment_destination = child;
    }
    segment_destination->insert(s);
    m_segment_lengths.insert(s.length);
}
std::vector<Segment> Quadtree::suboptimal_segments()
{
    // TODO: remove segment lengths from m_segment_lengths.
    return std::vector<Segment>();
}

} // namespace quadtree

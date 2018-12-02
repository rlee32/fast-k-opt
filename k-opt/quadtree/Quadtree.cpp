#include "Quadtree.h"

namespace quadtree {

void Quadtree::insert(Segment s, const std::vector<int>& insertion_path)
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
}
std::vector<Segment> Quadtree::suboptimal_segments()
{
    return std::vector<Segment>();
}

} // namespace quadtree

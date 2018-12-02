#include "Quadtree.h"

namespace quadtree {

void Quadtree::insert(const Segment<QuadtreeNode>* segment, const std::vector<int>& insertion_path)
{
    QuadtreeNode* segment_destination{m_root};
    for (auto quadrant : insertion_path)
    {
        auto child = segment_destination->child(insertion_path[quadrant]);
        if (not child)
        {
            segment_destination->create_child(quadrant);
            child = segment_destination->child(quadrant);
        }
        segment_destination = child;
    }
    segment_destination->add(segment);
}

void Quadtree::InsertTourSegments(fileio::Tour&)
{
    // for(int i = 0; i < point_count; ++i) InsertSegment(tour.segment(i));
}

} // namespace quadtree

#include "Quadtree.h"

namespace quadtree {

void Quadtree::InsertSegment(Segment<Quadtree>*)
{
    /*
    MortonKey key1 = point_morton_keys_[segment->start_city];
    MortonKey key2 = point_morton_keys_[segment->end_city];

    std::vector<int> traversal = MergePointMortonKeys(key1, key2);
    QuadtreeNode* current = m_root;
    for (std::vector<int>::iterator it=traversal.begin(); it!=traversal.end(); ++it)
    {
    if(current->children(*it) == nullptr) break;
    current = current->children(*it);
    }
    current->AddImmediateSegment(segment);
    segment->node = current;
    //Update max_segment_size_
    if(segment->length > current->max_segment_length())
    {
    current->set_max_segment_length(segment->length);
    }
    */
}

void Quadtree::InsertTourSegments(fileio::Tour&)
{
    // for(int i = 0; i < point_count; ++i) InsertSegment(tour.segment(i));
}

} // namespace quadtree

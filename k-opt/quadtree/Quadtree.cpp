#include "Quadtree.h"

namespace quadtree {

Quadtree::Quadtree()
{
    m_root = new QuadtreeNode();
}

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

void Quadtree::MakeMortonTour(std::vector<std::pair<morton_keys::MortonKey, int>>&, fileio::Tour&)
{
    /*
  double* x = tour.x();
  double* y = tour.y();
  double* x_buffer = new double[point_count];
  double* y_buffer = new double[point_count];
  std::copy( x, x+point_count, x_buffer );
  std::copy( y, y+point_count, y_buffer );
  for( int i = 0; i < point_count; ++i )
  {
    int city = morton_key_pairs[i].second;
    x[i] = x_buffer[city];
    y[i] = y_buffer[city];
  }
  tour.InitializeSegments();

  delete[] x_buffer;
  delete[] y_buffer;
  */
}

} // namespace quadtree

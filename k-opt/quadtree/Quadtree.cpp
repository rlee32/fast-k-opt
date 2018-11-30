#include "Quadtree.h"

namespace quadtree {

Quadtree::Quadtree(const std::vector<double>& x, const std::vector<double>& y)
{
    const auto point_count = x.size();
    // Get domain bounds
    double x_min = min_element(x, point_count);
    double x_max = max_element(x, point_count);
    double y_min = min_element(y, point_count);
    double y_max = max_element(y, point_count);

    double x_range = x_max - x_min;
    double y_range = y_max - y_min;

    // In this tree construction code we assume the points at within each node
    // have the same Morton Key prefix. So when a point is on the exact boundary,
    // it gets put into the quadrant it would go in if it was a small increment
    // larger (in either x or y). This is fine, EXCEPT at the root. There is no
    // next quadrant. So, we have to apply fudge factor to ranges to completely
    // capture boundary points within the root node.
    constexpr double RootNodeMargin = 1.00001;
    x_range *= RootNodeMargin;
    y_range *= RootNodeMargin;

    // The sorted morton key array is only needed for construction. After that,
    // it is no longer needed.
    // So we can sort by the first item in pair, and retain the city index,
    // we create the following vector.
    std::vector<std::pair<MortonKeyType, int>> morton_key_pairs;
    point_morton_keys_ = new MortonKeyType[point_count];
    for (int i{0}; i < point_count; ++i)
    {
        double x_normalized = (tour.x(i) - x_min) / x_range;
        double y_normalized = (tour.y(i) - y_min) / y_range;

        // filter normalized values
        x_normalized = (x_normalized < 0.0) ? 0.0: x_normalized;
        y_normalized = (y_normalized < 0.0) ? 0.0: y_normalized;
        x_normalized = (x_normalized > 1.0) ? 1.0: x_normalized;
        y_normalized = (y_normalized > 1.0) ? 1.0: y_normalized;

        MortonKey morton_key(i, x_normalized, y_normalized);
        // bitset<8*sizeof(morton_key.value())> morton_bits(morton_key.value());
        // cout << morton_bits.to_string().substr(22) << endl;
        pair<MortonKeyType, int> morton_key_pair ( morton_key.value(), i );
        point_morton_keys_[i] = morton_key.value();
        morton_key_pairs.push_back( morton_key_pair );
    }
    std::sort(morton_key_pairs.begin(), morton_key_pairs.end());

    // Let's make the tour a Morton-order tour!
    // MakeMortonTour(morton_key_pairs, tour);

    // Now we can create the tree (recursively)
    m_root = new QuadtreeNode();
    InsertTourSegments(tour);
}

static const MortonKeyType MORTON_THREE = static_cast<MortonKeyType>(3);

std::vector<int> Quadtree::MergePointMortonKeys(MortonKeyType key1, MortonKeyType key2)
{
    // cout << "Merging: " << endl;
    // cout << bitset<64>(key1).to_string().substr(22) << endl;
    // cout << bitset<64>(key2).to_string().substr(22) << endl;
    std::vector<int> traversal;
    // We skip i = 0 because that would simply lead to root comparison.
    for(int i = 1; i < MAX_LEVEL; ++i)
    {
        MortonKeyType level1 = key1 >> 2*(MAX_LEVEL - i - 1);
        MortonKeyType level2 = key2 >> 2*(MAX_LEVEL - i - 1);
        if (level1 == level2)
        {
            int quadrant = static_cast<int>(level1 & MORTON_THREE);
            traversal.push_back(quadrant);
            // cout << quadrant << endl;
        }
    }
    return traversal;
}

void Quadtree::InsertSegment(Segment* segment)
{
  MortonKeyType key1 = point_morton_keys_[segment->start_city];
  MortonKeyType key2 = point_morton_keys_[segment->end_city];

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
}

void Quadtree::InsertTourSegments(Tour& tour)
{
    for(int i = 0; i < point_count; ++i) InsertSegment(tour.segment(i));
}

void Quadtree::MakeMortonTour(std::vector<std::pair<MortonKeyType, int> >& morton_key_pairs, Tour& tour)
{
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
}

} // namespace quadtree

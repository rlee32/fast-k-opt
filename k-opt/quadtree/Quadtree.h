#pragma once

// This handles the generation and sorting of Morton keys, and quadtree construction.

#include <vector>
#include <algorithm>
#include <utility>
#include <bitset>

#include "Tour.h"
#include "MortonKey.h"
#include "QuadtreeNode.h"
#include "Segment.h"

namespace quadtree {

class Quadtree
{
public:
    Quadtree(Tour& tour);
    ~Quadtree()
    {
        delete[] point_morton_keys_;
        delete m_root;
    }
    QuadtreeNode* root() { return m_root; }
    void print(int max_level) { m_root->Print(max_level); }
    void InsertSegment(Segment* segment);
private:
    MortonKeyType* point_morton_keys_; // point morton keys accessible by point identifier.
    QuadtreeNode* m_root{nullptr};
    double minimum(double* x, int length);
    double maximum(double* x, int length);

    // void InsertTourSegments(Tour& tour);
    std::vector<int> MergePointMortonKeys(MortonKeyType key1, MortonKeyType key2);
    void InsertTourSegments(Tour&);
    void MakeMortonTour(std::vector<std::pair<MortonKeyType, int>>& morton_key_pairs, Tour&);
};

} // namespace quadtree

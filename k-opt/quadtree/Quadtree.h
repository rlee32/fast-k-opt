#pragma once

// This handles the generation and sorting of Morton keys, and quadtree construction.

#include <vector>
#include <algorithm>
#include <utility>
#include <bitset>

#include <fileio/Tour.h> // TODO: remove dependency on Tour class.

#include "morton_keys.h"
#include "QuadtreeNode.h"
#include "Segment.h"

namespace quadtree {

class Quadtree
{
public:
    Quadtree()
    {
        m_root = new QuadtreeNode();
    }
    ~Quadtree()
    {
        delete m_root;
    }
    QuadtreeNode* root() { return m_root; }
    void print(int max_level) { m_root->print(max_level); }
    void InsertSegment(Segment<Quadtree>* segment);
private:
    QuadtreeNode* m_root{nullptr};
    double minimum(double* x, int length);
    double maximum(double* x, int length);

    // void InsertTourSegments(Tour& tour);
    std::vector<int> MergePointMortonKeys(morton_keys::MortonKey key1, morton_keys::MortonKey key2);
    void InsertTourSegments(fileio::Tour&);
};

} // namespace quadtree

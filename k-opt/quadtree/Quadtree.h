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
    QuadtreeNode& root() { return m_root; }
    void print(int max_level) { m_root.print(max_level); }
    void insert(Segment, const std::vector<int>& insertion_path);
    std::vector<Segment> suboptimal_segments();

private:
    QuadtreeNode m_root;
};

} // namespace quadtree

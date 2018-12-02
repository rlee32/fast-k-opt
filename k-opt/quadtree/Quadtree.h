#pragma once

// This handles the generation and sorting of Morton keys, and quadtree construction.

#include "QuadtreeNode.h"
#include "Segment.h"
#include "morton_keys.h"

#include <algorithm>
#include <bitset>
#include <set>
#include <utility>
#include <vector>

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
    std::multiset<uint64_t> m_segment_lengths;
};

} // namespace quadtree

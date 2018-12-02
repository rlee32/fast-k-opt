#pragma once

// This handles the generation and sorting of Morton keys, and quadtree construction.

#include "QuadtreeNode.h"
#include "Segment.h"
#include "morton_keys.h"
#include <primitives.h>

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
    void print(primitives::depth_t max_depth) { m_root.print(max_depth); }
    void insert(Segment, const std::vector<primitives::morton_key_t>& keys);
    void erase(Segment, const std::vector<primitives::morton_key_t>& keys);
    std::vector<Segment> suboptimal_segments();

private:
    QuadtreeNode m_root;
    std::multiset<primitives::length_t> m_segment_lengths;
};

} // namespace quadtree

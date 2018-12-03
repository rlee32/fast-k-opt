#pragma once

// This handles the generation and sorting of Morton keys, and quadtree construction.

#include "depth_map/transform.h"
#include "depth_map/DepthMap.h"
#include "QuadtreeNode.h"
#include "Segment.h"
#include "morton_keys.h"
#include <primitives.h>

#include <algorithm>
#include <cstdint>
#include <set>
#include <vector>

namespace quadtree {

class Quadtree
{
public:
    Quadtree() { m_depth_map.add_node(0, 0, 0, &m_root); }
    QuadtreeNode& root() { return m_root; }
    void print(primitives::depth_t max_depth) { m_root.print(max_depth); }
    void insert(Segment, const std::vector<primitives::morton_key_t>& keys);
    void erase(Segment, const std::vector<primitives::morton_key_t>& keys);
    std::vector<Segment> suboptimal_segments();

    void iterate();

private:
    QuadtreeNode m_root;
    std::multiset<primitives::length_t> m_segment_lengths;
    depth_map::DepthMap m_depth_map;
};

} // namespace quadtree

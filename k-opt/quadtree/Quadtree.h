#pragma once

// This handles the generation and sorting of Morton keys, and quadtree construction.

#include "QuadtreeNode.h"
#include "depth_map/DepthMap.h"
#include "depth_map/transform.h"
#include "morton_keys.h"
#include <SearchState.h>
#include <Segment.h>
#include <primitives.h>

#include <algorithm>
#include <cstdint>
#include <set>
#include <vector>

namespace quadtree {

class Quadtree
{
public:
    Quadtree(depth_map::DepthMap& depth_map, const std::vector<primitives::morton_key_t>& morton_keys)
        : m_depth_map(depth_map), m_morton_keys(morton_keys) {}

    QuadtreeNode& root() { return m_root; }
    void insert(Segment);
    void erase(Segment);

private:
    depth_map::DepthMap& m_depth_map;
    const std::vector<primitives::morton_key_t>& m_morton_keys;

    QuadtreeNode m_root;
    std::multiset<primitives::length_t> m_segment_lengths;
};

} // namespace quadtree

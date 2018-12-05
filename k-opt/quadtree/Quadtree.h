#pragma once

// This handles the generation and sorting of Morton keys, and quadtree construction.

#include "LengthTable.h"
#include "QuadtreeNode.h"
#include "depth_map/DepthMap.h"
#include "depth_map/transform.h"
#include "morton_keys.h"
#include <SearchState.h>
#include <Segment.h>
#include <primitives.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

namespace quadtree {

class Quadtree
{
public:
    Quadtree(depth_map::DepthMap& depth_map, const std::vector<primitives::morton_key_t>& morton_keys)
        : m_depth_map(depth_map), m_morton_keys(morton_keys) {}

    QuadtreeNode* root() { return &m_root; }
    void insert(Segment);
    void erase(Segment);

    const LengthTable& length_table() const { return m_length_table; }

private:
    depth_map::DepthMap& m_depth_map;
    const std::vector<primitives::morton_key_t>& m_morton_keys;
    LengthTable m_length_table;

    QuadtreeNode m_root;
};

} // namespace quadtree

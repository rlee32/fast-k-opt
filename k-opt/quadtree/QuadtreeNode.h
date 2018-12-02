#pragma once

// Children are indexed by Morton key quadrant.

#include "morton_keys.h"
#include "Segment.h"
#include <primitives.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace quadtree {

class QuadtreeNode
{
public:
    QuadtreeNode() = default;
    QuadtreeNode(QuadtreeNode* parent, primitives::quadrant_t quadrant);

    primitives::depth_t depth() const { return m_depth; }
    primitives::quadrant_t quadrant() const { return m_quadrant; }
    QuadtreeNode* child(primitives::quadrant_t quadrant) { return m_children[quadrant].get(); }
    void print(primitives::depth_t max_level = morton_keys::MAX_LEVEL);

    size_t total_segment_count() { return m_total_segment_count; }

    void insert(Segment);
    size_t erase(Segment);
    void reset(primitives::quadrant_t quadrant);

    void create_child(primitives::quadrant_t quadrant);

private:
    QuadtreeNode* m_parent{nullptr};
    std::array<std::unique_ptr<QuadtreeNode>, 4> m_children; // index corresponds to Morton order quadrant.
    primitives::depth_t m_depth{0}; // root = 0.
    primitives::quadrant_t m_quadrant{4}; // The Morton order of this node relative to siblings (0-3). For the root, this is 4.
    // Segment information.
    std::unordered_set<Segment, Segment::Hash> m_segments; // segments under this node only (not children).
    size_t m_total_segment_count{0}; // total segments under this node and all child nodes.

    void modify_total_segment_count(int amount);
};

} // namespace quadtree

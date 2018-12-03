#pragma once

// Children are indexed by Morton key quadrant.

#include "morton_keys.h"
#include "Segment.h"
#include <primitives.h>

#include <algorithm>
#include <array>
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
    QuadtreeNode(QuadtreeNode* parent);

    // Need fast insertion and removal.
    using SegmentContainer = std::unordered_set<Segment, Segment::Hash>;

    QuadtreeNode* child(primitives::quadrant_t q) { return m_children[q].get(); }

    size_t total_segment_count() { return m_total_segment_count; }
    const SegmentContainer& segments() const { return m_segments; }

    void insert(Segment);
    size_t erase(Segment);
    void reset(primitives::quadrant_t);
    QuadtreeNode* parent() { return m_parent; }

    void create_child(primitives::quadrant_t);

private:
    QuadtreeNode* m_parent{nullptr};
    std::array<std::unique_ptr<QuadtreeNode>, 4> m_children; // index corresponds to Morton order quadrant.
    // Segment information.
    SegmentContainer m_segments; // segments under this node only (not children).
    size_t m_total_segment_count{0}; // total segments under this node and all child nodes.

    void modify_total_segment_count(int amount);
};

} // namespace quadtree

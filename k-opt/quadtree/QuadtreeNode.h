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
    using ChildArray = std::array<std::unique_ptr<QuadtreeNode>, 4>;
public:
    QuadtreeNode() = default;
    QuadtreeNode(QuadtreeNode* parent);

    // Need fast insertion and removal.
    using SegmentContainer = std::unordered_set<Segment, Segment::Hash>;

    const ChildArray& children() const { return m_children; }
    QuadtreeNode* child(primitives::quadrant_t q) { return m_children[q].get(); }

    size_t total_segment_count() const { return m_total_segment_count; }
    const SegmentContainer& segments() const { return m_segments; }
    SegmentContainer& segments() { return m_segments; }

    void insert(Segment);
    size_t erase(Segment);
    void reset(primitives::quadrant_t);
    QuadtreeNode* parent() { return m_parent; }
    const QuadtreeNode* parent() const { return m_parent; }

    void create_child(primitives::quadrant_t);

    // preorder traversal.
    // returns nullptr if end is reached.
    const QuadtreeNode* next(const QuadtreeNode* end) const;

    primitives::grid_t x() const { return m_x; }
    primitives::grid_t y() const { return m_y; }
    void x(primitives::grid_t x) { m_x = x; }
    void y(primitives::grid_t y) { m_y = y; }

private:
    QuadtreeNode* m_parent{nullptr};
    ChildArray m_children; // index corresponds to Morton order quadrant.
    // Segment information.
    SegmentContainer m_segments; // segments under this node only (not children).
    size_t m_total_segment_count{0}; // total segments under this node and all child nodes.
    primitives::grid_t m_x{0};
    primitives::grid_t m_y{0};

    void modify_total_segment_count(int amount);

    // preorder traversal.
    // returns nullptr if end is reached.
    const QuadtreeNode* next(const QuadtreeNode* child, const QuadtreeNode* end) const;
};

} // namespace quadtree

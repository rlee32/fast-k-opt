#pragma once

// Provides segments from preorder traversal of quadtree, starting from and ending at the provided root node.

#include "quadtree/QuadtreeNode.h"
#include "NodeIterator.h"

#include <iterator>
#include <vector>

namespace optimizer {

class SegmentIterator
{
    using SegmentContainer = quadtree::QuadtreeNode::SegmentContainer;
    using segment_iterator = SegmentContainer::const_iterator;
public:
    SegmentIterator(const NodeIterator& nit);

    const Segment& operator*() const { return *m_segment; }
    SegmentIterator& operator++();
    SegmentIterator operator++(int);

    bool done() const { return m_current == nullptr; }

private:
    const quadtree::QuadtreeNode* m_end{nullptr};
    const quadtree::QuadtreeNode* m_current{nullptr}; // becomes nullptr at end of search (root revisited).
    segment_iterator m_segment;
    segment_iterator m_extra;
    segment_iterator m_extra_end;

    void skip_empty_nodes();
    void next_node();
};

} // namespace optimizer

#pragma once

#include "quadtree/QuadtreeNode.h"

#include <vector>

namespace optimizer {

class NodeIterator
{
    using NodeContainer = std::vector<const quadtree::QuadtreeNode*>;
    using node_iterator = NodeContainer::const_iterator;
public:
    NodeIterator(const NodeContainer& partial, const NodeContainer& full);

    const quadtree::QuadtreeNode*  operator*() const;
    NodeIterator& operator++();
    NodeIterator operator++(int);

    bool done() const;
    bool skip_root() const { return m_skip_root; }

private:
    const NodeContainer& m_partial_nodes;
    const NodeContainer& m_full_nodes;
    node_iterator m_current;
    bool m_skip_root{true};

    void skip();
    bool skippable() const; // no segments or end.
    void move_to_full_nodes();
};

} // namespace optimizer

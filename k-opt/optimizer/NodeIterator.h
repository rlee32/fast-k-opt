#pragma once

#include "quadtree/QuadtreeNode.h"
#include "SearchBox.h"

#include <vector>

namespace optimizer {

class NodeIterator
{
    using NodeContainer = std::vector<const quadtree::QuadtreeNode*>;
    using node_iterator = NodeContainer::const_iterator;
public:
    NodeIterator(const NodeContainer& partial, const NodeContainer& full, SearchBox<> sb);

    const quadtree::QuadtreeNode*  operator*() const;
    NodeIterator& operator++();
    NodeIterator operator++(int);

    bool done() const;
    bool skip_root() const { return m_skip_root; }
    SearchBox<> sb() const { return m_sb; }
    void sb(SearchBox<> sb) { m_sb = sb; }
    void restrict_search();

private:
    const NodeContainer& m_partial_nodes;
    const NodeContainer& m_full_nodes;
    SearchBox<> m_sb;
    node_iterator m_current;
    bool m_skip_root{true};
    // Note that partial and full node vectors can have coinciding begin() and end().
    // In the case partial begin() == full end(), a premature done() can happen if the condition is
    //  to check for full end(). This can be very confusing as it is pretty much non-deterministic,
    //  because it depends on the relative allocation locations of the partial and full vectors.
    // So m_remaining is used instead.
    size_t m_remaining{0};

    void skip();
    bool skippable() const; // no segments or end.
    void move_to_full_nodes();
};

} // namespace optimizer

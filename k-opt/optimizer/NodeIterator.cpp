#include "NodeIterator.h"

namespace optimizer {

NodeIterator::NodeIterator(const NodeContainer& partial, const NodeContainer& full)
    : m_partial_nodes(partial)
    , m_full_nodes(full)
    , m_current(std::cbegin(m_partial_nodes))
{
    if (m_partial_nodes.empty())
    {
        move_to_full_nodes();
    }
}

const quadtree::QuadtreeNode*  NodeIterator::operator*() const
{
    if (done())
    {
        return nullptr;
    }
    return *m_current;
}

NodeIterator& NodeIterator::operator++()
{
    if (not done())
    {
        ++m_current;
        if (m_current == std::cend(m_partial_nodes))
        {
            move_to_full_nodes();
        }
    }
    return *this;
}
NodeIterator NodeIterator::operator++(int)
{
    auto old = *this;
    operator++();
    return old;
}

bool NodeIterator::done() const
{
    return m_current == std::cend(m_full_nodes);
}

void NodeIterator::move_to_full_nodes()
{
    m_current = std::cbegin(m_full_nodes);
    m_skip_root = false;
}

} // namespace optimizer

#include "NodeIterator.h"

namespace optimizer {

NodeIterator::NodeIterator(const NodeContainer& partial, const NodeContainer& full)
    : m_partial_nodes(partial)
    , m_full_nodes(full)
    , m_current(std::cbegin(partial))
    , m_remaining(m_partial_nodes.size() + m_full_nodes.size())
{
    if (m_partial_nodes.empty())
    {
        move_to_full_nodes();
    }
}

const quadtree::QuadtreeNode* NodeIterator::operator*() const
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
        --m_remaining;
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
    return m_remaining == 0;
}

void NodeIterator::move_to_full_nodes()
{
    m_current = std::cbegin(m_full_nodes);
    m_skip_root = false;
}

} // namespace optimizer

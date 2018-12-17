#include "SegmentIterator.h"

namespace optimizer {

SegmentIterator::SegmentIterator(const NodeIterator& nit)
    : m_end(*nit), m_current(*nit)
{
    if (not *nit)
    {
        return;
    }
    if (nit.skip_root() or m_current->segments().empty())
    {
        next_node();
    }
    skip_empty_nodes();
    if (not done())
    {
        m_segment = std::cbegin(m_current->segments());
    }
}

SegmentIterator::SegmentIterator(const quadtree::QuadtreeNode* root)
    : m_end(root), m_current(root)
{
    if (not root)
    {
        return;
    }
    if (m_current->segments().empty())
    {
        next_node();
    }
    skip_empty_nodes();
    if (not done())
    {
        m_segment = std::cbegin(m_current->segments());
    }
}

void SegmentIterator::skip_empty_nodes()
{
    if (done())
    {
        return;
    }
    while (m_current->segments().empty())
    {
        next_node();
        if (done())
        {
            break;
        }
    }
}

void SegmentIterator::next_node()
{
    if (done())
    {
        return;
    }
    m_current = m_current->next(m_end);
}

SegmentIterator& SegmentIterator::operator++()
{
    if (done())
    {
        return *this;
    }
    ++m_segment;
    if (m_segment == std::cend(m_current->segments()))
    {
        next_node();
        skip_empty_nodes();
        if (not done())
        {
            m_segment = std::cbegin(m_current->segments());
        }
    }
    return *this;
}
SegmentIterator SegmentIterator::operator++(int)
{
    auto old = *this;
    operator++();
    return old;
}

} // namespace optimizer


#include "SegmentIterator.h"

namespace optimizer {

SegmentIterator::SegmentIterator(const quadtree::QuadtreeNode* root, bool skip_root)
    : m_end(root), m_current(root)
{
    if (skip_root or m_current->segments().empty())
    {
        next_node();
    }
    skip_empty_nodes();
    m_segment = std::cbegin(m_current->segments());
}

void SegmentIterator::skip_empty_nodes()
{
    while (m_current->segments().empty() and m_current != m_end)
    {
        next_node();
    }
}

void SegmentIterator::next_node()
{
    m_current = m_current->next(m_end);
}

SegmentIterator& SegmentIterator::operator++()
{
    ++m_segment;
    if (m_segment == std::cend(m_current->segments()))
    {
        next_node();
        skip_empty_nodes();
        m_segment = std::cbegin(m_current->segments());
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


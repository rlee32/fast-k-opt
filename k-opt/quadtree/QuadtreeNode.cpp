#include "QuadtreeNode.h"

namespace quadtree {

QuadtreeNode::QuadtreeNode(QuadtreeNode* parent)
    : m_parent(parent) {}

void QuadtreeNode::modify_total_segment_count(int amount)
{
    m_total_segment_count += amount;
    if (m_parent)
    {
        m_parent->modify_total_segment_count(amount);
    }
}

void QuadtreeNode::insert(Segment s)
{
    m_segments.insert(s);
    modify_total_segment_count(1);
}

size_t QuadtreeNode::erase(Segment s)
{
    m_segments.erase(s);
    modify_total_segment_count(-1);
    return m_total_segment_count;
}

void QuadtreeNode::create_child(primitives::quadrant_t quadrant)
{
    if (m_children[quadrant])
    {
        return;
    }
    m_children[quadrant] = std::make_unique<QuadtreeNode>(this);
}

void QuadtreeNode::reset(primitives::quadrant_t quadrant)
{
    m_children[quadrant].reset();
}

const QuadtreeNode* QuadtreeNode::next(const QuadtreeNode* end) const
{
    for (const auto& unique_ptr : m_children)
    {
        if (unique_ptr)
        {
            return unique_ptr.get();
        }
    }
    // Leaf node.
    if (this == end)
    {
        return nullptr;
    }
    if (m_parent)
    {
        return m_parent->next(this, end);
    }
    return nullptr;
}

const QuadtreeNode* QuadtreeNode::next(const QuadtreeNode* child, const QuadtreeNode* end) const
{
    bool assign_next{false};
    const QuadtreeNode* next_child{nullptr};
    for (const auto& unique_ptr : m_children)
    {
        if (assign_next)
        {
            if (unique_ptr)
            {
                next_child = unique_ptr.get();
                break;
            }
        }
        else
        {
            assign_next = child == unique_ptr.get();
        }
    }
    if (next_child)
    {
        return next_child;
    }
    // Traversed all children.
    if (this == end)
    {
        return nullptr;
    }
    return m_parent->next(this, end);
}

} // namespace quadtree

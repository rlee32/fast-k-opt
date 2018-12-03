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

/*
void QuadtreeNode::populate_candidates(std::vector<primitives::point_id_t>& , std::vector<Segment>& candidates, int nodal_offset, int k)
{
}
*/

} // namespace quadtree

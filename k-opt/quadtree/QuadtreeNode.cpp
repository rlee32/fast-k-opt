#include "QuadtreeNode.h"

namespace quadtree {

QuadtreeNode::QuadtreeNode(QuadtreeNode* parent, primitives::quadrant_t quadrant)
    : m_parent(parent)
    , m_quadrant(quadrant)
{
    if (m_parent)
    {
        m_depth = m_parent->depth() + 1;
    }
}

void QuadtreeNode::print(primitives::depth_t max_level)
{
    if (m_depth <= max_level)
    {
        std::string tabs("");
        for (int i{0}; i < m_depth; ++i)
        {
            tabs += "\t";
        }
        std::cout << std::endl;
        std::cout << tabs << "Depth: " << m_depth << std::endl;
        std::cout << tabs << "Quadrant: " << m_quadrant << std::endl;
        std::cout << tabs << "Total Number of Segments: " << m_total_segment_count << std::endl;
        std::cout << tabs << "Immediate Segments: " << m_segments.size() << std::endl;
        std::cout << std::endl;
        for (const auto& child : m_children)
        {
            if (child)
            {
                child->print(max_level);
            }
        }
    }
}

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
    m_children[quadrant] = std::make_unique<QuadtreeNode>(this, quadrant);
}

void QuadtreeNode::reset(primitives::quadrant_t quadrant)
{
    m_children[quadrant].reset();
}

} // namespace quadtree

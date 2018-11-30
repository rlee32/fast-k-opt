#include "QuadtreeNode.h"

namespace quadtree {

QuadtreeNode::QuadtreeNode(QuadtreeNode* parent, int quadrant)
    : m_parent(parent)
    , m_quadrant(quadrant)
{
    if (m_parent)
    {
        m_tree_level = m_parent->tree_level() + 1;
    }
}

struct pair_search_comparator
{
    bool operator()(std::pair<MortonKeyType, int> pair, size_t size) const
    {
      return pair.first < size;
    }
    bool operator()(size_t size, std::pair<MortonKeyType, int> pair) const
    {
      return size < pair.first;
    }
};

void QuadtreeNode::print(int max_level)
{
    if (m_tree_level <= max_level)
    {
        std::string tabs("");
        for (int i{0}; i < m_tree_level; ++i)
        {
            tabs += "\t";
        }
        std::cout << std::endl;
        std::cout << tabs << "Tree level: " << m_tree_level << std::endl;
        std::cout << tabs << "Quadrant: " << m_quadrant << std::endl;
        std::cout << tabs << "Total Number of Segments: " << m_total_segment_count << std::endl;
        std::cout << tabs << "Immediate Segments: " << m_segments.size() << std::endl;
        std::cout << tabs << "Is leaf: " << m_is_leaf << std::endl;
        std::cout << std::endl;
        for (int i{0}; i < 4; ++i)
        {
            if (m_children[i])
            {
                m_children[i]->print(max_level);
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

void QuadtreeNode::add_segment(SegmentType* s)
{
    m_segments.push_back(s);
    modify_total_segment_count(1);
}

void QuadtreeNode::delete_segment(SegmentType* s)
{
    auto it = std::find(m_segments.begin(), m_segments.end(), s);
    m_segments.erase(it);
    modify_total_segment_count(-1);
}

} // namespace quadtree

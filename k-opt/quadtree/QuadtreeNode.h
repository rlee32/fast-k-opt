#pragma once

#include "morton_keys.h"
#include "Segment.h"

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace quadtree {

using IdContainer = std::vector<int>; // can contain segment or point identifiers.

class QuadtreeNode
{
using SegmentType = Segment<QuadtreeNode>;
using SegmentContainer = std::vector<SegmentType*>;
public:
    QuadtreeNode() = default;
    QuadtreeNode(QuadtreeNode* parent, int quadrant);
    ~QuadtreeNode()
    {
        for (int i{0}; i < 4; ++i)
        {
            if (m_children[i])
            {
                delete m_children[i];
            }
        }
    }

    int tree_level() const { return m_tree_level; }
    int quadrant() const { return m_quadrant; }
    QuadtreeNode* children(int index) const { return m_children[index]; }
    void print(int max_level = morton_keys::MAX_LEVEL);

    int total_segment_count() { return m_total_segment_count; }
    SegmentContainer* immediate_segments() { return &m_segments; }
    int immediate_segment_count() { return m_segments.size(); }

    void add_segment(SegmentType* segment);
    void delete_segment(SegmentType* segment);

private:
    // Tree location information.
    QuadtreeNode* m_parent{nullptr};
    int m_children_count{0}; // number of children currently held in m_children.
    std::array<QuadtreeNode*, 4> m_children{{nullptr, nullptr, nullptr, nullptr}}; //pointers to child nodes (null pointers if no
        // child node). Index corresponds to Morton order quadrant.
    int m_tree_level{0}; // tree level (root = 0).
    int m_quadrant{-1}; // The Morton order of this node relative to siblings (0-3). For the root, this is -1.
    bool m_is_leaf{true};

    // Segment information.
    SegmentContainer m_segments; // segments under this node only (not children).
    int m_total_segment_count{0}; // total segments under this node and all child nodes.

    void modify_total_segment_count(int amount);
    void delete_segment(SegmentContainer::iterator it);
};

} // namespace quadtree

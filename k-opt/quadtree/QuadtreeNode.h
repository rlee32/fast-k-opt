#pragma once

// Children are indexed by Morton key quadrant.

#include "morton_keys.h"
#include "Segment.h"

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

namespace quadtree {

class QuadtreeNode
{
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
    QuadtreeNode* child(int index) const { return m_children[index]; }
    void print(int max_level = morton_keys::MAX_LEVEL);

    int total_segment_count() { return m_total_segment_count; }

    void insert(Segment);
    void erase(Segment);

    void create_child(int quadrant);

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
    std::unordered_set<Segment, Segment::Hash> m_segments; // segments under this node only (not children).
    int m_total_segment_count{0}; // total segments under this node and all child nodes.

    void modify_total_segment_count(int amount);
};

} // namespace quadtree

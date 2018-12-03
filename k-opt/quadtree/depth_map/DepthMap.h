#pragma once

#include "transform.h"
#include <quadtree/QuadtreeNode.h>
#include <quadtree/morton_keys.h>

#include <array>
#include <map>

namespace quadtree {
namespace depth_map {

class DepthMap
{
    using NodeContainer = std::map<transform::hash_t, QuadtreeNode*>;
public:
    const QuadtreeNode* get_node(int depth, transform::grid_coord_t x, transform::grid_coord_t y) const
    {
        auto hash = transform::hash_grid_coord(x, y);
        const auto it = m_nodes[depth - 1].find(hash);
        if (it == m_nodes[depth - 1].end())
        {
            return nullptr;
        }
        else
        {
            return it->second;
        }
    }
    const NodeContainer& get_nodes(int depth) const
    {
        return m_nodes[depth - 1];
    }
    void add_node(int depth, transform::grid_coord_t x, transform::grid_coord_t y, QuadtreeNode* node)
    {
        auto hash = transform::hash_grid_coord(x, y);
        m_nodes[depth - 1][hash] = node;
    }

private:
    std::array<NodeContainer, morton_keys::MaxTreeDepth - 1> m_nodes; // exclude root node level.

};


} // namespace depth_map
} // namespace quadtree


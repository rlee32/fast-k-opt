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
    const QuadtreeNode* get_node(int depth, transform::grid_coord_t x, transform::grid_coord_t y) const;
    const NodeContainer& get_nodes(int depth) const;
    void add_node(int depth, transform::grid_coord_t x, transform::grid_coord_t y, QuadtreeNode* node);
    void remove_node(int depth, transform::grid_coord_t x, transform::grid_coord_t y);

private:
    std::array<NodeContainer, morton_keys::MaxTreeDepth> m_nodes;

};


} // namespace depth_map
} // namespace quadtree


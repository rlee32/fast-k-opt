#pragma once

#include "QuadtreeNode.h"
#include "morton_keys.h"

#include <array>
#include <limits>
#include <map>

namespace quadtree {

class DepthMap
{
    using hash_t = uint64_t;
    using grid_coord_t = uint32_t;
public:
    const QuadtreeNode* get_node(int depth, grid_coord_t x, grid_coord_t y) const
    {
        auto hash = hash_grid_coord(x, y);
        const auto it = m_nodes[depth].find(hash);
        if (it == m_nodes[depth].end())
        {
            return nullptr;
        }
        else
        {
            return it->second;
        }
    }
    const std::map<hash_t, QuadtreeNode*>& get_nodes(int depth) const
    {
        return m_nodes[depth];
    }

private:
    std::array<std::map<hash_t, QuadtreeNode*>, morton_keys::MaxTreeDepth> m_nodes;

    static constexpr hash_t hash_grid_coord(grid_coord_t x, grid_coord_t y)
    {
        return (static_cast<hash_t>(x) << 32) + static_cast<hash_t>(y);
    }
    static constexpr grid_coord_t unhash_x(hash_t hash)
    {
        return hash >> 32;
    }
    static constexpr grid_coord_t unhash_y(hash_t hash)
    {
        return hash & std::numeric_limits<grid_coord_t>::max();
    }
};


} // namespace quadtree


#include "DepthMap.h"

namespace quadtree {
namespace depth_map {

const QuadtreeNode* DepthMap::get_node(int depth, transform::hash_t hash) const
{
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
const DepthMap::NodeContainer& DepthMap::get_nodes(int depth) const
{
    return m_nodes[depth];
}
void DepthMap::add_node(int depth, transform::grid_coord_t x, transform::grid_coord_t y, QuadtreeNode* node)
{
    auto hash = transform::hash_grid_coord(x, y);
    m_nodes[depth][hash] = node;
}
void DepthMap::remove_node(int depth, transform::grid_coord_t x, transform::grid_coord_t y)
{
    auto hash = transform::hash_grid_coord(x, y);
    m_nodes[depth].erase(hash);
}

} // namespace depth_map
} // namespace quadtree

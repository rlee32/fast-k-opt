#pragma once

#include <primitives.h>

#include <cstdint>
#include <limits>

namespace quadtree {
namespace depth_map {
namespace transform {

using hash_t = uint64_t;
using grid_coord_t = uint32_t;

inline hash_t hash_grid_coord(grid_coord_t x, grid_coord_t y)
{
    return (static_cast<hash_t>(x) << 32) + static_cast<hash_t>(y);
}
inline grid_coord_t unhash_x(hash_t hash)
{
    return hash >> 32;
}
inline grid_coord_t unhash_y(hash_t hash)
{
    return hash & ((static_cast<hash_t>(1) << 32) - 1);
    //return hash & std::numeric_limits<grid_coord_t>::max();
}

inline grid_coord_t quadrant_x(primitives::quadrant_t q)
{
    // assuming "N" curve; see morton_keys::interleave_coordinates for an explanation.
    switch(q)
    {
        case 0:
        case 1:
        {
            return 0;
        }
        case 2:
        case 3:
        {
            return 1;
        }
        default: return 0;
    }
}
inline grid_coord_t quadrant_y(primitives::quadrant_t q)
{
    // assuming "N" curve; see morton_keys::interleave_coordinates for an explanation.
    switch(q)
    {
        case 0:
        case 2:
        {
            return 0;
        }
        case 1:
        case 3:
        {
            return 1;
        }
        default: return 0;
    }
}

} // namespace transform
} // namespace depth_map
} // namespace quadtree

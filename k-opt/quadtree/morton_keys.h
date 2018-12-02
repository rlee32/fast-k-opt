#pragma once

// Morton keys are interleaved coordinates, which are integer reprentations of x, y coordinates normalized to [0,1].

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility> // pair
#include <vector>

namespace quadtree {
namespace morton_keys {

using MortonKey = uint64_t;

constexpr int MAX_LEVEL = 21; // maximum quadtree depth / level. Leave at least one bit for flags.
constexpr MortonKey MORTON_ONE = static_cast<MortonKey>(1);

inline MortonKey interleave_coordinates(double normalized_coordinate1, double normalized_coordinate2)
{
    using IntegerCoordinate = uint32_t;
    constexpr IntegerCoordinate IntegerCoordinateMax = static_cast<IntegerCoordinate>(1) << (MAX_LEVEL - 1); // to be multiplied by the normalized (0,1) coordinate.
    IntegerCoordinate c1 = static_cast<IntegerCoordinate>(IntegerCoordinateMax * normalized_coordinate1);
    IntegerCoordinate c2 = static_cast<IntegerCoordinate>(IntegerCoordinateMax * normalized_coordinate2);
    MortonKey morton_key = static_cast<MortonKey>(0);
    constexpr int bytes = sizeof(IntegerCoordinate);
    constexpr int bits = 8 * bytes;
    for (int i{bits - 1}; i >= 0; --i)
    {
        constexpr MortonKey MORTON_ONE = static_cast<MortonKey>(1);
        morton_key |= (c1 >> i) & MORTON_ONE;
        morton_key <<= 1;
        morton_key |= (c2 >> i) & MORTON_ONE;
        if (i != 0)
        {
            morton_key <<= 1;
        }
    }
    return morton_key;
}

inline std::vector<MortonKey> compute_point_morton_keys(const std::vector<double>& x, const std::vector<double>& y)
{
    // Get domain bounds
    double x_min = *std::min_element(x.begin(), x.end());
    double x_max = *std::max_element(x.begin(), x.end());
    double y_min = *std::min_element(y.begin(), y.end());
    double y_max = *std::max_element(y.begin(), y.end());

    double x_range = x_max - x_min;
    double y_range = y_max - y_min;

    // In this tree construction code we assume the points at within each node
    // have the same Morton Key prefix. So when a point is on the exact boundary,
    // it gets put into the quadrant it would go in if it was a small increment
    // larger (in either x or y). This is fine, EXCEPT at the root. There is no
    // next quadrant. So, we have to apply fudge factor to ranges to completely
    // capture boundary points within the root node.
    constexpr double RootNodeMargin = 0.00001;
    x_min -= RootNodeMargin * x_range;
    y_min -= RootNodeMargin * y_range;
    x_range *= 1 + 2 * RootNodeMargin;
    y_range *= 1 + 2 * RootNodeMargin;

    const size_t point_count = x.size();
    std::vector<MortonKey> point_morton_keys;
    for (size_t i{0}; i < point_count; ++i)
    {
        double x_normalized = (x[i] - x_min) / x_range;
        double y_normalized = (y[i] - y_min) / y_range;
        if (x_normalized < 0.0 or x_normalized > 1.0)
        {
            std::cout << "ERROR: out-of-bounds normalized x coordinate: " << x_normalized << std::endl;
        }
        if (y_normalized < 0.0 or y_normalized > 1.0)
        {
            std::cout << "ERROR: out-of-bounds normalized y coordinate: " << y_normalized << std::endl;
        }
        MortonKey morton_key = interleave_coordinates(x_normalized, y_normalized);
        // bitset<8*sizeof(morton_key.value())> morton_bits(morton_key.value());
        // cout << morton_bits.to_string().substr(22) << endl;
        std::pair<MortonKey, int> morton_key_pair(morton_key, i);
        point_morton_keys[i] = morton_key;
    }
    return point_morton_keys;
}

inline std::vector<MortonKey> ExtractLeadingQuadrants(MortonKey node_morton_key, int tree_level)
{
    constexpr MortonKey MORTON_ALL_ZEROS = static_cast<MortonKey>(0);
    constexpr MortonKey MORTON_ALL_ONES = ~MORTON_ALL_ZEROS;
    constexpr MortonKey MORTON_TWO = static_cast<MortonKey>(2);
    constexpr MortonKey MORTON_THREE = static_cast<MortonKey>(3);
    // Determine prefix mask.
    int suffix_bits = 2 * (MAX_LEVEL - tree_level - 1); // we subtract one because
    // the quadrants are one level down from the current tree_level_.
    MortonKey prefix_mask = MORTON_ALL_ONES << suffix_bits;

    // Obviously, we assume keys have the same prefix for a given node.
    MortonKey prefix = node_morton_key & prefix_mask;

    // now determine the quadrant morton number.
    MortonKey suffix01 = MORTON_ONE << (suffix_bits - 2);
    MortonKey suffix02 = MORTON_TWO << (suffix_bits - 2);
    MortonKey suffix03 = MORTON_THREE << (suffix_bits - 2);

    std::vector<MortonKey> quadrant_keys;
    quadrant_keys.push_back(prefix);
    quadrant_keys.push_back(prefix + suffix01);
    quadrant_keys.push_back(prefix + suffix02);
    quadrant_keys.push_back(prefix + suffix03);

    return quadrant_keys;
}

inline std::vector<int> segment_insertion_path(MortonKey key1, MortonKey key2)
{
    constexpr MortonKey MORTON_THREE = static_cast<MortonKey>(3); // quadrant mask.
    std::vector<int> path;
    // We skip i = 0 because that would simply lead to root comparison.
    for(int i = 1; i < MAX_LEVEL; ++i)
    {
        MortonKey level1 = key1 >> 2 * (MAX_LEVEL - i - 1);
        MortonKey level2 = key2 >> 2 * (MAX_LEVEL - i - 1);
        if (level1 == level2)
        {
            int quadrant = static_cast<int>(level1 & MORTON_THREE);
            path.push_back(quadrant);
        }
    }
    return path;
}

} // namespace morton_keys
} // namespace quadtree

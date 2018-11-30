#include "MortonKey.h"

namespace quadtree {

static const MortonKeyType MORTON_ALL_ZEROS = static_cast<MortonKeyType>(0);
static const MortonKeyType MORTON_ALL_ONES = ~MORTON_ALL_ZEROS;
static const MortonKeyType MORTON_ONE = static_cast<MortonKeyType>(1);
static const MortonKeyType MORTON_TWO = static_cast<MortonKeyType>(2);
static const MortonKeyType MORTON_THREE = static_cast<MortonKeyType>(3);

void MortonKey::Interleave(BinaryType binary_coordinate1, BinaryType binary_coordinate2)
{
    m_value = MORTON_ALL_ZEROS;
    int bytes = sizeof(binary_coordinate1);
    int bits = 8 * bytes;
    for (int i = bits-1; i >= 0; --i)
    {
        m_value |= (binary_coordinate1 >> i) & MORTON_ONE;
        m_value <<= 1;
        m_value |= (binary_coordinate2 >> i) & MORTON_ONE;
        if (i != 0)
        {
            m_value <<= 1;
        }
    }
}

std::vector<MortonKeyType> ExtractLeadingQuadrants(MortonKeyType node_morton_key, int tree_level)
{
    // Determine prefix mask.
    int suffix_bits = 2 * (MAX_LEVEL - tree_level - 1); // we subtract one because
    // the quadrants are one level down from the current tree_level_.
    MortonKeyType prefix_mask = MORTON_ALL_ONES << suffix_bits;

    // Obviously, we assume keys have the same prefix for a given node.
    MortonKeyType prefix = node_morton_key & prefix_mask;

    // now determine the quadrant morton number.
    MortonKeyType suffix01 = MORTON_ONE << (suffix_bits - 2);
    MortonKeyType suffix02 = MORTON_TWO << (suffix_bits - 2);
    MortonKeyType suffix03 = MORTON_THREE << (suffix_bits - 2);

    std::vector<MortonKeyType> quadrant_keys;
    quadrant_keys.push_back(prefix);
    quadrant_keys.push_back(prefix + suffix01);
    quadrant_keys.push_back(prefix + suffix02);
    quadrant_keys.push_back(prefix + suffix03);

    return quadrant_keys;
}

} // namespace quadtree

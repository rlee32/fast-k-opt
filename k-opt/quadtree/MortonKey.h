#pragma once

#include <utility>
#include <vector>

using BinaryType = unsigned int; // coordinate binary represenation.
using MortonKeyType = unsigned long; // consists of interleaved BinaryType. (TODO: ?)
constexpr int MAX_LEVEL = 21; //maximum quadtree depth / level. Leave at least one bit for flags.
constexpr BinaryType BINARY_TYPE_MAXIMUM = static_cast<BinaryType>(1) << (MAX_LEVEL - 1); // to be multiplied by the normalized (0,1) coordinate.

// Coordinates normalized to [0,1].
class MortonKey
{
public:
    MortonKey(int point_id, double normalized_coordinate1, double normalized_coordinate2)
      : m_point_id(point_id)
    {
        BinaryType binary_coordinate1 = static_cast<BinaryType>(BINARY_TYPE_MAXIMUM * normalized_coordinate1);
        BinaryType binary_coordinate2 = static_cast<BinaryType>(BINARY_TYPE_MAXIMUM * normalized_coordinate2);
        Interleave(binary_coordinate1, binary_coordinate2);
    }
    size_t point_id() const { return m_point_id; }
    MortonKeyType value() const { return m_value; }
private:
    MortonKeyType m_value{0}; // the morton key value.
    size_t m_point_id{0}; // the point to which this morton key corresponds.

    void Interleave(BinaryType binary_coordinate1, BinaryType binary_coordinate2);
};

std::vector<MortonKeyType> ExtractLeadingQuadrants(MortonKeyType node_morton_key, int tree_level);


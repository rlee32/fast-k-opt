#pragma once

// Keeps track of segment lengths at all tree depths.
// Fast insertion, removal, and querying of maximum lengths.

// Used to determine maximum search radius.

#include <primitives.h>

#include <array>
#include <set>

namespace quadtree {

class LengthTable
{
    using length_t = primitives::length_t;
    using depth_t = primitives::depth_t;
    using LengthContainer = std::multiset<length_t>;
    template <typename Container>
    using Table = std::array<Container, primitives::MaxTreeDepth>;
public:
    void insert(depth_t depth, length_t length);

    // Returns true if length was found and erased, false if not found.
    // Erases a single instance of length, not all instances (e.g. multiset::erase).
    bool erase_one(depth_t depth, length_t length);

    const LengthContainer& lengths(depth_t depth) const;

private:
    Table<LengthContainer> m_lengths;
};

} // namespace quadtree

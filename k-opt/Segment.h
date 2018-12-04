#pragma once

// This represents a straight line path between two adjacent cities.
// A tour is made of a number of segments equal to the number of cities.

#include "primitives.h"

#include <algorithm>
#include <cstdint>

struct Segment
{
    // "First" and "second" point is assumed consistent among all segments.
    primitives::point_id_t a{0}; // first point in traversal.
    primitives::point_id_t b{0}; // second point in traversal.
    primitives::length_t length{0};

    // For use in unordered_set.
    struct Hash
    {
        using hash_t = uint64_t;
        hash_t operator()(const Segment& s) const
        {
            static_assert(sizeof(hash_t) == sizeof(s.a) + sizeof(s.b));
            constexpr auto ShiftBits = 4 * sizeof(hash_t);
            static_assert(ShiftBits / 8 == sizeof(s.b));
            return (static_cast<hash_t>(s.a) << ShiftBits) + static_cast<hash_t>(s.b);
        }
    };
};

// For use in unordered_set.
inline bool operator==(const Segment& lhs, const Segment& rhs)
{
    return lhs.a == rhs.a and lhs.b == rhs.b;
}


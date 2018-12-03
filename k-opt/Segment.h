#pragma once

// This represents a straight line path between two adjacent cities.
// A tour is made of a number of segments equal to the number of cities.

#include "primitives.h"

#include <algorithm>
#include <cstdint>

struct Segment
{
    Segment(primitives::point_id_t a, primitives::point_id_t b, primitives::length_t length)
        : a(std::min(a, b)), b(std::max(a, b)), length(length) {}
    primitives::point_id_t a{0}; // lower point id.
    primitives::point_id_t b{0}; // higher point id.
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


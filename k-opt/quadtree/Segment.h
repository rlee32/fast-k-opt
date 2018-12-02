#pragma once

// This represents a path segment between two adjacent cities.
// A tour is made of a number of segments equal to the number of cities.

#include <cstdint>

struct Segment
{
    uint32_t a{0}; // lower point id.
    uint32_t b{0}; // higher point id.
    uint64_t length{0};

    // For use in unordered_set.
    struct Hash
    {
        uint64_t operator()(const Segment& s) const
        {
            static_assert(sizeof(s.a) * 8 == 32);
            return (static_cast<uint64_t>(s.a) << 32) + static_cast<uint64_t>(s.b);
        }
    };
};

// For use in unordered_set.
inline bool operator==(const Segment& lhs, const Segment& rhs)
{
    return lhs.a == rhs.a and lhs.b == rhs.b;
}


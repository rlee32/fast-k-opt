#pragma once

#include <Segment.h>

#include <vector>

// New segments are aceepted only if the distance criterion is satisfied with all other segments.

namespace optimizer {

class CliqueFilter
{
public:
    CliqueFilter(const Segment& s, primitives::space_t max_radius)
        : m_max_radius(max_radius)
    {
        m_segments.push_back(s);
    }

    // returns true if within max_radius of all other segments.
    bool insert(const Segment&)
    {
        return false;
    }

private:
    std::vector<Segment> m_segments;
    primitives::space_t m_max_radius{0};
};

} // namespace optimizer


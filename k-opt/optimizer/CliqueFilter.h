#pragma once

#include <Segment.h>
#include <primitives.h>

#include <vector>

// New segments are aceepted only if the distance criterion is satisfied with all other segments.

namespace optimizer {

class CliqueFilter
{
public:
    CliqueFilter(const Segment& s, primitives::space_t max_radius)
        : m_sq_max_radius(max_radius * max_radius)
    {
        m_segments.push_back(s);
    }

    // returns true if within max_radius of all other segments.
    bool insert(const Segment& new_segment)
    {
        for (const auto& s : m_segments)
        {
            if (too_far(new_segment, s))
            {
                return false;
            }
        }
        m_segments.push_back(new_segment);
        return true;
    }

private:
    std::vector<Segment> m_segments;
    primitives::space_t m_sq_max_radius{0};

    bool too_far(const Segment& s1, const Segment& s2) const
    {
        auto sq_dx = s1.xm - s2.xm;
        sq_dx *= sq_dx;
        if (sq_dx > m_sq_max_radius)
        {
            return true;
        }
        auto sq_dy = s1.ym - s2.ym;
        sq_dy *= sq_dy;
        if (sq_dy > m_sq_max_radius)
        {
            return true;
        }
        if (sq_dx + sq_dy > m_sq_max_radius)
        {
            return true;
        }
        return false;
    }
};

} // namespace optimizer


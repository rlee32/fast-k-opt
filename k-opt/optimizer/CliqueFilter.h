#pragma once

#include <Segment.h>
#include <primitives.h>

#include <algorithm>
#include <vector>

// New segments are aceepted only if the distance criterion is satisfied with all other segments.

namespace optimizer {

class CliqueFilter
{
public:
    CliqueFilter(const Segment& s, primitives::space_t max_radius, std::vector<primitives::length_t> max_lengths)
        : m_sq_max_radius(std::ceil(max_radius) * std::ceil(max_radius)), m_max_lengths(std::move(max_lengths))
    {
        m_segments.push_back(s);
        auto it = std::find(std::cbegin(m_max_lengths), std::cend(m_max_lengths), s.length);
        if (it != std::cend(m_max_lengths))
        {
            m_max_lengths.erase(it);
        }
    }

    // returns true if within max_radius of all other segments.
    bool insert(const Segment& new_segment)
    {
        auto sq_max_radius = m_sq_max_radius;
        if (new_segment.length < m_max_lengths.front())
        {
            auto diff = m_max_lengths.front() - new_segment.length;
            sq_max_radius = std::ceil(std::sqrt(m_sq_max_radius)) - diff;
            sq_max_radius *= sq_max_radius;
            if (m_sq_max_distance > sq_max_radius)
            {
                return false;
            }
        }
        for (const auto& s : m_segments)
        {
            if (too_far(new_segment, s, sq_max_radius))
            {
                return false;
            }
        }
        if (new_segment.length >= m_max_lengths.front())
        {
            // we assume m_max_lengths will be of sufficiently small size that a linear search is reasonable.
            auto it = std::find(std::cbegin(m_max_lengths), std::cend(m_max_lengths), new_segment.length);
            if (it != std::cend(m_max_lengths))
            {
                m_max_lengths.erase(it);
            }
        }
        m_segments.push_back(new_segment);
        m_sq_max_radius = sq_max_radius;
        return true;
    }

private:
    std::vector<Segment> m_segments;
    primitives::space_t m_sq_max_radius{0};
    primitives::space_t m_sq_max_distance{0};
    std::vector<primitives::length_t> m_max_lengths;

    bool too_far(const Segment& s1, const Segment& s2, primitives::space_t sq_max_radius)
    {
        auto sq_dx = std::floor(s1.xm - s2.xm);
        sq_dx *= sq_dx;
        if (sq_dx > sq_max_radius)
        {
            return true;
        }
        auto sq_dy = std::floor(s1.ym - s2.ym);
        sq_dy *= sq_dy;
        if (sq_dy > sq_max_radius)
        {
            return true;
        }
        auto sq_dist = sq_dx + sq_dy;
        if (sq_dist > sq_max_radius)
        {
            return true;
        }
        primitives::space_t sq_gap = std::floor(std::sqrt(sq_dist)) - (s1.length + s2.length) / 2.0;
        sq_gap *= sq_gap;
        if (sq_gap > sq_max_radius)
        {
            return true;
        }
        m_sq_max_distance = std::max(m_sq_max_distance, sq_dist);
        return false;
    }
};

} // namespace optimizer


#pragma once

#include "Segment.h"
#include "primitives.h"

#include <algorithm> // find
#include <vector>

struct SearchState
{
    SearchState() = default;
    SearchState(const Segment& segment)
    {
        push_back(segment);
    }

    std::vector<Segment> segments;
    std::vector<primitives::point_id_t> points;
    primitives::length_t length{0};
    primitives::length_t improvement{0};
    std::vector<Segment> new_segments;

    bool valid(const Segment& s) const
    {
        return std::find(points.begin(), points.end(), s.a) == points.end()
            and std::find(points.begin(), points.end(), s.b) == points.end();
    }
    void push_back(const Segment& s)
    {
        segments.push_back(s);
        points.push_back(s.a);
        points.push_back(s.b);
        length += s.length;
    }
    void pop_back()
    {
        const auto& s = segments.back();
        points.erase(std::find(points.begin(), points.end(), s.a));
        points.erase(std::find(points.begin(), points.end(), s.b));
        length -= s.length;
        segments.pop_back();
    }
    size_t size() const { return segments.size(); }
    bool empty() const { return segments.empty(); }
};



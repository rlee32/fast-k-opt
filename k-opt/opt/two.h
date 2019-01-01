#pragma once

#include <DistanceTable.h>
#include <SearchState.h>
#include <Segment.h>

#include <vector>

namespace opt {

inline void two(const std::vector<Segment>& ordered_segments
    , SearchState& current
    , SearchState& best
    , const DistanceTable& dt)
{
    // TODO: logarithmic distance table.
    const auto& s = ordered_segments;
    auto& ns = current.new_segments;
    ns.clear();
    ns.push_back({s[0].a, s[1].a, dt.compute_length(s[0].a, s[1].a)});
    if (ns[0].length >= current.length)
    {
        return;
    }
    ns.push_back({s[0].b, s[1].b, dt.compute_length(s[0].b, s[1].b)});
    auto new_length = ns[0].length + ns[1].length;
    if (new_length >= current.length)
    {
        return;
    }
    current.improvement = current.length - new_length;
    // Using >= or > below can make a difference in results!
    // It is possible to get multiple swap configurations with the same improvement.
    // All are qualitatively equivalent choices, but still can lead to divergence in later results.
    // The configuration chosen depends on the search path.
    // If >, the first configuration will be kept.
    // If >=, the last configuration will be chosen.
    if (current.improvement >= best.improvement)
    {
        best = current;
    }
}

} // namespace opt

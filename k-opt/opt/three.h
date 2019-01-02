#pragma once

#include <DistanceTable.h>
#include <SearchState.h>
#include <Segment.h>

#include <vector>

namespace opt {

inline void three(const std::vector<Segment>& ordered_segments
    , SearchState& current
    , SearchState& best
    , const DistanceTable& dt)
{
    auto& new_segments = current.new_segments;
    const auto& s1 = ordered_segments[0];
    const auto& s2 = ordered_segments[1];
    const auto& s3 = ordered_segments[2];
	auto edge_1a2a = dt.compute_length(s1.a, s2.a);
	auto edge_1b3a = dt.compute_length(s1.b, s3.a);
	auto edge_2b3b = dt.compute_length(s2.b, s3.b);
	auto new_length = edge_1a2a + edge_1b3a + edge_2b3b;
    auto minimum_length = current.length;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.b, s3.b, edge_2b3b, dt);
    }
	auto edge_1a2b = dt.compute_length(s1.a, s2.b);
	auto edge_2a3b = dt.compute_length(s2.a, s3.b);
	new_length = edge_1a2b + edge_1b3a + edge_2a3b;
    if (new_length < minimum_length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
    }
	auto edge_1b3b = dt.compute_length(s1.b, s3.b);
	auto edge_2a3a = dt.compute_length(s2.a, s3.a);
	new_length = edge_1a2b + edge_1b3b + edge_2a3a;
    if (new_length < minimum_length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
    }
	auto edge_1a3a = dt.compute_length(s1.a, s3.a);
	auto edge_1b2b = dt.compute_length(s1.b, s2.b);
	new_length = edge_1a3a + edge_1b2b + edge_2a3b;
    if (new_length < minimum_length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
    }
    if (minimum_length >= current.length)
    {
        return;
    }
    current.improvement = current.length - minimum_length;
    if (current.improvement >= best.improvement)
    {
        best = current;
    }
}


} // namespace opt

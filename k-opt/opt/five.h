#pragma once

// Max possible edge configurations: 384
// Valid edge configurations: 188
// 35 edge lengths to compute.

#include "DistanceTable.h"
#include "SearchState.h"
#include "Segment.h"
#include "primitives.h"

#include <vector>

namespace opt {

inline void five(
    const std::vector<Segment>& ordered_segments
    , SearchState& current
    , SearchState& best
    , const DistanceTable& dt)
{
    auto& new_segments = current.new_segments;
    auto minimum_length = current.length;
    primitives::length_t new_length{0};
    const auto& s1 = ordered_segments[0];
    const auto& s2 = ordered_segments[1];
    const auto& s3 = ordered_segments[2];
    const auto& s4 = ordered_segments[3];
    const auto& s5 = ordered_segments[4];
    auto edge_1a5a = dt.compute_length(s1.a, s5.a);
    auto edge_2b3b = dt.compute_length(s2.b, s3.b);
    auto edge_1a3b = dt.compute_length(s1.a, s3.b);
    auto edge_1a4b = dt.compute_length(s1.a, s4.b);
    auto edge_3a5b = dt.compute_length(s3.a, s5.b);
    auto edge_4a5a = dt.compute_length(s4.a, s5.a);
    auto edge_2a5a = dt.compute_length(s2.a, s5.a);
    auto edge_1b5a = dt.compute_length(s1.b, s5.a);
    auto edge_2a4b = dt.compute_length(s2.a, s4.b);
    auto edge_1a2a = dt.compute_length(s1.a, s2.a);
    auto edge_2a3a = dt.compute_length(s2.a, s3.a);
    auto edge_1a2b = dt.compute_length(s1.a, s2.b);
    auto edge_4a5b = dt.compute_length(s4.a, s5.b);
    auto edge_2a3b = dt.compute_length(s2.a, s3.b);
    auto edge_3a4a = dt.compute_length(s3.a, s4.a);
    auto edge_1a3a = dt.compute_length(s1.a, s3.a);
    auto edge_1b4a = dt.compute_length(s1.b, s4.a);
    auto edge_2b4a = dt.compute_length(s2.b, s4.a);
    auto edge_1b3a = dt.compute_length(s1.b, s3.a);
    auto edge_1b4b = dt.compute_length(s1.b, s4.b);
    auto edge_1b5b = dt.compute_length(s1.b, s5.b);
    auto edge_1a4a = dt.compute_length(s1.a, s4.a);
    auto edge_3a4b = dt.compute_length(s3.a, s4.b);
    auto edge_2b4b = dt.compute_length(s2.b, s4.b);
    auto edge_3b5a = dt.compute_length(s3.b, s5.a);
    auto edge_2b5b = dt.compute_length(s2.b, s5.b);
    auto edge_2a5b = dt.compute_length(s2.a, s5.b);
    auto edge_1b3b = dt.compute_length(s1.b, s3.b);
    auto edge_2b5a = dt.compute_length(s2.b, s5.a);
    auto edge_3b5b = dt.compute_length(s3.b, s5.b);
    auto edge_3b4b = dt.compute_length(s3.b, s4.b);
    auto edge_3a5a = dt.compute_length(s3.a, s5.a);
    auto edge_1b2b = dt.compute_length(s1.b, s2.b);
    auto edge_4b5b = dt.compute_length(s4.b, s5.b);
    auto edge_2a4a = dt.compute_length(s2.a, s4.a);
    new_length = edge_1a2a + edge_1b3a + edge_2b4a + edge_3b5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[3] = Segment(s3.b, s5.a, edge_3b5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a2a + edge_1b3a + edge_2b4b + edge_3b5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[3] = Segment(s3.b, s5.a, edge_3b5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2a + edge_1b3a + edge_2b4b + edge_3b5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[3] = Segment(s3.b, s5.b, edge_3b5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a2a + edge_1b3a + edge_2b5a + edge_3b4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[3] = Segment(s3.b, s4.b, edge_3b4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2a + edge_1b3b + edge_2b4a + edge_3a5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a2a + edge_1b3b + edge_2b4b + edge_3a5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a2a + edge_1b3b + edge_2b5a + edge_3a4a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a2a + edge_1b3b + edge_2b5b + edge_3a4b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a2a + edge_1b4a + edge_2b3b + edge_3a5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a2a + edge_1b4a + edge_2b4b + edge_3a5b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a2a + edge_1b4a + edge_2b5a + edge_3a5b + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a2a + edge_1b4a + edge_2b5b + edge_3a4b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a2a + edge_1b4a + edge_2b5b + edge_3a5a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a2a + edge_1b4b + edge_2b3b + edge_3a5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2a + edge_1b4b + edge_2b3b + edge_3a5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a2a + edge_1b4b + edge_2b4a + edge_3a5a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a2a + edge_1b4b + edge_2b4a + edge_3a5b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a2a + edge_1b4b + edge_2b5a + edge_3a4a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a2a + edge_1b4b + edge_2b5b + edge_3a4a + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a2a + edge_1b5a + edge_2b3b + edge_3a4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2a + edge_1b5a + edge_2b4a + edge_3a4b + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a2a + edge_1b5a + edge_2b4a + edge_3a5b + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a2a + edge_1b5a + edge_2b4b + edge_3a4a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.a, edge_1a2a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a2b + edge_1b3a + edge_2a4a + edge_3b5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.b, s5.a, edge_3b5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a2b + edge_1b3a + edge_2a4b + edge_3b5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.b, s5.a, edge_3b5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2b + edge_1b3a + edge_2a4b + edge_3b5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.b, s5.b, edge_3b5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a2b + edge_1b3a + edge_2a5a + edge_3b4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s3.b, s4.b, edge_3b4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2b + edge_1b3b + edge_2a4b + edge_3a5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2b + edge_1b3b + edge_2a5a + edge_3a4a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a2b + edge_1b3b + edge_2a5a + edge_3a4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2b + edge_1b3b + edge_2a5b + edge_3a4b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a2b + edge_1b4a + edge_2a3a + edge_3b5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s3.b, s5.a, edge_3b5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a2b + edge_1b4a + edge_2a4b + edge_3a5a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a2b + edge_1b4a + edge_2a5a + edge_3a4b + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a2b + edge_1b4a + edge_2a5b + edge_3a4b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a2b + edge_1b4a + edge_2a5b + edge_3a5a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a2b + edge_1b4b + edge_2a3a + edge_3b5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s3.b, s5.a, edge_3b5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2b + edge_1b4b + edge_2a3a + edge_3b5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s3.b, s5.b, edge_3b5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a2b + edge_1b4b + edge_2a3b + edge_3a5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2b + edge_1b4b + edge_2a4a + edge_3a5a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a2b + edge_1b4b + edge_2a5b + edge_3a4a + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a2b + edge_1b5a + edge_2a3a + edge_3b4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s3.b, s4.b, edge_3b4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2b + edge_1b5a + edge_2a3b + edge_3a4a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a2b + edge_1b5a + edge_2a3b + edge_3a4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a2b + edge_1b5a + edge_2a4a + edge_3a4b + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a2b + edge_1b5b + edge_2a3b + edge_3a4b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a2b + edge_1b5b + edge_2a4a + edge_3a4b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a2b + edge_1b5b + edge_2a4a + edge_3a5a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a2b + edge_1b5b + edge_2a4b + edge_3a4a + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s2.b, edge_1a2b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a3a + edge_1b2b + edge_2a4a + edge_3b5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.b, s5.a, edge_3b5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3a + edge_1b2b + edge_2a4b + edge_3b5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.b, s5.a, edge_3b5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a3a + edge_1b2b + edge_2a4b + edge_3b5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.b, s5.b, edge_3b5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3a + edge_1b2b + edge_2a5a + edge_3b4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s3.b, s4.b, edge_3b4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a3a + edge_1b3b + edge_2a4b + edge_2b5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a3a + edge_1b3b + edge_2a5a + edge_2b4a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3a + edge_1b3b + edge_2a5a + edge_2b4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a3a + edge_1b3b + edge_2a5b + edge_2b4b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3a + edge_1b4a + edge_2a4b + edge_2b5a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a3a + edge_1b4a + edge_2a5a + edge_2b3b + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3a + edge_1b4a + edge_2a5a + edge_2b4b + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a3a + edge_1b4a + edge_2a5b + edge_2b4b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a3a + edge_1b4a + edge_2a5b + edge_2b5a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a3a + edge_1b4b + edge_2a3b + edge_2b5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a3a + edge_1b4b + edge_2a4a + edge_2b5a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a3a + edge_1b4b + edge_2a5b + edge_2b3b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3a + edge_1b4b + edge_2a5b + edge_2b4a + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a3a + edge_1b5a + edge_2a3b + edge_2b4a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3a + edge_1b5a + edge_2a3b + edge_2b4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a3a + edge_1b5a + edge_2a4a + edge_2b3b + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3a + edge_1b5a + edge_2a4a + edge_2b4b + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a3a + edge_1b5a + edge_2a5b + edge_2b4a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a3a + edge_1b5b + edge_2a3b + edge_2b4b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3a + edge_1b5b + edge_2a4a + edge_2b4b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a3a + edge_1b5b + edge_2a4a + edge_2b5a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a3a + edge_1b5b + edge_2a4b + edge_2b3b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3a + edge_1b5b + edge_2a4b + edge_2b4a + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a3a + edge_1b5b + edge_2a5a + edge_2b4a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.a, edge_1a3a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a3b + edge_1b2b + edge_2a4a + edge_3a5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3b + edge_1b2b + edge_2a4b + edge_3a5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3b + edge_1b2b + edge_2a5a + edge_3a4a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3b + edge_1b2b + edge_2a5b + edge_3a4b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3b + edge_1b3a + edge_2a4a + edge_2b5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3b + edge_1b3a + edge_2a4b + edge_2b5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3b + edge_1b3a + edge_2a5a + edge_2b4a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3b + edge_1b3a + edge_2a5b + edge_2b4b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3b + edge_1b4a + edge_2a3a + edge_2b5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3b + edge_1b4a + edge_2a4b + edge_2b5a + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a3b + edge_1b4a + edge_2a4b + edge_2b5b + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a3b + edge_1b4a + edge_2a5a + edge_2b4b + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a3b + edge_1b4a + edge_2a5a + edge_2b5b + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a3b + edge_1b4b + edge_2a3a + edge_2b5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3b + edge_1b4b + edge_2a4a + edge_2b5a + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a3b + edge_1b4b + edge_2a4a + edge_2b5b + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a3b + edge_1b4b + edge_2a5b + edge_2b4a + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a3b + edge_1b4b + edge_2a5b + edge_2b5a + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a3b + edge_1b5a + edge_2a3a + edge_2b4a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a3b + edge_1b5a + edge_2a4a + edge_2b4b + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a3b + edge_1b5a + edge_2a4a + edge_2b5b + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a3b + edge_1b5a + edge_2a5b + edge_2b4a + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a3b + edge_1b5a + edge_2a5b + edge_2b4b + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a3b + edge_1b5b + edge_2a3a + edge_2b4b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a3b + edge_1b5b + edge_2a4b + edge_2b4a + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a3b + edge_1b5b + edge_2a4b + edge_2b5a + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a3b + edge_1b5b + edge_2a5a + edge_2b4a + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a3b + edge_1b5b + edge_2a5a + edge_2b4b + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s3.b, edge_1a3b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a4a + edge_1b2b + edge_2a3b + edge_3a5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a4a + edge_1b2b + edge_2a4b + edge_3a5b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4a + edge_1b2b + edge_2a5a + edge_3a5b + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a4a + edge_1b2b + edge_2a5b + edge_3a4b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4a + edge_1b2b + edge_2a5b + edge_3a5a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a4a + edge_1b3a + edge_2a3b + edge_2b5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a4a + edge_1b3a + edge_2a4b + edge_2b5b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4a + edge_1b3a + edge_2a5a + edge_2b3b + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a4a + edge_1b3a + edge_2a5a + edge_2b5b + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a4a + edge_1b3a + edge_2a5b + edge_2b4b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4a + edge_1b3a + edge_2a5b + edge_2b5a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a4a + edge_1b3b + edge_2a3a + edge_2b5a + edge_4b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s4.b, s5.b, edge_4b5b, dt);
    }
    new_length = edge_1a4a + edge_1b3b + edge_2a4b + edge_2b5a + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a4a + edge_1b3b + edge_2a4b + edge_2b5b + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a4a + edge_1b3b + edge_2a5a + edge_2b4b + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a4a + edge_1b3b + edge_2a5a + edge_2b5b + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a4a + edge_1b4b + edge_2a3a + edge_2b5b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4a + edge_1b4b + edge_2a3b + edge_2b5a + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a4a + edge_1b4b + edge_2a3b + edge_2b5b + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a4a + edge_1b4b + edge_2a5b + edge_2b3b + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a4a + edge_1b5a + edge_2a3a + edge_2b5b + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a4a + edge_1b5a + edge_2a3b + edge_2b4b + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a4a + edge_1b5a + edge_2a3b + edge_2b5b + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a4a + edge_1b5a + edge_2a5b + edge_2b3b + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a4a + edge_1b5b + edge_2a3a + edge_2b4b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4a + edge_1b5b + edge_2a3a + edge_2b5a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a4a + edge_1b5b + edge_2a4b + edge_2b3b + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a4a + edge_1b5b + edge_2a5a + edge_2b3b + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.a, edge_1a4a, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a4b + edge_1b2b + edge_2a3b + edge_3a5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a4b + edge_1b2b + edge_2a3b + edge_3a5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a4b + edge_1b2b + edge_2a4a + edge_3a5a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s5.a, edge_3a5a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a4b + edge_1b2b + edge_2a4a + edge_3a5b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4b + edge_1b2b + edge_2a5a + edge_3a4a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a4b + edge_1b2b + edge_2a5b + edge_3a4a + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4b + edge_1b3a + edge_2a3b + edge_2b5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a4b + edge_1b3a + edge_2a3b + edge_2b5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a4b + edge_1b3a + edge_2a4a + edge_2b5a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a4b + edge_1b3a + edge_2a4a + edge_2b5b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4b + edge_1b3a + edge_2a5a + edge_2b3b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a4b + edge_1b3a + edge_2a5a + edge_2b4a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a4b + edge_1b3a + edge_2a5b + edge_2b3b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a4b + edge_1b3a + edge_2a5b + edge_2b4a + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4b + edge_1b3b + edge_2a3a + edge_2b5a + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a4b + edge_1b3b + edge_2a3a + edge_2b5b + edge_4a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s4.a, s5.a, edge_4a5a, dt);
    }
    new_length = edge_1a4b + edge_1b3b + edge_2a5a + edge_2b4a + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a4b + edge_1b3b + edge_2a5a + edge_2b5b + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a4b + edge_1b3b + edge_2a5b + edge_2b4a + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a4b + edge_1b3b + edge_2a5b + edge_2b5a + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a4b + edge_1b4a + edge_2a3a + edge_2b5a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a4b + edge_1b4a + edge_2a3a + edge_2b5b + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4b + edge_1b4a + edge_2a5a + edge_2b3b + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.a, edge_2a5a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a4b + edge_1b4a + edge_2a5b + edge_2b3b + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a4b + edge_1b5a + edge_2a3a + edge_2b4a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a4b + edge_1b5a + edge_2a3b + edge_2b4a + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a4b + edge_1b5a + edge_2a3b + edge_2b5b + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a4b + edge_1b5a + edge_2a4a + edge_2b3b + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s5.a, edge_1b5a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a4b + edge_1b5b + edge_2a3a + edge_2b4a + edge_3b5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s5.a, edge_3b5a, dt);
    }
    new_length = edge_1a4b + edge_1b5b + edge_2a3b + edge_2b4a + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a4b + edge_1b5b + edge_2a3b + edge_2b5a + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.a, edge_2b5a, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a4b + edge_1b5b + edge_2a4a + edge_2b3b + edge_3a5a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s4.b, edge_1a4b, dt);
        new_segments[1] = Segment(s1.b, s5.b, edge_1b5b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s5.a, edge_3a5a, dt);
    }
    new_length = edge_1a5a + edge_1b2b + edge_2a3b + edge_3a4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a5a + edge_1b2b + edge_2a4a + edge_3a4b + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s4.b, edge_3a4b, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a5a + edge_1b2b + edge_2a4a + edge_3a5b + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s3.a, s5.b, edge_3a5b, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a5a + edge_1b2b + edge_2a4b + edge_3a4a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s2.b, edge_1b2b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s3.a, s4.a, edge_3a4a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a5a + edge_1b3a + edge_2a3b + edge_2b4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a5a + edge_1b3a + edge_2a4a + edge_2b4b + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a5a + edge_1b3a + edge_2a4a + edge_2b5b + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a5a + edge_1b3a + edge_2a4b + edge_2b3b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a5a + edge_1b3a + edge_2a4b + edge_2b4a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a5a + edge_1b3a + edge_2a5b + edge_2b4a + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.a, edge_1b3a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a5a + edge_1b3b + edge_2a3a + edge_2b4b + edge_4a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s4.a, s5.b, edge_4a5b, dt);
    }
    new_length = edge_1a5a + edge_1b3b + edge_2a4b + edge_2b4a + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a5a + edge_1b3b + edge_2a4b + edge_2b5b + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a5a + edge_1b3b + edge_2a5b + edge_2b4a + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a5a + edge_1b3b + edge_2a5b + edge_2b4b + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s3.b, edge_1b3b, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a5a + edge_1b4a + edge_2a3a + edge_2b4b + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s4.b, edge_2b4b, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a5a + edge_1b4a + edge_2a3a + edge_2b5b + edge_3b4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.b, s4.b, edge_3b4b, dt);
    }
    new_length = edge_1a5a + edge_1b4a + edge_2a4b + edge_2b3b + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s4.b, edge_2a4b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a5a + edge_1b4a + edge_2a5b + edge_2b3b + edge_3a4b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s4.a, edge_1b4a, dt);
        new_segments[2] = Segment(s2.a, s5.b, edge_2a5b, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s4.b, edge_3a4b, dt);
    }
    new_length = edge_1a5a + edge_1b4b + edge_2a3a + edge_2b4a + edge_3b5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.a, edge_2a3a, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.b, s5.b, edge_3b5b, dt);
    }
    new_length = edge_1a5a + edge_1b4b + edge_2a3b + edge_2b4a + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s4.a, edge_2b4a, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
    }
    new_length = edge_1a5a + edge_1b4b + edge_2a3b + edge_2b5b + edge_3a4a;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s3.b, edge_2a3b, dt);
        new_segments[3] = Segment(s2.b, s5.b, edge_2b5b, dt);
        new_segments[4] = Segment(s3.a, s4.a, edge_3a4a, dt);
    }
    new_length = edge_1a5a + edge_1b4b + edge_2a4a + edge_2b3b + edge_3a5b;
    if (new_length < current.length)
    {
        minimum_length = new_length;
        new_segments[0] = Segment(s1.a, s5.a, edge_1a5a, dt);
        new_segments[1] = Segment(s1.b, s4.b, edge_1b4b, dt);
        new_segments[2] = Segment(s2.a, s4.a, edge_2a4a, dt);
        new_segments[3] = Segment(s2.b, s3.b, edge_2b3b, dt);
        new_segments[4] = Segment(s3.a, s5.b, edge_3a5b, dt);
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

#pragma once

// This represents a path segment between two adjacent cities.
// A tour is made of a number of segments equal to the number of cities.

template <typename Container>
struct Segment
{
    using cost_t = long int;

    int start_city{-1}; // index of the starting city of this segment.
    int end_city{-1}; // index of the ending city of this segment.
    int order{-1}; // The order of this segment in the global tour.
    cost_t length{0}; // length (or cost) of this segment.
    // The coordinates of the bisecting point. TODO: may not be needed.
    double center_x{0};
    double center_y{0};
    // The current owner of this segment.
    const Container* node{nullptr};
};

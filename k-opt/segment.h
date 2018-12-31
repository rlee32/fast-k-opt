#pragma once

#include "DistanceTable.h"
#include "Segment.h"
#include "aliases.h"
#include "primitives.h"

namespace segment {

inline primitives::space_t x_center(const Segment& s, const DistanceTable& dt)
{
    return 0.5 * (dt.x(s.a) + dt.x(s.b));
}
inline primitives::space_t y_center(const Segment& s, const DistanceTable& dt)
{
    return 0.5 * (dt.y(s.a) + dt.y(s.b));
}

} // namespace segment

#pragma once

#include <cstdint>

namespace primitives {

using length_t = uint64_t; // as in Segment lengths.
using point_id_t = uint32_t;
using space_t = double; // as in x, y coordinates.
using depth_t = uint8_t; // as in maximum quadtree depth.
using quadrant_t = uint8_t; // as in quadtree quadrant index.

} // namespace primitives


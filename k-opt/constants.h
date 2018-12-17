#pragma once

#include "primitives.h"

namespace constants {

constexpr auto InvalidPoint{std::numeric_limits<primitives::point_id_t>::max()};
constexpr primitives::depth_t MaxTreeDepth{21}; // maximum quadtree depth / level.
constexpr primitives::depth_t DepthEnd{21}; // number of tree levels, or 1 + the maximum depth index. Might want to leave at least one bit for morton key flags.

constexpr bool naive_mode{false};



} // namespace constants

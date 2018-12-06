#pragma once

#include "primitives.h"

#include <array>
#include <algorithm> // min_element, max_element
#include <vector>
#include <ostream>

namespace quadtree {

class Domain
{
public:
    Domain(const std::vector<primitives::space_t>& x, const std::vector<primitives::space_t>& y)
    {
        // Get domain bounds
        m_xmin = *std::min_element(x.begin(), x.end());
        primitives::space_t xmax = *std::max_element(x.begin(), x.end());
        m_ymin = *std::min_element(y.begin(), y.end());
        primitives::space_t ymax = *std::max_element(y.begin(), y.end());
        primitives::space_t xrange = xmax - m_xmin;
        primitives::space_t yrange = ymax - m_ymin;
        // In the quadtree we assume the points at within each node
        // have the same Morton Key prefix. So when a point is on the exact boundary,
        // it gets put into the quadrant it would go in if it was a small increment
        // larger (in either x or y). This is fine, EXCEPT at the root. There is no
        // next quadrant. So, we have to apply fudge factor to ranges to completely
        // capture boundary points within the root node.
        constexpr primitives::space_t RootNodeMargin = 0.00001;
        m_xmin -= RootNodeMargin * xrange;
        m_ymin -= RootNodeMargin * yrange;
        xrange *= 1 + 2 * RootNodeMargin;
        yrange *= 1 + 2 * RootNodeMargin;
        size_t grid_dim{1};
        for (size_t depth{0}; depth < primitives::MaxTreeDepth; ++depth)
        {
            m_xdim[depth] = xrange / static_cast<primitives::space_t>(grid_dim);
            m_ydim[depth] = yrange / static_cast<primitives::space_t>(grid_dim);
            grid_dim <<= 1;
        }
    }
    primitives::space_t xmin() const { return m_xmin; }
    primitives::space_t ymin() const { return m_ymin; }
    primitives::space_t xdim(int depth) const { return m_xdim[depth]; }
    primitives::space_t ydim(int depth) const { return m_ydim[depth]; }

private:
    primitives::space_t m_xmin{0};
    primitives::space_t m_ymin{0};
    std::array<primitives::space_t, primitives::MaxTreeDepth> m_xdim; // x-dimension of boxes.
    std::array<primitives::space_t, primitives::MaxTreeDepth> m_ydim; // y-dimension of boxes.
};

} // namespace quadtree

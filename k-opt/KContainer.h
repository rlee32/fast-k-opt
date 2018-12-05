#pragma once

// Keeps the highest k sequentially-inserted segment lengths.
// Values can be repeating.

#include "primitives.h"

#include <set>
#include <numeric> // accumulate

class KContainer
{
    // These aliases can be template parameters if this class has more than one application.
    using Value = primitives::length_t;
    using ValueContainer = std::multiset<Value>;
public:
    KContainer(int k) : m_k(k) {}

    // Only returns false when value was too small to be inserted.
    bool insert(const Value& v)
    {
        // insert if under capacity.
        if (m_values.size() < m_k)
        {
            m_values.insert(v);
            return true;
        }
        // reject if too small.
        auto b = m_values.begin();
        if (v <= *b)
        {
            return false;
        }
        // evict smallest (and only one element), then insert new value.
        m_values.erase(b);
        m_values.insert(v);
        return true;
    }
    const ValueContainer& values() const { return m_values; }
    Value sum() const
    {
        if (m_values.size() < m_k)
        {
            return 0; // this means not enough segments to make a comparison anyway.
        }
        return std::accumulate(m_values.cbegin(), m_values.cend(), 0);
    }

private:
    const size_t m_k{0}; // maximum values to hold.
    ValueContainer m_values;
};

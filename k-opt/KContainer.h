#pragma once

// Keeps the highest k sequentially-inserted segment lengths.
// Values can be repeating.

#include "primitives.h"

#include <iterator> // next
#include <set>
#include <numeric> // accumulate

template <typename Value = primitives::length_t>
class KContainer
{
    // These aliases can be template parameters if this class has more than one application.
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
    Value kopt_sum() const
    {
        if (m_values.size() < m_k)
        {
            return 0; // this means not enough segments to make a comparison.
        }
        auto it = m_values.cbegin();
        // sum half of two smallest values.
        auto sum = *it;
        sum += *(++it);
        sum += 1; // account for truncation.
        sum /= 2;
        // sum the rest.
        sum += std::accumulate(++it, m_values.cend(), 0);
        return sum;
    }

private:
    const size_t m_k{0}; // maximum values to hold.
    ValueContainer m_values;
};

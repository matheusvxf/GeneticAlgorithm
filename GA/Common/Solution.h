#pragma once

#include <vector>
#include <bitset>

#include "Common.h"

class BitArray
{
    typedef std::vector< std::bitset< 64 > > BitArray_t;

    BitArray_t array_;
    uint32_t size_; // Number of bits

public:
    BitArray();
    BitArray(const BitArray &bit_array);

    uint32_t set_size(uint32_t size);
    inline uint32_t size() const { return size_; }
    inline void assign(BitArray_t::iterator begin, BitArray_t::iterator end) { array_.assign(begin, end); }

    inline bit get(uint32_t i) const
    {
        int word = i / 64;
        int bit = i % 64;
        return array_[word][bit];
    }

    inline bit set(uint32_t i, bit value)
    {
        int word = i / 64;
        int bit = i % 64;
        return array_[word][bit] = value;
    }

    inline bit flip(uint32_t i)
    {
        int word = i / 64;
        int bit = i % 64;
        return array_[word][bit] = ~array_[word][bit];
    }

    inline bit set_random(uint32_t i)
    {
        int word = i / 64;
        int bit = i % 64;
        int r = (rand() % 100);
        return array_[word][bit] = r < 50 ? 0 : 1;
    }
};


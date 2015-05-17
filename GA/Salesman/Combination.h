#pragma once

#include <set>
#include <bitset>

class Combination
{
    std::bitset< 64 > mask_;
    std::bitset< 64 > combination_;
    int num_bits_, sub_set_size_;
    int begin_, end_, last_bit_;
public:
    Combination(std::set< int > &S, int subset_size);
    ~Combination();

    bool next_combination();
};


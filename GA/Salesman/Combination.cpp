#include "Combination.h"

#include "Common.h"

Combination::Combination(std::set< int > &S, int sub_set_size)
{
    num_bits_ = 64;
    sub_set_size_ = sub_set_size;
    begin_ = *S.begin();
    foreach(S, s)
    {
        mask_[*s] = 1;
        if (sub_set_size > 0)
        {
            combination_[*s] = 1;
            end_ = *s;
            sub_set_size--;
        }
        last_bit_ = *s;
    }
}


Combination::~Combination()
{
}

bool Combination::next_combination()
{
    if (begin_ == end_)
        return false;
    while (begin_ >= end_)
    {
        int old_end = end_;
        end_++;
        while (end_ <= last_bit_ && mask_[end_] == 0) end_++;
        
        if (end_ > last_bit_)
        {
            end_ = old_end - 1;
            last_bit_ = end_;
            while (begin_ >= end_ && combination_[end_] != 0) end_--;
        }
        else
        {
            if (old_end == begin_)
                begin_ = end_;
            combination_[end_] = 1;
            combination_[old_end] = 0;
        }
    }

    if (begin_ == end_)
        return false;
    else
        return true;
}
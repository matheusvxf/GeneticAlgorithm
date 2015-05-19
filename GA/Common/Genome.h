#pragma once

#include <vector>

#include "Common.h"

class Gene
{
public:
    Gene();
    virtual ~Gene();

    virtual Gene& Mutate() = 0;
    virtual Gene& set_random() = 0;
    virtual Gene* clone() const = 0;
};

class Genome
{
protected:
    typedef std::vector< Gene* > GeneArray;

    GeneArray gene_;
    uint32_t size_; // Number of bits

public:
    Genome();
    Genome(uint32_t size);
    Genome(const Genome &genome);
    virtual ~Genome();

    uint32_t set_size(uint32_t size);
    inline uint32_t size() const { return size_; }

    inline Gene& get(uint32_t i);
    inline Gene& set(uint32_t i, Gene& value);
    virtual inline Genome& randomize();
    virtual inline Gene& set_random(uint32_t i);
    virtual inline Gene& Mutate(uint32_t i);

    virtual Gene *RandomGeneFactory() = 0;
    virtual Genome *clone() const = 0;
};

inline Gene& Genome::get(uint32_t i)
{
    return *gene_[i];
}

inline Gene& Genome::set(uint32_t i, Gene& value)
{
    return *gene_[i] = value;
}

inline Gene& Genome::Mutate(uint32_t i)
{
    return gene_[i]->Mutate();
}

inline Genome& Genome::randomize()
{
    if (gene_.size() != 0)
    {
        foreach(gene_, it)
            delete *it;
    }

    gene_.resize(size_);
    for (uint32_t i = 0; i < size_; ++i)
    {
        gene_[i] = RandomGeneFactory();
    }

    return *this;
}

inline Gene& Genome::set_random(uint32_t i)
{
    return gene_[i]->set_random();
}




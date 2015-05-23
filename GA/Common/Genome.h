#pragma once

#include <vector>

#include "Common.h"

class GeneticAlgorithm;

class Gene
{
public:
    Gene();
    virtual ~Gene();

    //virtual Gene& Mutate() = 0;
    //virtual Gene& set_random() = 0;
    virtual Gene* clone() const = 0;
};

class IGeneIndependent : public Gene
{
public:
    virtual Gene& Mutate() = 0;
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

    inline uint32_t size() const { return size_; }

    inline Gene& gene(uint32_t i);
    inline Gene& set_gene(uint32_t i, Gene& value);
    virtual Genome& Randomize(GeneticAlgorithm &algorithm_manager);
    virtual uint32_t set_size(uint32_t size);

    virtual Gene *RandomGeneFactory() = 0;
    virtual Genome *clone() const = 0;
};

class IGenomeGeneIndependent : public Genome
{
public:
    virtual Gene& Mutate(uint32_t i);
};

inline Gene& Genome::gene(uint32_t i)
{
    return *gene_[i];
}

inline Gene& Genome::set_gene(uint32_t i, Gene& value)
{
    return *gene_[i] = value;
}

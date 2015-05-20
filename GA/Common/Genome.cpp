#include "Genome.h"

Gene::Gene() {}

Gene::~Gene() {}

Genome::Genome() : Genome(kGenomeSize) {}

Genome::Genome(uint32_t size) : size_(size) {}

Genome::Genome(const Genome& genome) : size_(genome.size_)
{
    gene_.resize(size_);
    for (uint32_t i = 0; i < size_; ++i)
        gene_[i] = genome.gene_[i]->clone();
}

Genome::~Genome()
{
    foreach(gene_, it)
        delete *it;
}

uint32_t Genome::set_size(uint32_t size)
{
    gene_.resize(size);
    return size_ = size;
}


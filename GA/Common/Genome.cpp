#include "Genome.h"


IGenome::IGenome() : IGenome(kGenomeSize) {}

IGenome::IGenome(uint32_t size) : size_(size) {}

IGenome::IGenome(const IGenome& genome) : size_(genome.size_)
{
    gene_.resize(size_);
    for (uint32_t i = 0; i < size_; ++i)
        gene_[i] = genome.gene_[i]->clone();
}

IGenome::~IGenome()
{
    foreach(gene_, it)
        delete *it;
}

uint32_t IGenome::set_size(uint32_t size)
{
    gene_.resize(size);
    return size_ = size;
}


IGenome& IGenome::Randomize()
{
    gene_->clear();
    gene_->resize(size_);

    for (uint32_t i = 0; i < size_; ++i)
        set_gene(i, *RandomGeneFactory());

    return *this;
}


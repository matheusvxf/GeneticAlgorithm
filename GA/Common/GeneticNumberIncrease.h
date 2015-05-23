#pragma once

#include "GeneticAlgorithm.h"
#include "Genome.h"

class NumberGene : public Gene
{
    typedef bool Bit;

    Bit bit_;

    virtual Gene& Mutate();
    virtual Gene& set_random();
    virtual Gene* clone() const;

public:
    NumberGene();
    NumberGene(const NumberGene& number);
    Bit bit() { return bit_; }
};

class NumberGenome : public Genome
{
public:
    NumberGenome(uint32_t size);
    NumberGenome(const NumberGenome& genome);

    Gene *RandomGeneFactory() { return new NumberGene(); };
    Genome *clone() const;
};

class NumberSolution : public IHasInvidualMutation
{
public:
    NumberSolution();
    NumberSolution(const NumberSolution& solution);

    virtual Solution* clone() const;

    virtual Fitness CalcFitness(GeneticAlgorithm &manager);
    
};

class GeneticNumberIncrease : public GeneticAlgorithm
{
public:
    GeneticNumberIncrease();
    virtual ~GeneticNumberIncrease();
};


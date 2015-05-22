#pragma once

#include "GeneticAlgorithm.h"


class TSPGene : public Gene
{
    typedef bool Bit;

    Bit bit_;

    virtual Gene& Mutate();
    virtual Gene& set_random();
    virtual Gene* clone() const;

public:
    TSPGene();
    TSPGene(const TSPGene& gene);
    inline Bit bit() { return bit_; }
};

class TSPGenome : public Genome
{
public:
    TSPGenome(uint32_t size);
    TSPGenome(const TSPGenome& genome);

    Gene *RandomGeneFactory() { return new TSPGene(); };
    Genome *clone() const;
};

class TSPSolution : public GeneticAlgorithm::Solution
{
public:
    TSPSolution();
    TSPSolution(const TSPSolution& solution);

    virtual Solution* clone() const;

    virtual Fitness CalcFitness(const GeneticAlgorithm &algorithm_manager);

};

class TSPGeneticAlgorithm : public GeneticAlgorithm
{
private:
    int capacity_;
    int num_items_;
    TSP *TSP_; // lent

public:

    TSPGeneticAlgorithm();
    virtual ~TSPGeneticAlgorithm();

    int set_capacity(int capacity) { return capacity_ = capacity; }
    void set_TSP(TSP &TSP);
    int num_items() { return num_items_; }
    int capacity() { return capacity_; }
    TSP &TSP() { return *TSP_; }
};

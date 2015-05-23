#pragma once

#include "GeneticAlgorithm.h"
#include "Salesman.h"

class TSPGene : public Gene
{
    typedef bool Bit;

    Bit bit_;

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

    Genome& Randomize(GeneticAlgorithm &algorithm_manager);
    Gene *RandomGeneFactory() { return new TSPGene(); };
    Genome *clone() const;
    virtual int set_gene(uint32_t i, int city);
};

class TSPSolution : public GeneticAlgorithm::Solution
{
public:
    TSPSolution();
    TSPSolution(const TSPSolution& solution);
    
    Solution* clone() const;
    GeneticAlgorithm::Solution& Mutation(GeneticAlgorithm& manager);
    Fitness CalcFitness(GeneticAlgorithm &algorithm_manager);
};

class TSPGeneticAlgorithm : public GeneticAlgorithm
{
private:
    Salesman *salesman_; // lent
    std::vector< int > cities_array_; // Keep to shuffle and generate random solutions

public:
    TSPGeneticAlgorithm();
    virtual ~TSPGeneticAlgorithm();

    Salesman& set_salesman(Salesman &TSP);
    inline Salesman& salesman() const { return *salesman_; }
    inline std::vector< int >& cities_array() { return cities_array_; }
    inline int num_cities() const { return salesman_->num_cities(); }
};

#pragma once

#include "GeneticAlgorithm.h"
#include "Salesman.h"

class TSPGene : public Gene
{
    typedef int City;

    City city_;

    virtual Gene* clone() const;

public:
    TSPGene() {}
    TSPGene(City city) : city_(city) {}
    TSPGene(const TSPGene& gene) : city_(gene.city_) {}

    inline City city() { return city_; }
    inline City& set_city(const City& city) { return city_ = city; }
};

class TSPGenome : public Genome
{
    friend class TSPSolution;
public:
    TSPGenome(uint32_t size);
    TSPGenome(const TSPGenome& genome);

    inline Gene *RandomGeneFactory() { return new TSPGene(); };

    Genome& Randomize(GeneticAlgorithm &algorithm_manager);
    Genome *clone() const;
    void swap(uint32_t i, uint32_t j);
    Gene& set_gene(uint32_t i, int city);
};

class TSPSolution : public Solution
{
public:
    TSPSolution();
    TSPSolution(const TSPSolution& solution);
    
    Solution** Crossover(const Solution* s) const;
    Solution* clone() const;
    Solution& Mutation(GeneticAlgorithm& manager);
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

    SolutionComparator Compare() const;

    inline Salesman& salesman() const { return *salesman_; }
    inline std::vector< int >& cities_array() { return cities_array_; }
    inline int num_cities() const { return salesman_->num_cities(); }

    Salesman& set_salesman(Salesman &TSP);
};

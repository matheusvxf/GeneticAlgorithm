#pragma once

#include <vector>

#include "Graph.h"
#include "Common.h"
#include "TestWrapper.h"
#include "TSPGenetic.h"

class Salesman : public SolverInterface
{
private:
    TSPGeneticAlgorithm ga_manager_;
    std::string generation_statistic_file_;
private:
    Graph graph_;
    std::vector< std::vector< int > > m;

    int DynamicProgrammingRecursion(int i, int S);
public:
    Salesman();
    ~Salesman();

    int SolveDynamicProgramming();
    GeneticAlgorithm::SolutionVector& SolveGeneticAlgorithm();
    bool ReadNextTestCase(std::fstream &fs);
    std::string problem_size() const { return int2str(graph_.num_nodes());  }

    std::string statistic_file() const { return kSalesmanStatistFile; }
    std::string default_time_file() const { return kSalesmanTimeFile; }
    std::string test_file() const { return kSalesmanTestFile; }
    std::string name() const { return "salesman"; }
    std::string& set_generation_statistic_file(const std::string& file) { return generation_statistic_file_ = file; }

    void set_num_vertices(int num_vertices);
    void set_connection(int src, int dst, int cost);
    inline int num_vertices() { return graph_.num_nodes(); }
    inline int num_cities() { return num_vertices(); }
    inline int cost(int i, int j) { return graph_.cost(i, j); }


    static std::string ProblemGenerator(int num_cities);
};


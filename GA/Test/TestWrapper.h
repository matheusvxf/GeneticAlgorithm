#pragma once

#include <string>
#include <sstream>

#include "GeneticAlgorithm.h"
#include "TesterFiles.h"

class SolverInterface
{
public:
    virtual void SolveExactSolution() = 0;
    virtual GeneticAlgorithm::SolutionVector& SolveGeneticAlgorithm() = 0;
    virtual GeneticAlgorithm& ga_manager() = 0;
    virtual std::string name() const = 0;
    virtual std::string& set_generation_statistic_file(const std::string &file) = 0;
    virtual bool ReadNextTestCase(std::fstream &fs) = 0;
    virtual std::string problem_size() const = 0;
};

class TestWrapper
{
protected:
    SolverInterface *solver_;
    std::string log_dir_;
    std::string test_file_;
    std::string statistic_file_;

    void SolveDynamicProgramming(const std::string& file);
    void SolveGeneticAlgorithm(const std::string& file);
public:
    TestWrapper(SolverInterface *solver) : solver_(solver), log_dir_(kLogDir) {}
    virtual ~TestWrapper() { delete solver_; }

    void Solve();

    std::string& test_file() { return test_file_; }
    std::string& log_dir() { return log_dir_; }
    std::string& statistic_file() { return statistic_file_; }
    std::string& set_log_dir(const std::string &log_dir) { return log_dir_ = log_dir; }
    std::string& set_test_file(const std::string &test_file) { return test_file_ = test_file; }
};


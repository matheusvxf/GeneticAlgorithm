#include "TestWrapper.h"

#include <fstream>
#include <chrono>

#include "Logger.h"
#include "TesterFiles.h"

void TestWrapper::Solve()
{
    std::fstream fs;
    Logger logger;
    int test = 1;
    bool first_test = true;
    statistic_file_ = log_dir() + solver_->name() + "-statistic.txt";
    std::string dynamic_time_file = log_dir() + "dynamic-time-" + solver_->name() + ".txt";
    std::string genetic_time_file = log_dir() + "genetic-time-" + solver_->name() + ".txt";

    logger.create(statistic_file());
    logger.create(dynamic_time_file);
    logger.create(genetic_time_file);

    fs.open(test_file(), std::fstream::in);

    printf("%s Problem\n", solver_->name().c_str());

    while (solver_->ReadNextTestCase(fs))
    {
        std::string generation_statistic_file = log_dir() + "statistic-" + solver_->name() +
            "-test-" + int2str(test) + ".txt";
        solver_->set_generation_statistic_file(generation_statistic_file);

        // No need to run dynamic programming every time for variance test
        if (!(Test::Task & RUN_VARIANCE) || first_test)
        {
            SolveDynamicProgramming(dynamic_time_file);
            first_test = false;
        }
        SolveGeneticAlgorithm(genetic_time_file);
        test++;
    }
    printf("\n");

    fs.close();
}

void TestWrapper::SolveDynamicProgramming(const std::string& file)
{
    Logger logger;
    auto start = std::chrono::system_clock::now();
    auto fitness = solver_->SolveExactSolution();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
    
    logger.open(file, std::fstream::app);
    logger.fstream() << solver_->problem_size() << " " << fitness << " " << duration.count() << std::endl;
    logger.close();
}

void TestWrapper::SolveGeneticAlgorithm(const std::string& file)
{
    Logger logger;
    auto start = std::chrono::system_clock::now();
    auto &population = solver_->SolveGeneticAlgorithm();
    auto &solution = **population.begin();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);

#if(DEBUG == TRUE)
    solution.print(solver_->ga_manager());
#endif
    logger.open(statistic_file(), std::fstream::app);
    logger.LogPopulationFitness(population);
    logger.close();
    logger.open(file, std::fstream::app);
    logger.fstream() << solver_->problem_size() << " " << solution.fitness() << " " << duration.count() << std::endl;
    logger.close();

    printf("Genetic Algorithm Solution: %f\n\n", solution.fitness());
}
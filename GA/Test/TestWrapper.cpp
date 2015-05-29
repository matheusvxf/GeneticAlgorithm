#include "TestWrapper.h"

#include <fstream>
#include <chrono>

#include "Logger.h"

void TestWrapper::Solve()
{
    std::fstream fs;
    Logger logger;
    int test = 1;

    if (!solver_->statistic_file().empty())
    {
        logger.create(solver_->statistic_file());
        logger.open(solver_->statistic_file(), std::fstream::app);
        logger.fstream() << "best worse average standard_deviation" << std::endl;
        logger.close();
    }
    if (!solver_->default_time_file().empty())
    {
        std::string str_builder = kLogDir + "dynamic-" + solver_->default_time_file();;

        logger.create(solver_->time_file());
        logger.create(str_builder);
        
        str_builder = kLogDir + "genetic-" + solver_->default_time_file();
        logger.create(str_builder);
    }

    fs.open(solver_->test_file(), std::fstream::in);

    printf("%s Problem\n", solver_->name().c_str());
    while (solver_->ReadNextTestCase(fs))
    {
        std::string str_builder = kLogDir + "statistic-" + solver_->name() + 
            "-test-" + int2str(test) + ".txt";
        solver_->set_generation_statistic_file(str_builder);

        str_builder = kLogDir + "dynamic-" + solver_->default_time_file();
        solver_->set_time_file(str_builder);

        SolveDynamicProgramming();

        str_builder = kLogDir + "genetic-" + solver_->default_time_file();
        solver_->set_time_file(str_builder);

        printf("Genetic Algorithm Solution: %f\n\n", SolveGeneticAlgorithm());
        test++;
    }
    printf("\n");

    fs.close();
}

void TestWrapper::SolveDynamicProgramming()
{
    Logger logger;
    auto start = std::chrono::system_clock::now();
    solver_->SolveExactSolution();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
    
    if (!solver_->time_file().empty())
    {
        logger.open(solver_->time_file(), std::fstream::app);
        logger.fstream() << solver_->problem_size() << " " << duration.count() << std::endl;
        logger.close();
    }
}

float TestWrapper::SolveGeneticAlgorithm()
{
    Logger logger;
    auto start = std::chrono::system_clock::now();
    auto &solution = **solver_->SolveGeneticAlgorithm().begin();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);

#if(DEBUG == TRUE)
    solution.print(solver_->ga_manager());
#endif
    if (!solver_->time_file().empty())
    {
        logger.open(solver_->time_file(), std::fstream::app);
        logger.fstream() << solver_->problem_size() << " " << duration.count() << std::endl;
        logger.close();
    }

    return  solution.fitness();
}
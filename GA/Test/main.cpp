#include <iostream>
#include <fstream>

#include "TestKnapsack.h"
#include "TestTSP.h"
#include "SampleGeneticAlgorithm.h"
#include "Logger.h"

// Private functions
static void RunKnapsackTest();
static void RunSalesmanTest();
static void RunSimpleGA();

int main()
{
    using namespace std;

    RunSalesmanTest();
    RunKnapsackTest();
}

void RunSimpleGA()
{
    SampleGeneticAlgorithm GA;
    
    Solution& solution = GA.Run();
}

void RunKnapsackTest()
{
    using namespace TestKnapsack;
    Knapsack knapsack;
    std::fstream fs;
    Logger logger;
    int test = 1;

    logger.create(kKnapsackStatistFile);
    logger.create(kKnapsackTimeFile);
    logger.open(kKnapsackStatistFile, std::fstream::app);
    logger.fstream() << "best worse average standard_deviation" << std::endl;
    logger.close();

    fs.open(knapsack_test_file);
    
    printf("Knapsack Problem\n");
    while (ReadNextTestCase(fs, knapsack))
    {
        printf("Dynamic Programming Solution: %d\n", knapsack.SolveDynamicProgramming());
        printf("Genetic Algorithm Solution: %f\n\n", knapsack.SolveGA(test++));
    }
    printf("\n");

    fs.close();
}

void RunSalesmanTest()
{
    using namespace TestTSP;
    Salesman salesman;
    std::fstream fs;
    Logger logger;
    int test = 1;

    logger.create(kSalesmanStatistFile);
    logger.create(kSalesmanTimeFile);
    logger.open(kSalesmanStatistFile, std::fstream::app);
    logger.fstream() << "best worse average standard_deviation" << std::endl;
    logger.close();

    fs.open(salesman_test_file);

    printf("Travelling Salesman Problem\n");
    while (ReadNextTestCase(fs, salesman))
    {
        printf("Dynamic Programming Solution: %d\n", salesman.SolveDynamicProgramming());
        printf("Genetic Algorithm Solution: %f\n\n", salesman.SolveGA(test++));
    }
    printf("\n");

    fs.close();
}
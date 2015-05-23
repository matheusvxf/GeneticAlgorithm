#include <iostream>
#include <fstream>

#include "TestKnapsack.h"
#include "TestTSP.h"
#include "GeneticNumberIncrease.h"

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
    GeneticNumberIncrease GA;
    
    Solution* solution = GA.Run();
}

void RunKnapsackTest()
{
    using namespace TestKnapsack;
    Knapsack knapsack;
    std::fstream fs;

    fs.open(knapsack_test_file);
    
    while (ReadNextTestCase(fs, knapsack))
    {
        printf("Dynamic Programming Solution: %d\n", knapsack.SolveDynamicProgramming());
        printf("Genetic Algorithm Solution: %d\n", knapsack.SolveGA());
    }

    fs.close();
}

void RunSalesmanTest()
{
    using namespace TestTSP;
    Salesman salesman;
    std::fstream fs;

    fs.open(salesman_test_file);

    while (ReadNextTestCase(fs, salesman))
    {
        printf("Dynamic Programming Solution: %d\n", salesman.SolveDynamicProgramming());
        printf("Genetic Algorithm Solution: %d\n", salesman.SolveGA());
    }

    fs.close();
}
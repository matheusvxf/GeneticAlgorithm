#include <iostream>
#include <fstream>

#include "TestKnapsack.h"
#include "TestTSP.h"

// Private functions
static void RunExactKnapsackTest();
static void RunExactSalesmanTest();

int main()
{
    using namespace std;

    //RunExactKnapsackTest();
    RunExactSalesmanTest();
}

void RunExactKnapsackTest()
{
    using namespace TestKnapsack;
    Knapsack knapsack;
    std::fstream fs;

    fs.open(knapsack_test_file);
    
    while (ReadNextTestCase(fs, knapsack))
    {
        printf("Solution: %d\n", knapsack.SolveDynamicProgramming());
    }

    fs.close();
}

void RunExactSalesmanTest()
{
    using namespace TestTSP;
    Salesman salesman;
    std::fstream fs;

    fs.open(salesman_test_file);

    while (ReadNextTestCase(fs, salesman))
    {
        printf("Solution: %d\n", salesman.SolveDynamicProgramming());
    }

    fs.close();
}
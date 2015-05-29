#include <iostream>
#include <fstream>

#include "Knapsack.h"
#include "Salesman.h"
#include "Common.h"

// Private functions
static void RunKnapsackTest();
static void RunSalesmanTest();
static void GenSalesmanTest();
static void GenKnapsackTest();

int main()
{
    using namespace std;

    RunSalesmanTest();
    //RunKnapsackTest();

    GenSalesmanTest();
    GenKnapsackTest();
}

void RunKnapsackTest()
{
    TestWrapper wrapper(new Knapsack());
    
    wrapper.Solve();
}

void RunSalesmanTest()
{
    TestWrapper wrapper(new Salesman());

    wrapper.Solve();
}

void GenSalesmanTest()
{
    std::fstream fs;
    fs.open(kInputDir + "tsp-test-1.txt", std::fstream::out);

    for (int i = 3; i < 20; ++i)
    {
        fs << Salesman::ProblemGenerator(i);
    }
    fs << "0 0" << std::endl;
    fs.close();
}

void GenKnapsackTest()
{
    std::fstream fs;
    int weight = rand() % 1000;
    fs.open(kInputDir + "knapsack-test-1.txt", std::fstream::out);

    for (int i = 10; i < 100; ++i)
    {
        fs << Knapsack::ProblemGenerator(i, weight);
    }
    fs << "0 0" << std::endl;
    fs.close();
}
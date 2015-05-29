#include <iostream>
#include <fstream>

#include "Knapsack.h"
#include "Salesman.h"

// Private functions
static void RunKnapsackTest();
static void RunSalesmanTest();

int main()
{
    using namespace std;

    RunSalesmanTest();
    RunKnapsackTest();
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
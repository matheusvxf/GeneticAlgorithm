#include <iostream>

#include "KnapsackTest.h"

// Private functions
static void RunExactKnapsackTest();

int main()
{
    using namespace std;

    RunExactKnapsackTest();
}

void RunExactKnapsackTest()
{
    using namespace KnapsackTest;
    Knapsack knapsack;

    while (ReadNextTestCase(knapsack))
    {
        printf("Solution: %d\n", knapsack.SolveDynamicProgramming());
    }
}
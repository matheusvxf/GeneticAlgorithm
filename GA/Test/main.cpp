#include <iostream>
#include <fstream>

#include "Knapsack.h"
#include "Salesman.h"
#include "Common.h"
#include "TesterFiles.h"

// Private functions
static void RunKnapsackTest();
static void RunSalesmanTest();
static void GenSalesmanTest();
static void GenSalesmanVarianceTest();
static void GenKnapsackNumItemsTest();
static void GenKnapsackWeightTest();
static void GenKnapsackVarianceTest();

enum TASK
{
    RUN_SALESMAN = 1 << 0,
    RUN_KNAPSACK = 1 << 1,
    RUN = RUN_SALESMAN | RUN_KNAPSACK,
    CREATE_TEST = 1 << 2
};

const int kTask = (RUN_KNAPSACK | CREATE_TEST);
//const TASK kTask = CREATE_TEST;

int main()
{
    using namespace std;

    if (kTask & RUN)
    {
        if (kTask & RUN_SALESMAN)
            RunSalesmanTest();
        if (kTask & RUN_KNAPSACK)
            RunKnapsackTest();
    }
    if (kTask & CREATE_TEST)
    {
        printf("Creating test...\n");
        GenSalesmanTest();
        GenSalesmanVarianceTest();
        GenKnapsackNumItemsTest();
        GenKnapsackWeightTest();
        GenKnapsackVarianceTest();
        printf("Test Generated\n");
    }
}

void RunKnapsackTest()
{
    TestWrapper wrapper(new Knapsack());
    
    wrapper.set_test_file(kInputDir + kKnapsackTestFile);
    wrapper.Solve();
}

void RunSalesmanTest()
{
    TestWrapper wrapper(new Salesman());

    wrapper.set_test_file(kInputDir + kTSPTestFile);
    wrapper.Solve();
}

void GenSalesmanTest()
{
    std::fstream fs;
    fs.open(kInputDir + kTSPNumCitiesTestFile, std::fstream::out);

    for (int i = 1; i < 15; ++i)
    {
        fs << Salesman::ProblemGenerator(i);
    }
    fs << "0 0" << std::endl;
    fs.close();
}

void GenSalesmanVarianceTest()
{
    std::fstream fs;
    std::string test_str = Salesman::ProblemGenerator(10);
    fs.open(kInputDir + kTSPVarianceTestFile, std::fstream::out);

    for (int i = 0; i < 30; ++i)
    {
        fs << test_str;
    }
    fs << "0 0" << std::endl;
    fs.close();
}

void GenKnapsackNumItemsTest()
{
    std::fstream fs;
    int weight = rand() % 1000;
    fs.open(kInputDir + kKnapsackNumItemsTestFile, std::fstream::out);

    for (int i = 10; i < 100; ++i)
    {
        fs << Knapsack::ProblemGenerator(i, weight);
    }
    fs << "0 0" << std::endl;
    fs.close();
}

void GenKnapsackWeightTest()
{
    std::fstream fs;
    int num_items = 200;
    fs.open(kInputDir + kKnapsackWeightTestFile, std::fstream::out);

    for (int w = 10000; w <= 200000; w += 10000)
    {
        fs << Knapsack::ProblemGenerator(num_items, w);
    }
    fs << "0 0" << std::endl;
    fs.close();
}

void GenKnapsackVarianceTest()
{
    std::fstream fs;
    int weight = rand() % 1000;
    std::string str_test = Knapsack::ProblemGenerator(100, weight);

    fs.open(kInputDir + kKnapsackVarianceTestFile, std::fstream::out);

    for (int i = 0; i < 30; ++i)
    {
        fs << str_test;
    }
    fs << "0 0" << std::endl;
    fs.close();
}
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

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

const extern float kKnapsackMutation = 0.5f;
const extern float kKnapsackCrossover = 70.0f;
const extern float kTSPMutation = 0.1f;
const extern float kTSPCrossover = 70.0f;

#if(KNAPSACK_TEST == NORMAL)
std::string KnapsackLogDir = kKnapsackDir + "normal/";
std::string KnapsackTestFile = kKnapsackNumItemsTestFile;
#elif(KNAPSACK_TEST == VARIANCE)
std::string KnapsackLogDir = kKnapsackDir + "variance/";
std::string KnapsackTestFile = kKnapsackVarianceTestFile;
#elif(KNAPSACK_TEST == KNAPSACK_WEIGHT)
std::string KnapsackLogDir = kKnapsackDir + "weight/";
std::string KnapsackTestFile = kKnapsackWeightTestFile;
#endif

#if(TSP_TEST == NORMAL)
std::string TSPLogDir = KTSPDir + "normal/";
std::string TSPTestFile = kTSPNumCitiesTestFile;
#elif(TSP_TEST == VARIANCE)
std::string TSPLogDir = KTSPDir + "variance/";
std::string TSPTestFile = kTSPVarianceTestFile;
#endif

int Test::Task = (RUN_KNAPSACK_NORMAL | CREATE_TEST);
//const TASK Test::Task = CREATE_TEST;

int main()
{
    using namespace std;

    // Initialize random seed
    srand((uint32_t)time(NULL));
    if (Test::Task & CREATE_TEST)
    {
        printf("Creating test...\n");
        GenSalesmanTest();
        GenSalesmanVarianceTest();
        GenKnapsackNumItemsTest();
        GenKnapsackWeightTest();
        GenKnapsackVarianceTest();
        printf("Test Generated\n");
    }
    if (Test::Task & RUN)
    {
        if (Test::Task & RUN_SALESMAN)
        {
            if (Test::Task & RUN_SALESMAN_NORMAL)
            {
                TSPLogDir = KTSPDir + "normal/";
                TSPTestFile = kTSPNumCitiesTestFile;
                RunSalesmanTest();
            }
            if (Test::Task & RUN_SALESMAN_VARIANCE)
            {
                TSPLogDir = KTSPDir + "variance/";
                TSPTestFile = kTSPVarianceTestFile;
                RunSalesmanTest();
            }
        }
        if (Test::Task & RUN_KNAPSACK)
        {
            if (Test::Task & RUN_KNAPSACK_NORMAL)
            {
                KnapsackLogDir = kKnapsackDir + "normal/";
                KnapsackTestFile = kKnapsackNumItemsTestFile;
                RunKnapsackTest();
            }
            if (Test::Task & RUN_KNAPSACK_WEIGHT)
            {
                KnapsackLogDir = kKnapsackDir + "weight/";
                KnapsackTestFile = kKnapsackNumItemsTestFile;
                RunKnapsackTest();
            }
            if (Test::Task & RUN_KNAPSACK_VARIANCE)
            {
                KnapsackLogDir = kKnapsackDir + "variance/";
                KnapsackTestFile = kKnapsackVarianceTestFile;
                RunKnapsackTest();
            }
        }
    }
}

void RunKnapsackTest()
{
    TestWrapper wrapper(new Knapsack());
    
    wrapper.set_test_file(kInputDir + KnapsackTestFile);
    wrapper.set_log_dir(KnapsackLogDir);
    wrapper.Solve();
}

void RunSalesmanTest()
{
    TestWrapper wrapper(new Salesman());

    wrapper.set_test_file(kInputDir + TSPTestFile);
    wrapper.set_log_dir(TSPLogDir);
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
    int weight = 1000;
    fs.open(kInputDir + kKnapsackNumItemsTestFile, std::fstream::out);

    for (int i = 10; i <= 200; i += 10)
    {
        fs << Knapsack::ProblemGenerator(i, weight);
    }
    fs << "0 0" << std::endl;
    fs.close();
}

void GenKnapsackWeightTest()
{
    std::fstream fs;
    int num_items = 100;
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
    int weight = 1000;
    int num_items = 100;
    std::string str_test = Knapsack::ProblemGenerator(num_items, weight);

    fs.open(kInputDir + kKnapsackVarianceTestFile, std::fstream::out);

    for (int i = 0; i < 30; ++i)
    {
        fs << str_test;
    }
    fs << "0 0" << std::endl;
    fs.close();
}
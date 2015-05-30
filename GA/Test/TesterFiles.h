#pragma once

#include <string>


// Test Type
#define NORMAL 0x00
#define VARIANCE 0x01
#define KNAPSACK_WEIGHT 0x02

#define KNAPSACK_TEST NORMAL
#define TSP_TEST NORMAL

const std::string kTSPNumCitiesTestFile = "tsp-test-num-cities-1.txt";
const std::string kTSPVarianceTestFile = "tsp-test-variance-1.txt";

const std::string kKnapsackNumItemsTestFile = "knapsack-test-num-items-1.txt";
const std::string kKnapsackWeightTestFile = "knapsack-test-weight-1.txt";
const std::string kKnapsackVarianceTestFile = "knapsack-test-variance-1.txt";

const std::string kOutputDir = "output-test/";
const std::string kInputDir = "input-test/";

const std::string kKnapsackDir = kOutputDir + "knapsack/";
const std::string KTSPDir = "salesman/";

const extern float kKnapsackMutation;
const extern float kKnapsackCrossover;
const extern float kTSPMutation;
const extern float kTSPCrossover;


extern std::string KnapsackLogDir;
extern std::string KnapsackTestFile;

extern std::string TSPLogDir;
extern std::string TSPTestFile;


enum TASK
{
    RUN_KNAPSACK_NORMAL = 1 << 0,
    RUN_KNAPSACK_WEIGHT = 1 << 1,
    RUN_KNAPSACK_VARIANCE = 1 << 2,
    RUN_KNAPSACK = (RUN_KNAPSACK_NORMAL | RUN_KNAPSACK_VARIANCE | RUN_KNAPSACK_WEIGHT),
    RUN_SALESMAN_NORMAL = 1 << 3,
    RUN_SALESMAN_VARIANCE = 1 << 4,
    RUN_SALESMAN = (RUN_SALESMAN_NORMAL | RUN_SALESMAN_VARIANCE),
    RUN = RUN_SALESMAN | RUN_KNAPSACK,
    RUN_VARIANCE = (RUN_KNAPSACK_VARIANCE | RUN_SALESMAN_VARIANCE),
    CREATE_TEST = 1 << 30
};

namespace Test
{
    extern int Task;
}
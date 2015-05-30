#pragma once

#include <string>

enum TEST_TYPE
{
    NORMAL = 0x00,
    VARIANCE = 0x01,
    KNAPSACK_WEIGHT = 0x04,
};

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

#if(KNAPSACK_TEST == NORMAL)
const std::string kKnapsackLogDir = kKnapsackDir + "normal/";
const std::string kKnapsackTestFile = kKnapsackNumItemsTestFile;
#elif(KNAPSACK_TEST == VARIANCE)
const std::string kKnapsackLogDir = kKnapsackDir + "variance/";
const std::string kKnapsackTestFile = kKnapsackVarianceTestFile;
#elif(KNAPSACK_TEST == KNAPSACK_WEIGHT)
const std::string kKnapsackLogDir = kKnapsackDir + "weight/";
const std::string kKnapsackTestFile = kKnapsackVarianceTestFile;
#endif

#if(TSP_TEST == NORMAL)
const std::string kTSPLogDir = KTSPDir + "normal/";
const std::string kTSPTestFile = kTSPNumCitiesTestFile;
#elif(TSP_TEST == VARIANCE)
const std::string kTSPLogDir = KTSPDir + "variance/";
const std::string kTSPTestFile = kTSPVarianceTestFile;
#endif

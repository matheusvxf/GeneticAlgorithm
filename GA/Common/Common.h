#pragma once

#include <stdlib.h>
#include <sstream>
#include <string>

typedef bool Bit;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;
typedef signed char int8_t;
typedef signed long long int int64_t;


typedef float Fitness;


const uint32_t kGenomeSize = 64;

#define FLAG_Logger true
#define DEBUG false
#define INF (1 << 30)
#define ALL(Q) Q.begin(), Q.end()
#define FIND(Q, q) (Q.find(q) != Q.end())
#define foreach(Q, it) for(auto it = Q.begin(); it != Q.end(); ++it)

const std::string kLogDir = "output-test/";
const std::string kInputDir = "input-test/";
const std::string kStatisticFile = kLogDir + "statistic.txt";
const std::string KKnapsackTestFile = kInputDir + "knapsack-test-1.txt";
const std::string kKnapsackStatistFile = kLogDir + "statistic-knapsack.txt";
const std::string kKnapsackTimeFile = "time-knapsack.txt";
const std::string kSalesmanTestFile = kInputDir + "tsp-test-1.txt";
const std::string kSalesmanStatistFile = kLogDir + "statistic-salesman.txt";
const std::string kSalesmanTimeFile = "time-salesman.txt";

const uint32_t kElitismSize = 2;
const uint32_t kNumGenerations = 200;
const uint32_t kPopulationSize = 100;

#define frand() (((float)rand() / (float)RAND_MAX) * 100.0f)


extern inline int DivideCeil(int numerator, int denominator)
{
    return numerator / denominator + (numerator % denominator == 0 ? 0 : 1);
}

template< class T >
extern inline std::string Convert2String(T data)
{
    std::stringstream buffer;
    buffer << data;
    return buffer.str();
}

extern inline std::string int2str(int num)
{
    return Convert2String<int>(num);
}

extern inline std::string float2str(float num)
{
    return Convert2String<float>(num);
}

extern inline std::string double2str(double num)
{
    return Convert2String<double>(num);
}
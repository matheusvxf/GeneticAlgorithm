#pragma once

#include <stdlib.h>

typedef bool Bit;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;
typedef signed char int8_t;
typedef signed long long int int64_t;


typedef float Fitness;


const uint32_t kGenomeSize = 64;

#define DEBUG false
#define INF (1 << 30)
#define ALL(Q) Q.begin(), Q.end()
#define FIND(Q, q) (Q.find(q) != Q.end())
#define foreach(Q, it) for(auto it = Q.begin(); it != Q.end(); ++it)

const char salesman_test_file[] = "test_tsp.txt";
const char knapsack_test_file[] = "test_knapsack.txt";

#define frand() (((float)rand() / (float)RAND_MAX) * 100.0f)

extern inline int DivideCeil(int numerator, int denominator)
{
    return numerator / denominator + (numerator % denominator == 0 ? 0 : 1);
}
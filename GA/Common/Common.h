#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


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
#define TRUE 1
#define FALSE 0
#define DEBUG FALSE
#define INF (1 << 30)
#define ALL(Q) Q.begin(), Q.end()
#define FIND(Q, q) (Q.find(q) != Q.end())
#define foreach(Q, it) for(auto it = Q.begin(); it != Q.end(); ++it)


const uint32_t kElitismSize = 2;
const uint32_t kNumGenerations = 100;
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
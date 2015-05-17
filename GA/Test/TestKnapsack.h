#pragma once

#include <fstream>

#include "Knapsack.h"
#include "Common.h"

namespace TestKnapsack
{
    extern bool ReadNextTestCase(std::fstream &fs, Knapsack &knapsack);
}
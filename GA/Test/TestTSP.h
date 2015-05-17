#pragma once

#include <fstream>

#include "Salesman.h"

namespace TestTSP {
    extern bool ReadNextTestCase(std::fstream &fs, Salesman &salesman);
};


#include "GeneticAlgorithmWrapper.h"

#include <chrono>

#include "Log.h"

void GeneticAlgorithmWrapper::Loop()
{
    if (!time_output_file().empty())
    {
        Log log;
        auto start = std::chrono::system_clock::now();

        GeneticAlgorithm::Loop();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
        log.open(time_output_file(), std::fstream::app);
        log.fstream() << duration.count() << std::endl;
        log.close();
    }
    else
    {
        GeneticAlgorithm::Loop();
    }
}

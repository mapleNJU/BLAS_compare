#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "operation.h"

void generate_random_datatypes(int rows, int cols, datatype min_value, datatype max_value, const std::string &filename)
{
    auto now = std::chrono::system_clock::now();
    auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::mt19937 gen(static_cast<unsigned int>(seed));
    std::uniform_real_distribution<datatype> dis(min_value, max_value);

    std::ofstream outfile(filename);
    if (!outfile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            datatype random_value = dis(gen);
            outfile << random_value << " ";
        }
        outfile << std::endl;
    }

    outfile.close();
}

#include <iostream>
#include <fstream>
#include <vector>
#include "operation.h"

std::vector<datatype> read_elements_from_file(const std::string& filename, int num, int gap) {
    std::vector<datatype> data; // Vector to hold the elements
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data; // Return an empty vector if the file cannot be opened
    }

    // Calculate the starting position in the file based on 'num' and 'gap'
    int start_position = (num - 1) * gap * sizeof(datatype);

    // Set the file position indicator to the appropriate location in the file
    file.seekg(start_position);

    datatype value;
    // Read 'num' elements with the specified 'gap' and add them to the vector
    for (int i = 0; i < num && file >> value; ++i) {
        data.push_back(value);
        // Move the file position indicator to the next element based on 'gap'
        file.seekg(gap * sizeof(datatype), std::ios_base::cur);
    }

    return data;
}

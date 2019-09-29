//
// Created by Joker on 8/14/2018.
//

#include <fstream>

#include "File.hpp"

using namespace PhantomEngine::IO;

char* File::ReadAllText(const char *path) {
    std::ifstream f(path);          // Open file
    f.seekg(0, std::ios::end);      // Seek to end
    int length = f.tellg();         // Get index(index == length)
    auto buffer = new char[length];

    f.seekg(0, std::ios::beg);      // Go to beginning
    f.read(buffer, length);         // Read all into buffer

    return buffer;
}

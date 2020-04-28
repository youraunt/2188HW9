//
// Created by BK Allen on 4/23/2020.
//

#ifndef INC_2188HW9_FUNCTIONS_H
#define INC_2188HW9_FUNCTIONS_H
/// @brief Dependencies
#include <unordered_map>
#include <utility>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <list>
#include <filesystem>

#define WHAT_IS(x) std::cerr << #x << " is " << x << std::endl;

#include "HashTable.h"


/// @brief Exits program successfully with message
inline std::string exit_program() {
    std::cout << "Exiting program!" << std::endl;
    /// @brief I used EXIT_SUCCESS here to unwind the stack
    exit(EXIT_SUCCESS);
}

inline void unknown_input() {
    std::cerr << "\nError?! Unknown input.\n" << std::endl;
    exit_program();
}

[[noreturn]] inline void fileNotFound() {
    std::cerr << "File not found!" << std::endl
              << "Exiting Program!" << std::endl;
    /// @brief winds down stack
    exit(EXIT_FAILURE);
}

unsigned int dictionary_matches(const std::string &file);

int total_words_in_file(const std::string &file);

bool enter_program(int argc, char **argv, const HashTable &dictionary_hash_table);

std::string get_file_name(int argc, char **argv);
std::string get_reference_file_name();


#endif //INC_2188HW9_FUNCTIONS_H

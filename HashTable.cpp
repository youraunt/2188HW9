//
// Created by BK Allen on 4/23/2020.
//

#include <algorithm>
#include "HashTable.h"
#include "Functions.h"


void HashTable::from_file(const std::string &file) {
    std::string temporary_string_housing;
    std::ifstream in_file(file.c_str(),std::ios_base::in);
        if (!in_file || in_file.fail()) {
            std::cout << "I could not find your file." << std::endl;
           unknown_input();
        }

    while (in_file.peek() != EOF) {
        in_file >> temporary_string_housing;
        temporary_string_housing = tolower(temporary_string_housing);
        put(temporary_string_housing);
    }
    in_file.close();
}

bool HashTable::is_in_table(std::string entry) {
    entry = tolower(entry);
    int index = hash_string(entry);
    std::list<std::string>::iterator iterator;
    for (iterator = hash_table[index].begin(); iterator != hash_table[index].end(); ++iterator) {
        if (*iterator == entry) { return true; }
    }
    return false;
}

void HashTable::put(const std::string &entry) {
    int index = hash_string(entry);
    hash_table[index].push_back(entry);
}

int HashTable::how_big() {
    int counter{};
    for (auto &i : hash_table) { counter += i.size(); }
    return counter;
}



std::string HashTable::clean_string(std::string in) {
    std::string out;
    in.erase(std::remove_if(in.begin(), in.end(), (int (*)(int)) std::isalnum), in.end());
    //std::transform(in.begin(), in.end(), std::back_inserter(out), ::to_lower);
    return out;
}

int HashTable::hash_string(const std::string &input) {
    int index{};
    int hash{};
    int size_of = input.length();
    for (unsigned int i = 0; i < size_of; ++i) { hash += input[i]; }
    index = hash % SIZE_OF_TABLE;
    return index;
}
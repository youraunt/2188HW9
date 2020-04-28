//
// Created by BK Allen on 4/23/2020.
//

#ifndef INC_2188HW9_HASHTABLE_H
#define INC_2188HW9_HASHTABLE_H

#include <iostream>
#include <list>
#include <cctype>
#include <fstream>

class HashTable {
    static const int SIZE_OF_TABLE = 1373;

    std::list<std::string> hash_table[SIZE_OF_TABLE];
public:
    int hash_string(const std::string &in);

    void from_file(const std::string &file);

    bool is_in_table(std::string entry);

    void put(const std::string &entry);

    int how_big();

    static std::string clean_string(std::string in);


};


#endif //INC_2188HW9_HASHTABLE_H

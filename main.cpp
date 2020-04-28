//
// Created by BK Allen on 4/23/2020.
//

#include "Functions.h"
#include "HashTable.h"

int main(int argc, char ** argv) {
HashTable dictionary_hash_table;
dictionary_hash_table.from_file(R"(dict.txt)");
    try {
        std::cin.exceptions(std::istream::failbit);
        enter_program(argc, argv,dictionary_hash_table);
    }catch (const std::exception &exception){
        std::cerr << exception.what() << std::endl;
        unknown_input();
    }
}

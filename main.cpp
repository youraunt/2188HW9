//
// Created by BK Allen on 4/23/2020.
//

#include "Functions.h"
#include "HashTable.h"

int main(int argc, char **argv) {
    std::ifstream dictionary_infile;
    dictionary_infile.open("dictionary.txt");
    assert(dictionary_infile.is_open());
    std::unordered_set<std::string> dictionary_set{};
    dictionary_set.rehash(1373);
    while(!dictionary_infile.eof()){
        std::string entry{};
        getWord(dictionary_infile, entry);
        entry = tolower(entry);
        if(!entry.empty()){ dictionary_set.insert(entry);}
    }
    HashTable dictionary_hash_table;
    dictionary_hash_table.from_file(R"(dict.txt)");
    try {
        std::cin.exceptions(std::istream::failbit);
        enter_program(argc, argv, dictionary_hash_table,dictionary_set);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        unknown_input();
    }
}

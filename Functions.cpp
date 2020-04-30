//
// Created by BK Allen on 4/23/2020.
//

#include "Functions.h"
#include <utility>

#define WHAT_IS(x) std::cerr << #x << " is " << x << std::endl;

/// @brief static const char array to display the menu header
static const char MENU_TITLE[] =
        "\n\x1b[36m"
        "-----------------------------------\n"
        "|            Main Menu            |\n"
        "-----------------------------------\n"
        "\n\x1b[0m";


/// @brief Displays main menu
/// @param userChoice the menu choice selected by user
/// @return integer value of user choice
unsigned int main_menu() {
    unsigned int user_choice = 0;
    std::cout
            << MENU_TITLE << std::endl
            << "Please select one of the following options by entering it's "
            << "number in the prompt below and pressing [ENTER] " << std::endl
            << "1. Load Dictionary" << std::endl
            << "2. Load secondary file" << std::endl
            << "3. Display" << std::endl
            << "4. Write out" << std::endl
            << "5. Exit" << std::endl
            << "\x1b[32m> \x1b[0m";
    std::cin >> user_choice;
    return user_choice;
}///# MainMenu
bool enter_program(int argc, char **argv, HashTable &hashTable,const std::unordered_set<std::string>& set) {
    unsigned int choice{};
    unsigned int matches{};
    std::ofstream outfile("dictionary_out.txt", std::ios_base::out);
    std::string dictionary_file = "dict.txt";
    std::string reference_file = "potter.txt";
    do {

        choice = main_menu();
        switch (choice) {
            case 1:
                dictionary_file = get_file_name(argc, argv);
                std::cout << "Success!" << std::endl;
                break;
            case 2:
                reference_file = get_reference_file_name();
                dictionary_matches(reference_file,set);
                std::cout << "Success!" << std::endl;
                break;
            case 3:
                std::cout << "Total number of words in \"dict.txt\": " << total_words_in_file(dictionary_file)
                          << std::endl
                          << "Number of words found in your reference file: " << total_words_in_file(reference_file)
                          << std::endl
                          << "Number of words not in \"dict.txt\": " << dictionary_matches(reference_file,set)
                          << std::endl;
                break;
            case 4:
                exit_program();
                break;
            default:
                break;
        }
    } while (choice != 5);
    return false;
}///# enter_program

/// @brief  This function handles user input with option of entering filename at command line
///         Verifies that the file exists before returning filename
/// @param argc (argument count) the number of strings pointed to by argv should be 1+
/// @param argv (argument vector) A one dimensional array of strings. Each string is one/// @return userInput string
//   of the arguments passed to the program.
/// @brief  This function handles user input with option of entering filename at command line
///         Verifies that the file exists before returning filename
/// @param argc (argument count) the number of strings pointed to by argv should be 1+
/// @param argv (argument vector) A one dimensional array of strings. Each string is one/// @return userInput string
//   of the arguments passed to the program.
std::string get_file_name(int argc, char **argv) {
    std::string user_input{};
    /// @brief I am a mac user and not familiar with command line prompts
    /// I got this from a geeks for geeks post
    /// if more than one argument is passed use it.
    if (argc > 1) { user_input = argv[1]; }
        /// else get input from user do/while to continue until valid file is found.
    else {
        do {// until file is found
            std::cout << "Please enter your file name: " << std::endl
                      << "\x1b[32m> \x1b[0m";
            std::cin >> user_input;
            std::ifstream infile("user_input", std::ios_base::in);
            bool valid;
            infile.open(user_input);
            assert(infile.is_open());
            valid = infile.is_open();
//            /// @reference https://en.cppreference.com/w/cpp/filesystem/exists
//            bool valid{std::__fs::filesystem::exists(user_input)};
/// another c++std17 feature that the dated grid, GCC version 6.3.1 releases December, 21, 2016, cannot handle
            if (!valid) {
                std::cout << "I could not fine your file." << std::endl
                          << "Please, try again." << std::endl;
                continue;
            }
            break;
        } while (true);
    }///# else
    return std::string(user_input);
} ///#getFileName

void print(std::unordered_set<std::string> const &s){
    std::copy(s.begin(),s.end(),std::experimental::make_ostream_joiner(std::cout,"\n"));
}

unsigned int dictionary_matches(const std::string &file, const std::unordered_set<std::string> &set) {
    std::string temporary_string_housing;
    std::ifstream reference_infile(file,std::ios_base::in);
    assert(reference_infile.is_open());
    std::unordered_set<std::string> reference_set{1373};
    reference_set.rehash(1373);
    int not_in_dictionary=0;
    while (!reference_infile.eof()) {
        getWord(reference_infile, temporary_string_housing);
        if(!temporary_string_housing.empty()){
            temporary_string_housing = tolower(temporary_string_housing);
            auto temp = set.find(temporary_string_housing);
            if(temp == set.end()){
                reference_set.insert(temporary_string_housing);
                not_in_dictionary++;
            }

    }
//        for(const auto& entry : reference_set){
//            std::cout<< entry << std::endl;
//        }
        print(reference_set);
       std::cout<<"\nref "<< not_in_dictionary <<  std::endl;

    return not_in_dictionary;
}}

int total_words_in_file(const std::string &file) {
    HashTable hash_table;
    hash_table.from_file(file);
    return hash_table.how_big();
}

std::string tolower(const std::string& s)
{
    // returns a completely lowercase version
    std::string newString;
    for (auto c : s)
    {
        newString += tolower(c);
    }

    return newString;
}
std::ifstream &getWord(std::ifstream &fin, std::string &w) {
    char c;
    w = ""; // clear the string of characters
    while (fin.get(c) && !isalpha(c)); // do nothing. just ignore c
    // return on end-of-file
    if (fin.eof())
        return fin;
    // record first letter of the word
    w += tolower(c);
    // collect letters and digits
    while (fin.get(c) && (isalpha(c) || isdigit(c)|| ispunct(c))) {
        if (isalpha(c) || isdigit(c)) {
            w += tolower(c);
        }
    }
    return fin;
}

std::string get_reference_file_name() {
    std::string file_name{};
    std::cout<< "Please enter a reference filename: " << std::endl
            << "> ";
    std::cin >> file_name;
    return std::string(file_name);
}

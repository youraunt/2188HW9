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
bool enter_program(int argc, char **argv, const HashTable& dictionary_hash_table) {
    unsigned int choice{};
    unsigned int matches{};
    std::ofstream outfile("dictionary_out.txt", std::ios_base::out);
    std::string dictionary_file = "dict.txt";
    std::string reference_file;
    do {

        choice = main_menu();
        switch (choice) {
            case 1:
                dictionary_file = get_file_name(argc, argv);
                std::cout << "Success!" << std::endl;
                break;
            case 2:
                reference_file = get_reference_file_name();
                dictionary_matches(reference_file);
                std::cout << "Success!" << std::endl;
                break;
            case 3:
                std::cout << "Total number of words in file: " << total_words_in_file(dictionary_file) << std::endl
                          << "Number of words found in Dictionary: " << std::endl;
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


std::string get_reference_file_name() {
    std::string user_input{};
        std::cout << "Please enter your file name: " << std::endl
                  << "\x1b[32m> \x1b[0m";
        std::cin >> user_input;
        std::ifstream infile(user_input.c_str(), std::ios_base::in);

        assert(infile.is_open());
        infile.close();
//            /// @reference https://en.cppreference.com/w/cpp/filesystem/exists
//            bool valid{std::__fs::filesystem::exists(user_input)};
/// another c++std17 feature that the dated grid, GCC version 6.3.1 releases December, 21, 2016, cannot handle

    return std::string(user_input);
} ///#getFileName



unsigned int dictionary_matches(const std::string &file) {
    std::string user_input{};
    std::string temporary_string_housing{};
    std::ifstream infile;
    HashTable dictionary_hash_table;
    unsigned int counter{};
    dictionary_hash_table.from_file("dict.txt");
    dictionary_hash_table.from_file(user_input);
    do {
        infile >> temporary_string_housing;
        ++counter;
    } while (infile.peek() != EOF || infile.fail());
    infile.close();
    return counter;
}

int total_words_in_file(const std::string &file) {
    HashTable hash_table;
    hash_table.from_file(file);
    return hash_table.how_big();
}

#include <iostream>
#include "keygen/keygen.h"

int main()
{
    int selection;
    std::string input;
    do
    {
        std::cout << "Enter the keygen number (1, 2, or 3): ";
        std::cin >> selection;
        if (selection < 1 || selection > 3)
        {
            std::cout << "Invalid selection. Please try again." << std::endl;
        }
    } while (selection < 1 || selection > 3);
    std::cin.ignore(); // Clear the newline character from the input buffer
    std::cout << "Enter the input string: ";
    std::getline(std::cin, input);
    std::string result = keygen_map.at(selection)(input);
    std::cout << "Generated key: " << result << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.ignore(); // Wait for user to press Enter

    return 0;
}
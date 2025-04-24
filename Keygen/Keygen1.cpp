#include "Keygen.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// Calculate f1 as X4
int f1(int number1, int number2, int number3, int number4, int number5, int number6, int number7, int number8, int number9) {
    return number6 * number2 * number7 + number3 * number8 * number4 + number9 * number5 * number1
        - (number4 * number2 * number9 + number1 * number8 * number6 + number7 * number5 * number3);
}

// Calculate f2 as X1, X2, X3
int f2(int number3, int number5, int number7, int number9, int n) {
    return 10000 * (number5 % 10) + 1000 * n + 100 * (number3 / 10 % 10 + 5) + 10 * (number9 / 10 % 10) + (number7 % 10) + 2;
}

//  Check first condition if X1 = X2 = X3
bool checkCondition(int number1, int number2, int number6) {
    return (number1 % 10 == number6 % 10) && (number1 % 10 == (number2 % 10) + 3);
}

// Convert to ASCII
std::string convertToString(const std::vector<int>& numbers) {
    std::string result;
    for (int num : numbers) {
        result += to_string(num) + " ";
    }
    return result;
}


std::string keygen1(const std::string& input, std::string& error)
{
    srand(time(0));  // Choose a random seed for the random number generator

    bool success = false;
    int number1, number2, number3, number4, number5, number6, number7, number8, number9;
    while (!success) {
        // Choose random values for number2, number3, number4, number5, number7, number8
        // number1, number6 = number2 + 3
        number2 = 1 + rand() % 100;
        number1 = number6 = number2 + 3;
        number3 = number4 = number5 = number7 = number8 = 1 + rand() % 100;

        // Brute force to find the correct number9
        int r1 = -1, r2 = 0;
        number9 = 0;
        while (r1 < r2) {
            number9++;
            r1 = f1(number1, number2, number3, number4, number5, number6, number7, number8, number9);
            r2 = f2(number3, number5, number7, number9, number1 % 10);
            int r3 = f2(number3, number5, number7, number9, number6 % 10);
            int r4 = f2(number3, number5, number7, number9, (number2 % 10) + 3);
        }

        r1 = f1(number1, number2, number3, number4, number5, number6, number7, number8, number9);
        r2 = f2(number3, number5, number7, number9, number1 % 10);
        int r3 = f2(number3, number5, number7, number9, number6 % 10);
        int r4 = f2(number3, number5, number7, number9, (number2 % 10) + 3);

        // If X1 = X2 = X3 = X4, return true
        if (r1 == r2 && r2 == r3 && r3 == r4) {
            success = true;
        }
    }

    // Create output
    std::vector<int> numbers = { number1, number2, number3, number4, number5, number6, number7, number8, number9 };
    std::string result = convertToString(numbers);
	return result;
}
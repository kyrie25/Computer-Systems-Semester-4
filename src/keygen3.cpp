#include "keygen.h"

std::string keygen3(const std::string &input)
{
    if (input.length() <= 4)
    {
        std::cout << "Input string is too short. Please provide a longer string." << std::endl;
        return "";
    }

    std::string firstHalf, secondhalf;

    // Step 1: Get sum of all ASCII values of the input string
    int sum = 0;
    for (char c : input)
    {
        sum += static_cast<int>(c);
    }

    // Step 2: XOR length of input powered by 3 to sum
    int length = input.length();
    length = std::pow(length, 3);
    length = length ^ sum;

    // Step 3: Get first and last character of input, multiply them, then power by 2. Afterwards, XOR then with B221
    char firstChar = input[0];
    char lastChar = input[input.length() - 1];
    int firstLastProduct = static_cast<int>(firstChar) * static_cast<int>(lastChar);
    firstLastProduct = std::pow(firstLastProduct, 2);
    firstLastProduct = firstLastProduct ^ 0xB221;

    // Step 4: Divide product by length;
    int res = firstLastProduct / length;

    // Step 5: Concatenate the two results and convert to string
    firstHalf = std::to_string(res);
    secondhalf = std::to_string(firstLastProduct);

    return firstHalf + '-' + secondhalf;
}
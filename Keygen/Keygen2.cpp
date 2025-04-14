#include "Keygen.h"

std::string keygen2(const std::string& input, std::string& error)
{
	// Error check
	int size = 0;
	for (char i : input){
		if (isalpha(i)) size++;
	}
	if (size < 5) {
		error = "Username must have at least 5 alphabetical characters.";
		return "";
	}

	std::string userName = input;

	// Uppercase lowercase letters
	for (int i = 0; i < userName.size(); i++){
        if (userName[i] >= 97 && userName[i] <= 122){
            userName[i] -= 32;
        }
    }

	// Remove non-alphabetical letters
	for (int i = 0; i < userName.size(); i++){
        if (!isalpha(userName[i])){
            userName.erase(i, 1);
            i--;
        }
    }

	// Step 1: Hash the first 5 alphabetical letters of username into an int
	int result = 0;         
    for (int i = 0; i <= 4; i++){
        result = result * 26 + (userName[i] - 'A');
    }

	// Step 2: Compute the indicies needed for each part of the serial to hash into the same number as the username hash result
	std::vector<int> indicies(5, 0);
	for (int i = 0; i < indicies.size(); i++){
		indicies[i] = result % 36;
		result /= 36;
	}

	// Step 3: Create serial using the calculated indicies
	std::string serial;													   // Hold result
	std::string LKTable = "AGMSY4BHNTZ5CIOU06DJPV17EKQW28FLRX39";          // Look up table for mapping characters in each part
	int start = 0, end = 4;												   // Indicies to iterate in each part

	// Loop to create each part of the result
	int loopSize = 4;
	while (loopSize--){
		for (int i = end; i >= start; i--){
			char mappedChar = LKTable[indicies[end - i]];
			serial.push_back(mappedChar);
		}

		// Update indicies for iteration
		start += 6;
		end += 6;
		
		// Add seperator
		if (loopSize) serial.push_back('-');

		// Update look up table
		std::string temp = LKTable.substr(0, 6);
		LKTable = LKTable.erase(0, 6) + temp;
	}

	return serial;
}
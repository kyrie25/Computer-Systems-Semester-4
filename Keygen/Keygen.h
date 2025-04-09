#pragma once

#include "resource.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <bitset>
#include <map>
#include <functional>
#include <unordered_map>
#include <cmath>

std::string keygen1(const std::string& input, std::string& error);
std::string keygen2(const std::string& input, std::string& error);
std::string keygen3(const std::string& input, std::string& error);

const std::unordered_map<int, std::function<std::string(const std::string& input, std::string& error)>> keygen_map = {
	{1, keygen1},
	{2, keygen2},
	{3, keygen3}
};
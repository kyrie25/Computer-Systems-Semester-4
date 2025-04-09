#pragma once
#ifndef KEYGEN_H
#define KEYGEN_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <bitset>
#include <map>
#include <functional>

std::string keygen1(const std::string &input);
std::string keygen2(const std::string &input);
std::string keygen3(const std::string &input);

const std::unordered_map<int, std::function<std::string(const std::string &input)>> keygen_map = {
    {1, keygen1},
    {2, keygen2},
    {3, keygen3}};

#endif // KEYGEN_H
#include "Keygen.h"

void GenerateKey(int option, const std::string& name, std::string& serial, std::string& error)
{
	serial = keygen_map.at(option)(name, error);
}
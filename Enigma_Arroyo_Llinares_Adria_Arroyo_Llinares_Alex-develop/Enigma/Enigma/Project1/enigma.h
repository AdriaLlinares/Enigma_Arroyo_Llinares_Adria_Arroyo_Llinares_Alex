#pragma once
#include <string>
#include "Rotor.h"

std::string cifrar(const std::string& texto,Rotor& r1, Rotor& r2, Rotor& r3, int pos1, int pos2, int pos3);

std::string descifrar(const std::string& texto, Rotor& r1, Rotor& r2, Rotor& r3, int pos1, int pos2, int pos3);

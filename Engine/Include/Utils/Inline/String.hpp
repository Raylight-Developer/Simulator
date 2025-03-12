#pragma once

#include <string>

#include "Glm.hpp"
#include "Types.hpp"

using namespace std;

// STRING

inline dvec1  str_to_d (const string& val_1) { return stod(val_1); }
inline dvec2  str_to_d (const string& val_1, const string& val_2) { return dvec2(stod(val_1), stod(val_2)); }
inline dvec3  str_to_d (const string& val_1, const string& val_2, const string& val_3) { return dvec3(stod(val_1), stod(val_2), stod(val_3)); }
inline dvec4  str_to_d (const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return dvec4(stod(val_1), stod(val_2), stod(val_3), stod(val_4)); }

inline ivec1  str_to_i (const string& val_1) { return stoi(val_1); }
inline ivec2  str_to_i (const string& val_1, const string& val_2) { return ivec2(stoi(val_1), stoi(val_2)); }
inline ivec3  str_to_i (const string& val_1, const string& val_2, const string& val_3) { return ivec3(stoi(val_1), stoi(val_2), stoi(val_3)); }
inline ivec4  str_to_i (const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return ivec4(stoi(val_1), stoi(val_2), stoi(val_3), stoi(val_4)); }
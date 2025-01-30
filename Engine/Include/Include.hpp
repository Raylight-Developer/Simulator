#pragma once

#include <unordered_map>
#include <unordered_set>
#include <type_traits>
#include <filesystem>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <optional>
#include <cstdlib>
#include <cstddef>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <sstream>
#include <variant>
#include <cerrno>
#include <chrono>
#include <future>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <array>
#include <regex>
#include <tuple>
#include <any>
#include <map>
#include <set>

#include <windows.h>
#include <math.h>
#include <omp.h>

#include <QtWidgets>
#include <QtCharts>
#include <QtCore>
#include <QtGui>

using namespace std;

typedef std::byte      Byte;
typedef vector<Byte>   Byte_Array;
typedef vector<string> Tokens;
typedef vector<Tokens> Token_Array;

typedef chrono::high_resolution_clock::time_point timestamp;

// INT
typedef int8_t              int8; // min: -128 | max: 127
typedef int16_t            int16; // min: -32'768 | max: 32'767
typedef int32_t            int32; // min: -2'147'483'648 | max: 2'147'483'647
typedef int64_t            int64; // min: -9'223'372'036'854'775'808 | max: 9'223'372'036'854'775'807

// UINT
typedef uint32_t             uint; //max: 4'294'967'295
typedef uint8_t             uint8; //max: 255
typedef uint16_t           uint16; //max: 65'535
typedef uint32_t           uint32; //max: 4'294'967'295
typedef uint64_t           uint64; //max: 18'446'744'073'709'551'615

#define SOLUTION_DIR string("D:/Extensible Cpp/")

#ifdef _DEBUG
#define BUILD_DIR (std::filesystem::current_path().parent_path().string() + "/x64/Debug/")
#else
#define BUILD_DIR (std::filesystem::current_path().parent_path().string() + "/x64/Release/")
#endif

#undef interface
#pragma once

#include "Import.hpp"

using namespace std;

typedef std::byte      Byte;
typedef vector<Byte>   Byte_Array;
typedef vector<string> Tokens;
typedef vector<Tokens> Token_Array;

// FLOATING

typedef double     dvec1; // 64-bits | min: 2.2250738585072014e-308 | max: 1.7976931348623158e+308

typedef glm::dvec2 dvec2; // 128-bits
typedef glm::dvec3 dvec3; // 196-bits
typedef glm::dvec4 dvec4; // 256-bits

typedef glm::dquat dquat; // 256-bits

typedef glm::dmat2 dmat2; // 256-bits
typedef glm::dmat3 dmat3; // 576-bits
typedef glm::dmat4 dmat4; // 1024-bits

//typedef float     vec1; // 32-bits | min: 1.175494351e-38f | max: 3.402823466e+38f
//typedef glm::vec2 vec2; // 64-bits
//typedef glm::vec3 vec3; // 96-bits
//typedef glm::vec4 vec4; // 128-bits
//typedef glm::quat quat; // 128-bits
//typedef glm::mat2 mat2; // 128-bits
//typedef glm::mat3 mat3; // 288-bits
//typedef glm::mat4 mat4; // 512-bits

// INT

typedef int8_t              int8; // min: -128 | max: 127
typedef int16_t            int16; // min: -32'768 | max: 32'767
typedef int32_t            int32; // min: -2'147'483'648 | max: 2'147'483'647
typedef int64_t            int64; // min: -9'223'372'036'854'775'808 | max: 9'223'372'036'854'775'807

typedef int64              ivec1; // 64-bits
typedef glm::tvec2<int64>  ivec2; // 128-bits
typedef glm::tvec3<int64>  ivec3; // 192-bits
typedef glm::tvec4<int64>  ivec4; // 256-bits

// UINT

typedef uint32_t             uint; //max: 4'294'967'295
typedef uint8_t             uint8; //max: 255
typedef uint16_t           uint16; //max: 65'535
typedef uint32_t           uint32; //max: 4'294'967'295
typedef uint64_t           uint64; //max: 18'446'744'073'709'551'615
#pragma once

#include "Import.hpp"
#include "Types.hpp"

inline dvec1 i_to_d (const ivec1& val) { return static_cast<dvec1> (val); }
inline dvec2 i_to_d (const ivec2& val) { return static_cast<dvec2> (val); }
inline dvec3 i_to_d (const ivec3& val) { return static_cast<dvec3> (val); }
inline dvec4 i_to_d (const ivec4& val) { return static_cast<dvec4> (val); }

inline ivec1 d_to_i (const dvec1& val) { return static_cast<ivec1> (val); }
inline ivec2 d_to_i (const dvec2& val) { return static_cast<ivec2> (val); }
inline ivec3 d_to_i (const dvec3& val) { return static_cast<ivec3> (val); }
inline ivec4 d_to_i (const dvec4& val) { return static_cast<ivec4> (val); }
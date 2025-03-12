#pragma once

#include "pch.h"

#include "Include.hpp"

#include "Scripting.hpp"

#undef LOG
#undef FLUSH
#undef SESSION

#define SCRIPT NODE::NODES::EXEC::Script
#define EXPORT(cls_name) extern "C" __declspec(dllexport) cls_name* scriptInstance() { return new cls_name(); }

typedef NODE::Port Port;
typedef NODE::PORT::Data_I Data_I;
typedef NODE::PORT::Data_O Data_O;
typedef NODE::PORT::Exec_I Exec_I;
typedef NODE::PORT::Exec_O Exec_O;
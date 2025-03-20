#pragma once

#include "pch.h"

#include "KL.hpp"

#include "Scripting.hpp"

#undef LOG
#undef FLUSH
#undef SESSION

#define SCRIPT NODES::SCRIPT::Script
#define EXPORT(cls_name) extern "C" __declspec(dllexport) cls_name* scriptInstance() { return new cls_name(); }

#define LOG this->session->log()
#define FLUSH this->session->flush()

typedef NODE::Port Port;
typedef NODE::PORT::Data_I Data_I;
typedef NODE::PORT::Data_O Data_O;
typedef NODE::PORT::Exec_I Exec_I;
typedef NODE::PORT::Exec_O Exec_O;
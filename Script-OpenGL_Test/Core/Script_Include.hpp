#pragma once

#include "pch.h"

#include "KL.hpp"

#include "OpenGL.hpp"
#include "Scripting.hpp"

#undef GL
#undef LOG
#undef FLUSH
#undef PRINT
#undef SESSION

#define SCRIPT NODES::SCRIPT::Script
#define EXPORT(cls_name) extern "C" __declspec(dllexport) cls_name* scriptInstance() { return new cls_name(); }

#define GL this->session->gl()
#define LOG this->session->log()
#define FLUSH this->session->flush()
#define PRINT(msg) this->session->printer() msg; printf(this->session->printer().str().c_str()); this->session->printer().clear()

using Port = NODE::Port;
using Data_I = NODE::PORT::Data_I;
using Data_O = NODE::PORT::Data_O;
using Exec_I = NODE::PORT::Exec_I;
using Exec_O = NODE::PORT::Exec_O;
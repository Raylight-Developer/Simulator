#pragma once

#include "pch.h"

#include "KL.hpp"

#include "OpenGL.hpp"
#include "Session.hpp"
#include "Viewport.hpp"
#include "Scripting.hpp"

#undef GL
#undef LOG
#undef FLUSH
#undef PRINT
#undef SESSION

#undef DATA_I
#undef DATA_O
#undef EXEC_I
#undef EXEC_O

#define SCRIPT NODES::SCRIPT::Script
#define SCRIPT_INIT Session::initialize(this->session);

#define EXPORT(cls_name) extern "C" __declspec(dllexport) cls_name* scriptInstance(Session* session) { return new cls_name(session); }

#define GL this->session->gl
#define LOG this->session->log
#define FLUSH this->session->flush()
#define PRINT(msg) this->session->printer msg; printf(this->session->printer.str().c_str()); this->session->printer.clear()

using Port = NODE::Port;
using Data_I = NODE::PORT::Data_I;
using Data_O = NODE::PORT::Data_O;
using Exec_I = NODE::PORT::Exec_I;
using Exec_O = NODE::PORT::Exec_O;

#define DATA_I(label, type) new Data_I(this, label, type);
#define DATA_O(label, type) new Data_O(this, label, type);
#define EXEC_I(label) new Exec_I(this, label);
#define EXEC_O(label) new Exec_O(this, label);
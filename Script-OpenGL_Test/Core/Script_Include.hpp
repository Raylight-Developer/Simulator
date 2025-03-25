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

#define SCRIPT NODES::SCRIPT::Script
#define SCRIPT_INIT(name) Script::Script(Session* session) : SCRIPT(name) {\
	this->session = session;\
	Session::getInstance().gl = this->session->gl;\
	Session::getInstance().viewport = this->session->viewport;\
}

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
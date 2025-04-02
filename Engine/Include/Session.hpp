#pragma once

#include "KL.hpp"

#include "File.hpp"
#include "Node.hpp"
#include "Nodes.hpp"
#include "Variable.hpp"
#include "Scripting.hpp"

struct Viewport;

struct Session : KL::Session {
	static Session* session_ptr;

	static void initialize(Session* session);

	static void destroy();

	QOpenGLFunctions_4_5_Core* gl;
	GUI::Window* window;
	Viewport* viewport;

	int64 current_frame;
	int64 samples;
	Timestamp start;
	bool active;
	bool realtime;

	File file;

	KL::U_Map<QString, Variable> variables;
	KL::U_Map<QString, KL::List<Node*>> variable_refs;

	KL::List<NODES::SCRIPT::Script*> scripts;
	KL::U_Map<NODES::SCRIPT::Script*, HINSTANCE> dlls;

	Session();
	~Session() = default;
	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;
};

#define SESSION Session::session_ptr
#define PRINT(msg) SESSION->printer msg; printf(SESSION->printer.str().c_str()); SESSION->printer.clear()
#define FILE SESSION->file
#define GL SESSION->gl
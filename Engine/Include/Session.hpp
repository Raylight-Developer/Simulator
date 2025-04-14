#pragma once

#include "KL.hpp"

#include "File.hpp"
#include "Node.hpp"
#include "Nodes.hpp"
#include "Variable.hpp"
#include "Scripting.hpp"

struct Viewport;

struct Session : CORE::Session {
	U16 major_version, minor_version, patch_version;
	static Session* session_ptr;

	static void initialize(Session* session);

	static void destroy();

	QOpenGLFunctions_4_5_Core* gl;
	GUI::Window* window;
	Viewport* viewport;

	I64 current_frame;
	I64 samples;
	Timestamp start;
	bool active;
	bool realtime;

	File file;

	CORE::UMap<QString, Variable> variables;
	CORE::UMap<QString, CORE::Stack<Ptr_S<Node>>> variable_refs;

	CORE::Stack<NODES::SCRIPT::Script*> scripts;
	CORE::UMap<NODES::SCRIPT::Script*, HINSTANCE> dlls;

	Session();
	~Session() = default;
	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;
};

#define SESSION Session::session_ptr

#define H_PUSH(command) SESSION->history.execute(command)
#define H_UNDO(count)   SESSION->history.undo(count)
#define H_REDO(count)   SESSION->history.redo(count)
#define LOG   SESSION->buffer
#define FLUSH SESSION->flushLog()

#define LOGL(msg) LOG NL msg; FLUSH

#define PRINT(msg) SESSION->printer msg; printf(SESSION->printer.str().c_str()); SESSION->printer.clear()
#define FILE SESSION->file
#define GL SESSION->gl
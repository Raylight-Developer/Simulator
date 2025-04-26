#pragma once

#include "KL.hpp"

#include "File.hpp"
#include "Node.hpp"
#include "Nodes.hpp"
#include "Window.hpp"
#include "Variable.hpp"
#include "Scripting.hpp"

struct Viewport;

enum struct Playback_Mode {
	REALTIME,
	O_STOPPED,
	STOPPED,
	PLAYING,
	O_RESET,
	RESET
};

struct Hook {
	F64_V2 viewport_resolution;
	F64_V2 mouse_pos;
	bool mouse_on_screen;
	T_V2<I32> mouse_wheel;
	CORE::UMap<string, bool> input_down;

	Timestamp playback_start;
	U64 current_frame;

	Hook();
};

struct Session : CORE::Session {
	U16 major_version, minor_version, patch_version;
	static Session* session_ptr;

	static void initialize(Session* session);

	static void destroy();

	QOpenGLFunctions_4_5_Core* gl;
	Window* window;
	Viewport* viewport;

	I64 samples;
	Playback_Mode playback_mode;

	Hook hook;
	File file;

	Session();
	~Session() = default;
	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;
};

#define SESSION Session::session_ptr

#define H_BUFFER_GROUP(count) SESSION->history.buffer_group(count)
#define H_PUSH(command) SESSION->history.execute(command)
#define H_GROUP(count)  SESSION->history.group(count)
#define H_UNDO          SESSION->history.undo()
#define H_REDO          SESSION->history.redo()
#define LOG   SESSION->buffer
#define FLUSH SESSION->flushLog()

#define LOGL(msg) LOG NL msg; FLUSH

#define PRINT(msg) SESSION->printer msg; printf(SESSION->printer.str().c_str()); SESSION->printer.clear()
#define FILE SESSION->file
#define GL SESSION->gl
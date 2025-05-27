#pragma once

#include "KL.hpp"

#include "File.hpp"
#include "Node.hpp"
#include "Nodes.hpp"
#include "Window.hpp"
#include "Variable.hpp"
#include "3D_Camera.hpp"
#include "Scripting.hpp"

struct Viewport;

enum struct Playback_Mode {
	REALTIME,
	STOPPED,
	PLAYING,
	RESET
};

struct Hook {
	F64_V2 viewport_resolution;
	F64_V2 camera_pos_2d;
	F64 camera_zoom_2d;
	F64 pixel_ratio;
	F64 delta_time;
	F64 exec_time;

	Camera_3D camera_3d;

	F64_V2 mouse_pos;
	bool mouse_on_screen;
	T_V2<I32> mouse_wheel;
	CORE::UMap<string, bool> input_down;

	Timestamp playback_start;
	F64 playback_delta_time;
	U64 current_frame;
	I64 samples;
	Playback_Mode playback_mode;

	CORE::UMap<void*, function<void(const F64_V2&)>> onWheel;
	CORE::UMap<void*, function<void(const string&)>> onKeyUp;
	CORE::UMap<void*, function<void(const string&)>> onKeyDown;

	CORE::UMap<void*, function<void()>> onInit;
	CORE::UMap<void*, function<void(const F64&)>> onTick;
	CORE::UMap<void*, function<void(QPainter*)>> onGuiRender;

	Hook();

	F64 getDeltaTime() const;
};

struct Session : CORE::Session {
	static Session* session_ptr;
	static void initialize(Session* session);
	static void destroy();

	U16 major_version, minor_version, patch_version;

	Window* window;
	Viewport* viewport;
	QOpenGLFunctions_4_5_Core* gl;
	vector<function<void()>> gl_2d_callbacks;
	vector<function<void()>> gl_3d_callbacks;

	Hook hook;
	File file;

	Session();
	~Session() = default;
	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;
};

#define SESSION Session::session_ptr
#define SIM_HOOK SESSION->hook

#define H_BUFFER_GROUP(count) SESSION->history.buffer_group(count)
#define H_PUSH(command) SESSION->history.execute(command)
#define H_GROUP(count)  SESSION->history.group(count)
#define H_UNDO          SESSION->history.undo()
#define H_REDO          SESSION->history.redo()
#define LOG   SESSION->buffer
#define FLUSH SESSION->flushLog()

#define LOGL(msg) LOG NL msg; FLUSH

#define FILE SESSION->file
#define GL SESSION->gl
#define GL_2D_FUNC SESSION->gl_2d_callbacks
#define GL_3D_FUNC SESSION->gl_3d_callbacks
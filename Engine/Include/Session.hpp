#pragma once

#include "KL.hpp"

#include "File.hpp"
#include "Node.hpp"
#include "Nodes.hpp"
#include "Scripting.hpp"

struct Session : KL::Session {
	static Session& getInstance();

	QOpenGLFunctions_4_5_Core* gl;
	uvec2 viewport_resolution;

	File file;

	QMap<QString, NODES::SCRIPT::Script*> scripts;
	QMap<NODES::SCRIPT::Script*, HINSTANCE> dlls;

	Session();
	~Session() = default;
	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;
};

#define SESSION Session::getInstance()
#define PRINT(msg) SESSION.printer msg; printf(SESSION.printer.str().c_str()); SESSION.printer.clear()
#define FILE SESSION.file
#define GL SESSION.gl
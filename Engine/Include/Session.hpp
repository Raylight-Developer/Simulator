#pragma once

#include "KL.hpp"

#include "Node.hpp"
#include "Nodes.hpp"
#include "Scripting.hpp"

struct Session : KL::Session {
	static Session& getInstance();

	QMap<QString, NODES::SCRIPT::Script*> scripts;
	QMap<NODES::SCRIPT::Script*, HINSTANCE> dlls;

	Session();
	~Session() = default;
	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;
};

#define SESSION Session::getInstance()
#define FILE
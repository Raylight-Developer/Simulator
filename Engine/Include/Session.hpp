#pragma once

#include "Include.hpp"

// FWD DECL OTHER
namespace CORE {
	class Lace;
}

// FWD DECL THIS

// DECL
namespace CORE {
	struct Session {
		Lace log;
		static Session& getInstance();
		void flushLog();

		Session();
		~Session() = default;
		Session(const Session&) = delete;
		Session& operator=(const Session&) = delete;
	};
}

#define SESSION CORE::Session::getInstance()
#define SESSION_LOG   CORE::Session::getInstance().log
#define SESSION_FLUSH CORE::Session::getInstance().flushLog()

#define FILE
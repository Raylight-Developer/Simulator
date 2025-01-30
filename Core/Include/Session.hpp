#pragma once

#include "Lace.hpp"

// FWD DECL OTHER
namespace CORE {
	class Lace;
}

// FWD DECL THIS

// DECL
namespace CORE {
	class Session {
	public:
		Lace log;
		static Session& getInstance();
		void flushLog();
	private:
		Session();
		~Session() = default;
		Session(const Session&) = delete;
		Session& operator=(const Session&) = delete;

		friend class Window;
		friend class Script_Manager;
	};
}

#define SESSION CORE::Session::getInstance()
#define LOG     CORE::Session::getInstance().log
#define FLUSH   CORE::Session::getInstance().flushLog()
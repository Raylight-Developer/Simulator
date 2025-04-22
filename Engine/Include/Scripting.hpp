#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

struct Session;

namespace NODES {
	namespace SCRIPT {
		struct Script : Node {
			Session* session;

			Script(const QString& id, Session* session);
			~Script();

			void execAllDownstream() const;

			void exec(const Port* port) final override;
			Variable getData(const Port* port) const final override;

			virtual void exec(const PORT::Exec_I* port);
			virtual Variable getData(const PORT::Data_O* port) const;

			virtual void onLoad() = 0;
			virtual void onUnload() = 0;
		};

		void loadDLL(HINSTANCE& dynlib, const QString& dll_path);
		void unloadDLL(HINSTANCE& dynlib);

		Script* loadScript(const QString& dll_path);
		void reloadScript(Script* script);
		void unloadScript(Script* script);
	}
}
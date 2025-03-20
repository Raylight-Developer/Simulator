#pragma once

#include "KL.hpp"

#include "Node.hpp"

struct Session;
namespace NODES {
	namespace SCRIPT {
		struct Script;
	}
}

namespace NODES {
	namespace SCRIPT {
		namespace SCRIPT_LAYER {
			class SL_Session {
			private:
				Session* session;
			public:
				SL_Session(Script* script = nullptr, Session* session = nullptr);

				KL::Lace& log();
				void flush();
			};
		}

		struct Script : Node {
			SCRIPT_LAYER::SL_Session* session;

			Script(const QString& id);
			~Script();

			virtual void onLoad() {}
			virtual void onUnload() {}
		};

		void loadDLL(HINSTANCE& dynlib, const QString& dll_path);
		void unloadDLL(HINSTANCE& dynlib);

		void loadScript  (const QString& dll_path);
		void reloadScript(const QString& dll_path);
		void unloadScript(const QString& dll_path);
	}
}
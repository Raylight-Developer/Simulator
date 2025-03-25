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

				KL::Lace& log() const;
				KL::Lace& printer() const;
				QOpenGLFunctions_4_5_Core* gl() const;

				uvec2 viewportResolution() const;

				dvec1 viewport2DZoom() const;
				dvec2 viewport2DCenter() const;

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

		Script* loadScript(const QString& dll_path);
		void reloadScript(Script* script);
		void unloadScript(Script* script);
	}
}
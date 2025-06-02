#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

#include "Node.hpp"

using namespace NODE;

struct Session;

namespace NODES {
	namespace SCRIPT {

		struct Script : Node {
			Session* session;

			Script(const QString& id, Session* session);
			virtual ~Script();

			void execAllDownstream() const;
			bool missingInputs() const;

			void exec(const Port* port) final override;
			Ptr_S<Variable> getData(const Port* port) final override;

			virtual void exec(const PORT::Exec_I* port);
			virtual Ptr_S<Variable> getData(const PORT::Data_O* port);

			void saveDetail(CORE::Lace& lace) const override;

			virtual void onLoad() = 0;
			virtual void onUnload() = 0;

		private:
			QString path;

			friend Script* loadScript(const QString& dll_path); 
		};

		void loadDLL(HINSTANCE& dynlib, const QString& dll_path);
		void unloadDLL(HINSTANCE& dynlib);

		Script* loadScript(const QString& dll_path);
		void reloadScript(Script* script);
		void unloadScript(Script* script);
	}
}
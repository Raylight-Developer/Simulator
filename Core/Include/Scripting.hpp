#pragma once

#include "Include.hpp"

#include "Lace.hpp"

namespace CORE {
	class Session;
	class Script;
}

namespace SCRIPT_LAYER {
	class Session;

	class Session {
	private:
		CORE::Session* session;
	public:
		Session(CORE::Script* script = nullptr, CORE::Session* session = nullptr);

		CORE::Lace& log();
		void flush();
	};
}

namespace CORE {
	class Script : public QGraphicsItem {
	public:
		SCRIPT_LAYER::Session* session;

		Script() = default;
		virtual ~Script();

		virtual void onLoad() {}
		virtual void onUnload() {}
		QRectF boundingRect() const override;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
	};

	class Script_Manager {
		static void loadDLL(HINSTANCE& dynlib);
		static void recompileDLL(HINSTANCE& dynlib);
		static void unloadDLL(HINSTANCE& dynlib);
	};
}
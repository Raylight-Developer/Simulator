#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("GUI", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(60);
	rect.setHeight(40);

	SIM_HOOK.onGuiRender[this] = [this](QPainter* painter) {
		if (SESSION->viewport->frame_count >= 60) {
			painter->setPen(QColor(50, 255, 50));
		}
		else if (SESSION->viewport->frame_count >= 48) {
			painter->setPen(QColor(150, 255, 50));
		}
		else if (SESSION->viewport->frame_count >= 24) {
			painter->setPen(QColor(255, 150, 50));
		}
		else {
			painter->setPen(QColor(255, 50, 50));
		}
		painter->drawText(20, 20, "FPS:");
		painter->setPen(Qt::white);
		painter->drawText(65, 20, QString::number(SESSION->viewport->frame_count));
	};

	LOGL(<< "Loaded GUI Showcase Script");
}

void Script::onUnload() {
	SIM_HOOK.onGuiRender.remove(this);

	LOGL(<< "Unloaded GUI Showcase Script");
}
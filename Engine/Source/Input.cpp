#include "Input.hpp"

#include "Session.hpp"

bool Input::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		if (key_event->isAutoRepeat()) {
			return false;
		}
		const int key = key_event->key();
		if (!keys_held.contains(key)) {
			keys_held.insert(key);
			if (key_event->modifiers() == Qt::KeyboardModifier::ControlModifier) {
				if (key == Qt::Key::Key_Z) {
					H_UNDO;
					return false;
				}
				else if (key == Qt::Key::Key_Y) {
					H_REDO;
					return false;
				}
			}
		}
	}
	else if (event->type() == QEvent::KeyRelease) {
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		if (key_event->isAutoRepeat()) {
			return false;
		}
		keys_held.remove(key_event->key());
	}

	return QObject::eventFilter(obj, event);
}
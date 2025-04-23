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
			else if (key_event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) and key == Qt::Key::Key_Z) {
				H_REDO;
				return false;
			}
			SESSION->hook.input_down[qtKey(key_event->key())] = true;
		}
	}
	else if (event->type() == QEvent::KeyRelease) {
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		if (key_event->isAutoRepeat()) {
			return false;
		}
		keys_held.remove(key_event->key());
		SESSION->hook.input_down[qtKey(key_event->key())] = false;
	}

	if (event->type() == QEvent::MouseMove) {
		if (SESSION->window->viewport->underMouse()) {
			SESSION->hook.mouse_on_screen = true;
		}
		else {
			SESSION->hook.mouse_on_screen = false;
		}
	}

	return QObject::eventFilter(obj, event);
}
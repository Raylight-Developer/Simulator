#include "Input.hpp"

#include "Session.hpp"

bool Input::eventFilter(QObject* obj, QEvent* event) {
	switch (event->type()) {
		case QEvent::KeyPress: {
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
			break;
		}
		case QEvent::KeyRelease: {
			QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
			if (key_event->isAutoRepeat()) {
				return false;
			}
			keys_held.remove(key_event->key());
			SESSION->hook.input_down[qtKey(key_event->key())] = false;
			break;
		}
		case QEvent::MouseMove: {
			if (SESSION->window->viewport->underMouse()) {
				SESSION->hook.mouse_on_screen = true;
			}
			else {
				SESSION->hook.mouse_on_screen = false;
			}
			break;
		}
		case QEvent::Wheel: {
			QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
			const QPoint scrollAmount = wheel_event->angleDelta();
			SESSION->hook.mouse_wheel.x = scrollAmount.x();
			SESSION->hook.mouse_wheel.y = scrollAmount.y();
			break;
		}
	}

	return QObject::eventFilter(obj, event);
}
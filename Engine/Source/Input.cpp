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
				else if (key_event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && key == Qt::Key::Key_Z) {
					H_REDO;
					return false;
				}

				const auto key = qtKey(key_event->key());

				if (SIM_HOOK.playback_mode == Playback_Mode::REALTIME || SIM_HOOK.playback_mode == Playback_Mode::PLAYING) {
					SIM_HOOK.input_down[key] = true;
					for (auto& [k, f] : SIM_HOOK.onKeyDown) {
						f(key);
					}
				}
			}
			break;
		}
		case QEvent::KeyRelease: {
			QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
			if (key_event->isAutoRepeat()) {
				return false;
			}
			keys_held.remove(key_event->key());
			const auto key = qtKey(key_event->key());

			if (SIM_HOOK.playback_mode == Playback_Mode::REALTIME || SIM_HOOK.playback_mode == Playback_Mode::PLAYING) {
				SIM_HOOK.input_down[key] = false;
				for (auto& [k, f] : SIM_HOOK.onKeyUp) {
					f(key);
				}
			}
			break;
		}
		case QEvent::MouseButtonPress: {
			QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
			const auto button = qtKey(mouse_event->button());

			if (SIM_HOOK.playback_mode == Playback_Mode::REALTIME || SIM_HOOK.playback_mode == Playback_Mode::PLAYING) {
				SIM_HOOK.input_down[button] = true;
				for (auto& [k, f] : SIM_HOOK.onKeyDown) {
					f(button);
				}
			}
			break;
		}
		case QEvent::MouseButtonRelease: {
			QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
			const auto button = qtKey(mouse_event->button());

			if (SIM_HOOK.playback_mode == Playback_Mode::REALTIME || SIM_HOOK.playback_mode == Playback_Mode::PLAYING) {
				SIM_HOOK.input_down[button] = false;
				for (auto& [k, f] : SIM_HOOK.onKeyUp) {
					f(button);
				}
			}
			break;
		}
		case QEvent::MouseMove: {
			QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
			if (SESSION->window->viewport->underMouse()) {
				SIM_HOOK.mouse_on_screen = true;
			}
			else {
				SIM_HOOK.mouse_on_screen = false;
			}
			SIM_HOOK.mouse_pos = p_to_d(mouse_event->position()) * SIM_HOOK.pixel_ratio;
			break;
		}
	}
	return QObject::eventFilter(obj, event);
}
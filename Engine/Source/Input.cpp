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
					/*
					if (SESSION->history.group_undo_stack.empty()) return false;
					if (SESSION->history.group_undo_stack.back() > 1) {
						LOGL(<< "Undo: [" << SESSION->history.group_undo_stack.back() << "] Actions");
						LOG++;
						for (U16 i = 0; i < SESSION->history.group_undo_stack.back(); i++) {
							LOGL(<< SESSION->history.undo_stack[SESSION->history.undo_stack.size() - 1 - i]->info);
						}
						LOG--;
					}
					else {
						LOGL(<< "Undo: " << SESSION->history.undo_stack.back()->info);
					}
					*/
					H_UNDO;
					return false;
				}
				else if (key == Qt::Key::Key_Y) {
					/*
					if (SESSION->history.group_redo_stack.empty()) return false;
					if (SESSION->history.group_redo_stack.back() > 1) {
						LOGL(<< "Redo: [" << SESSION->history.group_redo_stack.back() << "] Actions");
						LOG++;
						for (U16 i = 0; i < SESSION->history.group_redo_stack.back(); i++) {
							LOGL(<< SESSION->history.redo_stack[SESSION->history.redo_stack.size() - 1 - i]->info);
						}
						LOG--;
					}
					else {
						LOGL(<< "Redo: " << SESSION->history.redo_stack.back()->info);
					}
					*/
					H_REDO;
					return false;
				}
			}
			else if (key_event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) and key == Qt::Key::Key_Z) {
				H_REDO;
				return false;
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
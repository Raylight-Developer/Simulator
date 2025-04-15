#include "Input.hpp"

#include "Session.hpp"

bool Input::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		if (key_event->modifiers() == Qt::KeyboardModifier::ControlModifier) {
			if (key_event->key() == Qt::Key::Key_Z) {
				H_UNDO(1);
				return false;
			}
			else if (key_event->key() == Qt::Key::Key_Y) {
				H_REDO(1);
				return false;
			}
		}
	}

	return QObject::eventFilter(obj, event);
}
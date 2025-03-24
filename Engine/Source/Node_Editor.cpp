#include "Node_Editor.hpp"

#include "Session.hpp"

Node_Editor::Node_Editor(QWidget* parent) :
	GUI::Graphics_View(parent)
{
	scene = new GUI::Graphics_Scene(this);
	setScene(scene);

	selection_rect = new QGraphicsRectItem(QRectF(0, 0, 0, 0));
	selection_rect->setBrush(QColor(255, 135, 25, 50));
	selection_rect->setPen(QPen(QColor(255, 135, 25, 200), 2.5));
	selection_rect->setZValue(10);
	selection_rect->hide();

	creating_connection = nullptr;

	scene->addItem(selection_rect);

	scene->addItem(FILE.tick.pointer);
	FILE.tick.pointer->setPos(QPointF(0,0));
}

Node_Editor::~Node_Editor() {
	delete creating_connection;
	delete selection_rect;
}

void Node_Editor::drawBackground(QPainter* painter, const QRectF& rect) {
	QGraphicsView::drawBackground(painter, rect);

	constexpr qreal smallGridSpacing = 10.0;
	constexpr qreal majorGridSpacing = smallGridSpacing * 10;

	qreal left = int(rect.left()) - int(rect.left()) % int(smallGridSpacing);
	qreal right = int(rect.right());
	qreal top = int(rect.top()) - int(rect.top()) % int(smallGridSpacing);
	qreal bottom = int(rect.bottom());

	if (transform().m11() > 0.6) {
		for (qreal x = left; x <= right; x += smallGridSpacing) {
			bool isMajorLine = (int(x) % int(majorGridSpacing) == 0);
			QPen gridPen(isMajorLine ? QColor(255, 255, 255) : QColor(150, 150, 150), isMajorLine ? 0.2 : 0.1);
			painter->setPen(gridPen);
			painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
		}

		for (qreal y = top; y <= bottom; y += smallGridSpacing) {
			bool isMajorLine = (int(y) % int(majorGridSpacing) == 0);
			QPen gridPen(isMajorLine ? QColor(255, 255, 255) : QColor(150, 150, 150), isMajorLine ? 0.2 : 0.1);
			painter->setPen(gridPen);
			painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
		}
	}
	else {
		for (qreal x = left; x <= right; x += smallGridSpacing) {
			if (int(x) % int(majorGridSpacing) == 0) {
				QPen gridPen(QColor(255, 255, 255), 0.2);
				painter->setPen(gridPen);
				painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
			}
		}

		for (qreal y = top; y <= bottom; y += smallGridSpacing) {
			if (int(y) % int(majorGridSpacing) == 0) {
				QPen gridPen(QColor(255, 255, 255), 0.2);
				painter->setPen(gridPen);
				painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
			}
		}
	}
}

void Node_Editor::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::MouseButton::RightButton) {
		moving = false;
		setCursor(Qt::ArrowCursor);
	}
	if (event->button() == Qt::MouseButton::LeftButton) {
		moving = false;
		setCursor(Qt::ArrowCursor);
		if (selecting) {
			for (auto item : scene->items(selection_rect->rect())) {
				if (Node* node = dynamic_cast<Node*>(item)) {
					if (!node->isSelected()) {
						node->setSelected(true);
						selection.push_back(node);
					}
				}
			}
			selecting = false;
			selection_rect->hide();
		}
		if (creating_connection) {
			if (auto item = dynamic_cast<NODE::Port*>(scene->itemAt(mapToScene(event->pos()), transform()))) {
				if (auto drop_port = dynamic_cast<NODE::PORT::Data_I*>(item)) {
					if (auto source_port = dynamic_cast<NODE::PORT::Data_O*>(creating_connection->port_l)) {
						if (source_port->node != drop_port->node) {
							auto new_conn = new NODE::Connection(source_port, drop_port);
							if (drop_port->requestConnection(new_conn) and source_port->requestConnection(new_conn)) {
								if (drop_port->connection) {
									delete drop_port->connection;
								}
								drop_port->connection = new_conn;
								source_port->connections.push_back(new_conn);
							}
							else {
								delete new_conn;
							}
						}
					}
				}
				else if (auto drop_port = dynamic_cast<NODE::PORT::Data_O*>(item)) {
					if (auto source_port = dynamic_cast<NODE::PORT::Data_I*>(creating_connection->port_l)) {
						if (source_port->node != drop_port->node) {
							auto new_conn = new NODE::Connection(drop_port, source_port);
							if (source_port->requestConnection(new_conn) and drop_port->requestConnection(new_conn)) {
								if (source_port->connection) {
									delete source_port->connection;
								}
								source_port->connection = new_conn;
								drop_port->connections.push_back(new_conn);
							}
							else {
								delete new_conn;
							}
						}
					}
				}
				else if (auto drop_port = dynamic_cast<NODE::PORT::Exec_I*>(item)) {
					if (auto source_port = dynamic_cast<NODE::PORT::Exec_O*>(creating_connection->port_l)) {
						if (source_port->node != drop_port->node) {
							auto new_conn = new NODE::Connection(source_port, drop_port);
							if (drop_port->requestConnection(new_conn) and source_port->requestConnection(new_conn)) {
								if (source_port->connection) {
									delete source_port->connection;
								}
								source_port->connection = new_conn; // TODO Not Working. connection being deleted somewhere.
								drop_port->connections.push_back(new_conn);
							}
							else {
								delete new_conn;
							}
						}
					}
				}
				else if (auto drop_port = dynamic_cast<NODE::PORT::Exec_O*>(item)) {
					if (auto source_port = dynamic_cast<NODE::PORT::Exec_I*>(creating_connection->port_l)) {
						if (source_port->node != drop_port->node) {
							auto new_conn = new NODE::Connection(drop_port, source_port);
							if (source_port->requestConnection(new_conn) and drop_port->requestConnection(new_conn)) {
								if (drop_port->connection) {
									delete drop_port->connection;
								}
								drop_port->connection = new_conn;
								source_port->connections.push_back(new_conn);
							}
							else {
								delete new_conn;
							}
						}
					}
				}
			}
			else {
				// TODO create context nodes
			}
			delete creating_connection;
			creating_connection = nullptr;
		};
	}
	GUI::Graphics_View::mouseReleaseEvent(event);
}

void Node_Editor::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::MouseButton::LeftButton) {
		if (auto item = scene->itemAt(mapToScene(event->pos()), transform())) {
			if (NODE::Port* port = dynamic_cast<NODE::Port*>(item)) {
				if (auto port_r = dynamic_cast<NODE::PORT::Data_I*>(port)) {
					if (!port_r->connection) {
						creating_connection = new NODE::Connection(port_r);
					}
					else {
						auto port_l = static_cast<NODE::PORT::Data_O*>(port_r->connection->port_l);
						delete port_r->connection;
						creating_connection = new NODE::Connection(port_l);
					}
				}
				else if (auto port_l = dynamic_cast<NODE::PORT::Exec_O*>(port)) {
					if (!port_l->connection) {
						creating_connection = new NODE::Connection(port_l);
					}
					else {
						auto port_r = static_cast<NODE::PORT::Exec_I*>(port_l->connection->port_r);
						delete port_l->connection;
						creating_connection = new NODE::Connection(port_r);
					}
				}
				else {
					creating_connection = new NODE::Connection(port);
				}
			}
			else if (Node* node = dynamic_cast<Node*>(item)) {
				moving = true;
				setCursor(Qt::ClosedHandCursor);
				if (event->modifiers() & Qt::KeyboardModifier::ShiftModifier) {
					if (!node->isSelected()) {
						node->setSelected(true);
						selection.push_back(node);
					}
					else {
						node->setSelected(false);
					}
				}
				else {
					if (!node->isSelected()) {
						for (auto item : selection) {
							item->setSelected(false);
						}
						selection.clear();
						node->setSelected(true);
						selection.push_back(node);
					}
				}
				move_pos = mapToScene(event->pos()) - node->pos();
			}
			else {
				for (auto item : selection) {
					item->setSelected(false);
				}
				selection.clear();
			}
		}
		else {
			for (auto item : selection) {
				item->setSelected(false);
			}
			selection.clear();

			selecting = true;
			selection_start = mapToScene(event->pos());
			selection_rect->setRect(QRectF(selection_start, QSizeF(0,0)));
			selection_rect->show();
		}
	}
	GUI::Graphics_View::mousePressEvent(event);
}

void Node_Editor::mouseMoveEvent(QMouseEvent* event) {
	if (event->modifiers() & Qt::KeyboardModifier::AltModifier) {
		if (auto item = scene->itemAt(mapToScene(event->pos()), transform())) {
			if (NODE::Port* port = dynamic_cast<NODE::Port*>(item)) {
				if (auto port_r = dynamic_cast<NODE::PORT::Data_I*>(item)) {
					if (port_r->connection) {
						auto port_l = static_cast<NODE::PORT::Data_O*>(port_r->connection->port_l);
						delete port_r->connection;
						port_l->disconnect();
						port_r->disconnect();
					}
				}
				else if (auto port_l = dynamic_cast<NODE::PORT::Data_O*>(item)) {
					for (auto conn : port_l->connections) {
						auto port_r = static_cast<NODE::PORT::Data_I*>(conn->port_r);
						delete conn;
						port_r->disconnect();
					}
					port_l->connections.clear();
					port_l->disconnect();
				}
				else if (auto port_r = dynamic_cast<NODE::PORT::Exec_I*>(item)) {
					for (auto conn : port_r->connections) {
						auto port_l = static_cast<NODE::PORT::Exec_O*>(conn->port_l);
						delete conn;
						port_l->disconnect();
					}
					port_r->connections.clear();
					port_r->disconnect();
				}
				else if (auto port_l = dynamic_cast<NODE::PORT::Exec_O*>(item)) {
					if (port_l->connection) {
						auto port_r = static_cast<NODE::PORT::Exec_I*>(port_l->connection->port_r);
						delete port_l->connection;
						port_l->disconnect();
						port_r->disconnect();
					}
				}
			}
		}
	}
	else {
		if (moving) {
			for (auto& node : selection) {
				const QPointF delta = mapToScene(event->pos()) - move_pos;
				node->setPos(KL::f_roundToNearest(delta.x(), 10.0), KL::f_roundToNearest(delta.y(), 10.0));
			}
		}
		if (selecting) {
			const QRectF newRect(selection_start, mapToScene(event->pos()));
			selection_rect->setRect(newRect.normalized());
		}
		if (creating_connection) {
			if (creating_connection->port_l) {
				creating_connection->updateR(mapToScene(event->pos()));
			}
			else {
				creating_connection->updateL(mapToScene(event->pos()));
			}
			creating_connection->update();
		}
	}
	GUI::Graphics_View::mouseMoveEvent(event);
}

void Node_Editor::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
		case Qt::Key_Delete: {
			for (Node* node : selection) {
				if (not dynamic_cast<NODES::EXEC::Euler_Tick*>(node)) {
					scene->removeItem(node);
					delete node;
				}
			}
			selection.clear();
			return;
		}
		case Qt::Key_R: {
			return;
		}
	}
	for (QWidget* widget : QApplication::topLevelWidgets()) {
		if (widget->inherits("QLineEdit") && widget->hasFocus()) {
			QApplication::sendEvent(widget, event);
		}
	}
	GUI::Graphics_View::keyPressEvent(event);
}

void Node_Editor::wheelEvent(QWheelEvent* event) {
	const QPoint scrollAmount = event->angleDelta();
	for (QWidget* widget : QApplication::topLevelWidgets()) {
		if (widget->inherits("QComboBox") && widget->isVisible()) {
			auto combo_box = static_cast<GUI::Options*>(widget);
			if (combo_box->view()->isVisible()) {
				if (scrollAmount.y() > 0) {
					combo_box->scrollBy(-1);
				}
				else if (scrollAmount.y() < 0) {
					combo_box->scrollBy(1);
				}
				return;
			}
		}
	}

	GUI::Graphics_View::wheelEvent(event);
}

void Node_Editor::dragMoveEvent(QDragMoveEvent* event) {
	event->acceptProposedAction();
}

void Node_Editor::dropEvent(QDropEvent* event) {
	const QPointF drop_pos = d_to_p(KL::f_roundToNearest(p_to_d(mapToScene(event->position().toPoint())), 10.0));
	if (event->mimeData()->hasText()) {
		Node* node = nullptr;

		if (event->mimeData()->text() == "NODE") {
			QByteArray itemDataType = event->mimeData()->data("Type");
			QDataStream dataStreamType(&itemDataType, QIODevice::ReadOnly);
			QString type;
			dataStreamType >> type;

			if (type == "ARITHMETIC") {
				node = new NODES::Arithmetic();
			}
			else if (type == "TRIGONOMETRY") {
				node = new NODES::Trigonometry();
			}
			else if (type == "INPUT INTEGER") {
				node = new NODES::INPUT::Integer();
			}
			else if (type == "INPUT DOUBLE") {
				node = new NODES::INPUT::Double();
			}
			else if (type == "INPUT VEC2") {
				node = new NODES::INPUT::Vec2();
			}
			else if (type == "INPUT VEC3") {
				node = new NODES::INPUT::Vec3();
			}
			else if (type == "INPUT VEC4") {
				node = new NODES::INPUT::Vec4();
			}
			else if (type == "MAKE VEC2") {
				node = new NODES::CAST::MAKE::Vec2();
			}
			else if (type == "MAKE VEC3") {
				node = new NODES::CAST::MAKE::Vec3();
			}
			else if (type == "MAKE VEC4") {
				node = new NODES::CAST::MAKE::Vec4();
			}
			else if (type == "MAKE QUAT") {
				node = new NODES::CAST::MAKE::Quat();
			}
			else if (type == "MAKE MAT2") {
				node = new NODES::CAST::MAKE::Mat2();
			}
			else if (type == "MAKE MAT3") {
				node = new NODES::CAST::MAKE::Mat3();
			}
			else if (type == "MAKE MAT4") {
				node = new NODES::CAST::MAKE::Mat4();
			}
			else if (type == "RENDER 2D LINE") {
				node = new NODES::RENDERING::DIM_2D::Line();
			}
			else if (type == "RENDER 2D TRIANGLE") {
				node = new NODES::RENDERING::DIM_2D::Triangle();
			}
			else if (type == "RENDER 2D RECTANGLE") {
				node = new NODES::RENDERING::DIM_2D::Rectangle();
			}
			else if (type == "RENDER 2D CIRCLE") {
				node = new NODES::RENDERING::DIM_2D::Circle();
			}
		}
		if (node) {
			scene->addItem(node);
			node->setPos(drop_pos);
			event->acceptProposedAction();
		}
	}
}
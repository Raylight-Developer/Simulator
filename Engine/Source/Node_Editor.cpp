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

	scene->addItem(FILE.euler_tick.get());
	FILE.euler_tick->setPos(QPointF(0,0));
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
		if (moving) {
			if (!selection.empty()) {
				H_GROUP(selection.size());
			}
			for (Node* node : selection) {
				const QPointF from = node_move_start_pos[node];
				const QPointF delta = from + mapToScene(event->pos()) - l_mouse_down;
				const F64_V2 to = F64_V2(MATH::roundToNearest(delta.x(), 10.0), MATH::roundToNearest(delta.y(), 10.0));
				h_moveNode(node->shared_from_this(), F64_V2(from.x(), from.y()), to);
			}
		}
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
			// TODO escape key cancel
			if (NODE::Port* port = dynamic_cast<NODE::Port*>(item)) {
				if (auto port_r = dynamic_cast<NODE::PORT::Data_I*>(port)) {
					if (port_r->var_type != VARIABLE::Type::BLOCKED) {
						if (!port_r->connection) {
							creating_connection = new NODE::Connection(port_r);
						}
						else {
							auto port_l = static_cast<NODE::PORT::Data_O*>(port_r->connection->port_l);
							delete port_r->connection;
							creating_connection = new NODE::Connection(port_l);
						}
					}
				}
				else if (auto port_l = dynamic_cast<NODE::PORT::Exec_O*>(port)) { // TODO Modify lift connection behavior
					if (!port_l->connection) {
						creating_connection = new NODE::Connection(port_l);
					}
					else {
						auto port_r = static_cast<NODE::PORT::Exec_I*>(port_l->connection->port_r);
						delete port_l->connection;
						creating_connection = new NODE::Connection(port_r);
					}
				}
				else if (auto port_l = dynamic_cast<NODE::PORT::Data_O*>(port)) {
					if (port_l->var_type != VARIABLE::Type::BLOCKED) {
						creating_connection = new NODE::Connection(port);
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
			}
			//else if (QGraphicsProxyWidget* proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget*>(item)) {
			//	QApplication::sendEvent(proxyWidget->widget(), event);
			//}
			else {
				for (auto item : selection) {
					item->setSelected(false);
				}
				selection.clear();
			}
		}
		else {
			for (Node* node : selection) {
				node->setSelected(false);
			}
			selection.clear();

			selecting = true;
			selection_start = mapToScene(event->pos());
			selection_rect->setRect(QRectF(selection_start, QSizeF(0,0)));
			selection_rect->show();
		}
		l_mouse_down = mapToScene(event->pos());
		node_move_start_pos.clear();
		for (Node* node : selection) {
			node_move_start_pos[node] = node->pos();
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
			for (Node* node : selection) {
				const QPointF current_pos = mapToScene(event->pos());
				const QPointF delta = node_move_start_pos[node] + current_pos - l_mouse_down;
				node->setPos(MATH::roundToNearest(delta.x(), 10.0), MATH::roundToNearest(delta.y(), 10.0));
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
			U64 count = 0;
			for (Node* node : selection) {
				if (
					not dynamic_cast<NODES::SINGLETON::Euler_Tick*>(node)
				) {
					h_deleteNode(node->shared_from_this());
					count++;
				}
			}
			if (count != 0) {
				H_GROUP(count);
			}
			selection.clear();
			break;
		}
	}
	for (QWidget* widget : QApplication::topLevelWidgets()) {
		if (widget->inherits("QLineEdit") && widget->hasFocus()) {
			QApplication::sendEvent(widget, event);
		}
	}
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
	const QPointF drop_pos = d_to_p(MATH::roundToNearest(p_to_d(mapToScene(event->position().toPoint())), 10.0));
	if (event->mimeData()->hasText()) {
		Ptr_S<Node> node;

		if (event->mimeData()->text() == "NODE") {
			QByteArray itemDataType = event->mimeData()->data("Type");
			QDataStream dataStreamType(&itemDataType, QIODevice::ReadOnly);
			QString type;
			dataStreamType >> type;

			if (type == "CONSTANT") {
				node = make_shared<NODES::VARIABLES::Constant>();
			}
			else if (type == "VARIABLE SET") {
				node = make_shared<NODES::VARIABLES::Set>();
			}
			else if (type == "VARIABLE GET") {
				node = make_shared<NODES::VARIABLES::Get>();
			}
			else if (type == "MAKE VEC2") {
				node = make_shared<NODES::CAST::MAKE::Vec2>();
			}
			else if (type == "MAKE VEC3") {
				node = make_shared<NODES::CAST::MAKE::Vec3>();
			}
			else if (type == "MAKE VEC4") {
				node = make_shared<NODES::CAST::MAKE::Vec4>();
			}
			else if (type == "MAKE QUAT") {
				node = make_shared<NODES::CAST::MAKE::Quat>();
			}
			else if (type == "MAKE MAT2") {
				node = make_shared<NODES::CAST::MAKE::Mat2>();
			}
			else if (type == "MAKE MAT3") {
				node = make_shared<NODES::CAST::MAKE::Mat3>();
			}
			else if (type == "MAKE MAT4") {
				node = make_shared<NODES::CAST::MAKE::Mat4>();
			}
			else if (type == "ARITHMETIC") {
				node = make_shared<NODES::Arithmetic>();
			}
			else if (type == "TRIGONOMETRY") {
				node = make_shared<NODES::Trigonometry>();
			}
			else if (type == "BOOLEAN COMPARISON") {
				node = make_shared<NODES::BOOLEAN::Compare>();
			}
			else if (type == "BOOLEAN IF") {
				node = make_shared<NODES::BOOLEAN::If>();
			}
			else if (type == "BOOLEAN IF ELSE") {
				node = make_shared<NODES::BOOLEAN::If_Else>();
			}
			else if (type == "BOOLEAN SELECT") {
				node = make_shared<NODES::BOOLEAN::Select>();
			}
			else if (type == "RENDER 2D LINE") {
				node = make_shared<NODES::RENDERING::DIM_2D::Line>();
			}
			else if (type == "RENDER 2D TRIANGLE") {
				node = make_shared<NODES::RENDERING::DIM_2D::Triangle>();
			}
			else if (type == "RENDER 2D RECTANGLE") {
				node = make_shared<NODES::RENDERING::DIM_2D::Rectangle>();
			}
			else if (type == "RENDER 2D CIRCLE") {
				node = make_shared<NODES::RENDERING::DIM_2D::Circle>();
			}
			else if (type.startsWith("SINGLETON")) {
				#define NODE_EXISTS(type) false;\
				for (Ptr_S<Node> node : FILE.nodes) {\
					if (dynamic_pointer_cast<type>(node)) {\
						exists = true;\
						break;\
					}\
				}
				if (type == "SINGLETON BACKGROUND") {
					bool exists = NODE_EXISTS(NODES::SINGLETON::Background)
					if (!exists) {
						node = make_shared<NODES::SINGLETON::Background>();
					}
				}
				else if (type == "SINGLETON 2D CAMERA") {
					bool exists = NODE_EXISTS(NODES::SINGLETON::Camera_2D)
					if (!exists) {
						node = make_shared<NODES::SINGLETON::Camera_2D>();
					}
				}
				else if (type == "SINGLETON 3D CAMERA") {
					bool exists = NODE_EXISTS(NODES::SINGLETON::Camera_3D)
					if (!exists) {
						node = make_shared<NODES::SINGLETON::Camera_3D>();
					}
				}
			}
			else if (type.startsWith("VARIABLE")) {
				const QString name = type.remove(0, 9);
				if (auto existing = dynamic_cast<NODES::VARIABLES::Get*>(scene->itemAt(mapToScene(event->position().toPoint()), transform()))) {
					SESSION->variable_refs[existing->var].remove(existing->shared_from_this());
					SESSION->variable_refs[name].push(existing->shared_from_this());
					existing->setVar(name);
				}
				else if (auto existing = dynamic_cast<NODES::VARIABLES::Set*>(scene->itemAt(mapToScene(event->position().toPoint()), transform()))) {
					SESSION->variable_refs[existing->var].remove(existing->shared_from_this());
					SESSION->variable_refs[name].push(existing->shared_from_this());
					existing->setVar(name);
				}
				else {
					auto def_node = make_shared<NODES::VARIABLES::Get>();
					SESSION->variable_refs[name].push(def_node);
					def_node->setVar(name);
					node = def_node;
				}
			}
			else if (type == "SCRIPT") {
				QByteArray itemDataPath = event->mimeData()->data("Path");
				QDataStream dataStreamPath(&itemDataPath, QIODevice::ReadOnly);
				QString script_path;
				dataStreamPath >> script_path;
				node = Ptr_S<NODES::SCRIPT::Script>(NODES::SCRIPT::loadScript(script_path));
			}
		}
		if (node) {
			h_addNode(node, F64_V2(drop_pos.x(), drop_pos.y()));
			H_GROUP(1);
		}
	}
}

void Node_Editor::h_addNode(Ptr_S<Node> node, const F64_V2& pos) {
	H_PUSH(make_shared<Add_Node>(node, this, pos));
}

void Node_Editor::h_moveNode(Ptr_S<Node> node, const F64_V2& from, const F64_V2& to) {
	H_PUSH(make_shared<Move_Node>(node, this, from, to));
}

void Node_Editor::h_deleteNode(Ptr_S<Node> node) {
	H_PUSH(make_shared<Delete_Node>(node, this));
}

Node_Editor::Add_Node::Add_Node(Ptr_S<Node> node, Node_Editor* editor, const F64_V2& pos) :
	CORE::CMD("Add Node"),
	editor(editor),
	node(node),
	pos(pos)
{}

void Node_Editor::Add_Node::execute() const {
	FILE.nodes.push(node);
	editor->scene->addItem(node.get());
	node->setPos(pos.x, pos.y);
}

void Node_Editor::Add_Node::undo() {
	if (auto node_def = dynamic_pointer_cast<NODES::VARIABLES::Get>(node)) {
		SESSION->variable_refs[node_def->var].remove(node_def->shared_from_this());
	}
	else if (auto node_def = dynamic_pointer_cast<NODES::VARIABLES::Set>(node)) {
		SESSION->variable_refs[node_def->var].remove(node_def->shared_from_this());
	}
	FILE.nodes.remove(node->shared_from_this());
	editor->scene->removeItem(node.get());
}

Node_Editor::Move_Node::Move_Node(Ptr_S<Node> node, Node_Editor* editor, const F64_V2& from, const F64_V2& to) :
	CORE::CMD("Move Node"),
	editor(editor),
	node(node),
	from(from),
	to(to)
{}

void Node_Editor::Move_Node::execute() const {
	node->setPos(to.x, to.y);
}

void Node_Editor::Move_Node::undo() {
	node->setPos(from.x, from.y);
}

Node_Editor::Delete_Node::Delete_Node(Ptr_S<Node> node, Node_Editor* editor) :
	CORE::CMD("Delete Node"),
	editor(editor),
	node(node)
{
	pos = F64_V2(node->pos().x(), node->pos().y());
}

void Node_Editor::Delete_Node::execute() const {
	if (auto node_def = dynamic_pointer_cast<NODES::VARIABLES::Get>(node)) {
		SESSION->variable_refs[node_def->var].remove(node_def->shared_from_this());
	}
	else if (auto node_def = dynamic_pointer_cast<NODES::VARIABLES::Set>(node)) {
		SESSION->variable_refs[node_def->var].remove(node_def->shared_from_this());
	}
	FILE.nodes.remove(node->shared_from_this());
	editor->scene->removeItem(node.get());
}

void Node_Editor::Delete_Node::undo() {
	FILE.nodes.push(node);
	editor->scene->addItem(node.get());
	node->setPos(pos.x, pos.y);
}
#include "Node_Editor.hpp"

#include "Session.hpp"

Node_Editor::Node_Editor(QWidget* parent) :
	GUI::Graphics_View(parent),
	moving(false),
	selecting(false)
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
	editor_ptr = this;
}

Node_Editor::~Node_Editor() {
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
			U32 count = 0;
			for (Node* node : selection) {
				const QPointF from  = node_move_start_pos[node];
				const QPointF to    = from + mapToScene(event->pos()) - l_mouse_down;
				const F64_V2 r_to   = F64_V2(MATH::roundToNearest(to.x()  , 10.0), MATH::roundToNearest(to.y()  , 10.0));
				const F64_V2 r_from = F64_V2(MATH::roundToNearest(from.x(), 10.0), MATH::roundToNearest(from.y(), 10.0));
				if (r_to != r_from) {
					h_moveNode(node->shared_from_this(), r_from, r_to);
					count++;
				}
			}
			if (count > 0) {
				H_GROUP(count);
			}
		}
		moving = false;
		setCursor(Qt::ArrowCursor);
		if (selecting) {
			for (auto item : scene->items(selection_rect->rect())) {
				if (item->type() == Graphics_Item_Type::E_NODE) {
					Node* node = static_cast<Node*>(item);
					if (!node->isSelected()) {
						node->setSelected(true);
						selection.push(node);
					}
				}
			}
			selecting = false;
			selection_rect->hide();
		}
		if (creating_connection) {
			if (auto item = scene->itemAt(mapToScene(event->pos()), transform())) {
				const int type = item->type();
				if (type == Graphics_Item_Type::E_DATA_I) {
					auto drop_port = static_cast<NODE::PORT::Data_I*>(item);
					if (creating_connection->port_l->type() == Graphics_Item_Type::E_DATA_O) {
						auto source_port = static_cast<NODE::PORT::Data_O*>(creating_connection->port_l);
						if (source_port->node != drop_port->node) {
							if (source_port->var_type == drop_port->variable->type and source_port->var_container == drop_port->variable->container) {
								if (drop_port->connected()) {
									h_disconnectPort(drop_port);
									h_connectPorts(source_port, drop_port);
									H_GROUP(2);
								}
								else {
									h_connectPorts(source_port, drop_port);
									H_GROUP(1);
								}
							}
						}
					}
				}
				else if (type == Graphics_Item_Type::E_DATA_O) {
					auto drop_port = static_cast<NODE::PORT::Data_O*>(item);
					if (creating_connection->port_l->type() == Graphics_Item_Type::E_DATA_I) {
						auto source_port = static_cast<NODE::PORT::Data_I*>(creating_connection->port_l);
						if (source_port->node != drop_port->node) {
							if (drop_port->var_type == source_port->variable->type and drop_port->var_container == source_port->variable->container) {
								if (source_port->connected()) {
									h_disconnectPort(source_port);
									h_connectPorts(drop_port, source_port);
									H_GROUP(2);
								}
								else {
									h_connectPorts(drop_port, source_port);
									H_GROUP(1);
								}
							}
						}
					}
				}
				else if (type == Graphics_Item_Type::E_EXEC_O) {
					auto drop_port = static_cast<NODE::PORT::Exec_O*>(item);
					if (creating_connection->port_l->type() == Graphics_Item_Type::E_EXEC_I) {
						auto source_port = static_cast<NODE::PORT::Exec_I*>(creating_connection->port_l);
						if (source_port->node != drop_port->node) {
							if (drop_port->connected()) {
								h_disconnectPort(drop_port);
								h_connectPorts(drop_port, source_port);
								H_GROUP(2);
							}
							else {
								h_connectPorts(drop_port, source_port);
								H_GROUP(1);
							}
						}
					}
				}
				else if (type == Graphics_Item_Type::E_EXEC_I) {
					auto drop_port = static_cast<NODE::PORT::Exec_I*>(item);
					if (creating_connection->port_l->type() == Graphics_Item_Type::E_EXEC_O) {
						auto source_port = static_cast<NODE::PORT::Exec_O*>(creating_connection->port_l);
						if (source_port->node != drop_port->node) {
							if (source_port->connected()) {
								h_disconnectPort(source_port);
								h_connectPorts(source_port, drop_port);
								H_GROUP(2);
							}
							else {
								h_connectPorts(source_port, drop_port);
								H_GROUP(1);
							}
						}
					}
				}
				else {
					// TODO create context menu for available nodes
				}
			}
			creating_connection.reset();
		}
	}
	GUI::Graphics_View::mouseReleaseEvent(event);
	viewport()->update();
}

void Node_Editor::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::MouseButton::LeftButton) {
		if (auto item = scene->itemAt(mapToScene(event->pos()), transform())) {
			const int type = item->type();
			// TODO escape key cancel creating conn or lifting conn
			// TODO better shift/multi behavior and grow current selection further
			if (IS_PORT(type)) {
				if (type == Graphics_Item_Type::E_DATA_I) {
					auto port_r = static_cast<NODE::PORT::Data_I*>(item);
					if (port_r->variable->type != VAR_TYPE::NONE) {
						if (!port_r->connected()) {
							creating_connection = make_unique<NODE::Connection>(port_r);
						}
						else {
							h_disconnectPort(port_r);
							H_GROUP(1);
							creating_connection = make_unique<NODE::Connection>(port_r);
						}
					}
				}
				else if (type == Graphics_Item_Type::E_EXEC_O) {
					auto port_l = static_cast<NODE::PORT::Exec_O*>(item);
					if (!port_l->connected()) {
						creating_connection = make_unique<NODE::Connection>(port_l);
					}
					else {
						h_disconnectPort(port_l);
						H_GROUP(1);
						creating_connection = make_unique<NODE::Connection>(port_l);
					}
				}
				else if (type == Graphics_Item_Type::E_DATA_O) {
					auto port_l = static_cast<NODE::PORT::Data_O*>(item);
					if (port_l->var_type != VAR_TYPE::NONE) {
						creating_connection = make_unique<NODE::Connection>(port_l);
					}
				}
				else {
					auto port = static_cast<NODE::Port*>(item);
					creating_connection = make_unique<NODE::Connection>(port);
				}
			}
			if (type == Graphics_Item_Type::E_NODE) {
				Node* node = static_cast<Node*>(item);
				moving = true;
				setCursor(Qt::ClosedHandCursor);
				if (event->modifiers() & Qt::KeyboardModifier::ShiftModifier) {
					if (!node->isSelected()) {
						node->setSelected(true);
						selection.push(node);
					}
					else {
						node->setSelected(false);
						selection.remove(node);
					}
				}
				else {
					if (!node->isSelected()) {
						for (auto item : selection) {
							item->setSelected(false);
						}
						selection.clear();

						selection.push(node);
						node->setSelected(true);
					}
				}
				node->update();

				l_mouse_down = mapToScene(event->pos());
				node_move_start_pos.clear();
				for (Node* node : selection) {
					node_move_start_pos[node] = node->pos();
				}
			}
		}
		else {
			for (Node* node : selection) {
				node->setSelected(false);
				node->update();
			}
			selection.clear();

			selecting = true;
			selection_start = mapToScene(event->pos());
			selection_rect->setRect(QRectF(selection_start, QSizeF(0,0)));
			selection_rect->show();
		}
	}
	GUI::Graphics_View::mousePressEvent(event);
	viewport()->update();
}

void Node_Editor::mouseMoveEvent(QMouseEvent* event) {
	if (event->modifiers() & Qt::KeyboardModifier::AltModifier) {
		if (auto item = scene->itemAt(mapToScene(event->pos()), transform())) {
			if (IS_PORT(item->type())) {
				NODE::Port* port = static_cast<NODE::Port*>(item);
				if (port->connected()) {
					h_disconnectPort(port);
					H_GROUP(1);
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
					node->node_type != NODES::Node_Type::SINGLETON_EULER_TICK
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
	viewport()->update();
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
	viewport()->update();
}

void Node_Editor::dragMoveEvent(QDragMoveEvent* event) {
	event->acceptProposedAction();
}

void Node_Editor::dropEvent(QDropEvent* event) {
	const QPointF drop_pos = d_to_p(MATH::roundToNearest(p_to_d(mapToScene(event->position().toPoint())), 10.0));
	auto under_mouse = scene->itemAt(mapToScene(event->position().toPoint()), transform());
	if (event->mimeData()->hasText()) {
		Ptr_S<Node> node;

		if (event->mimeData()->text() == "NODE") {
			QByteArray itemDataType = event->mimeData()->data("Type");
			QDataStream dataStreamType(&itemDataType, QIODevice::ReadOnly);
			QString type;
			dataStreamType >> type;

			if (type == "VARIABLE CONSTANT") {
				node = make_shared<NODES::VARIABLE::Constant>();
			}
			else if (type == "VARIABLE SET") {
				node = make_shared<NODES::VARIABLE::Set>();
			}
			else if (type == "VARIABLE GET") {
				node = make_shared<NODES::VARIABLE::Get>();
			}
			else if (type == "CAST CONVERT I64 TO F64") {
				node = make_shared<NODES::CAST::CONVERT::I64_To_F64>();
			}
			else if (type == "CAST BREAK VEC2") {
				node = make_shared<NODES::CAST::BREAK::Vec2>();
			}
			else if (type == "CAST MAKE COLOR") {
				node = make_shared<NODES::CAST::MAKE::Color>();
			}
			else if (type == "CAST MAKE VEC2") {
				node = make_shared<NODES::CAST::MAKE::Vec2>();
			}
			else if (type == "CAST MAKE VEC3") {
				node = make_shared<NODES::CAST::MAKE::Vec3>();
			}
			else if (type == "CAST MAKE VEC4") {
				node = make_shared<NODES::CAST::MAKE::Vec4>();
			}
			else if (type == "CAST MAKE QUAT") {
				node = make_shared<NODES::CAST::MAKE::Quat>();
			}
			else if (type == "CAST MAKE MAT2") {
				node = make_shared<NODES::CAST::MAKE::Mat2>();
			}
			else if (type == "CAST MAKE MAT3") {
				node = make_shared<NODES::CAST::MAKE::Mat3>();
			}
			else if (type == "CAST MAKE MAT4") {
				node = make_shared<NODES::CAST::MAKE::Mat4>();
			}
			else if (type == "MATH ARITHMETIC") {
				node = make_shared<NODES::MATH::Arithmetic>();
			}
			else if (type == "MATH TRIGONOMETRY") {
				node = make_shared<NODES::MATH::Trigonometry>();
			}
			else if (type == "BOOLEAN COMPARISON") {
				node = make_shared<NODES::BOOLEAN::Compare>();
			}
			else if (type == "BOOLEAN SELECT") {
				node = make_shared<NODES::BOOLEAN::Select>();
			}
			else if (type == "CONTAINER LIST ACCESS") {
				node = make_shared<NODES::CONTAINER::LIST::Access>();
			}
			else if (type == "CONTAINER LIST CREATE") {
				node = make_shared<NODES::CONTAINER::LIST::Create>();
			}
			else if (type == "CONTAINER LIST INSERT") {
				node = make_shared<NODES::CONTAINER::LIST::Insert>();
			}
			else if (type == "CONTAINER LIST MODIFY") {
				node = make_shared<NODES::CONTAINER::LIST::Modify>();
			}
			else if (type == "CONTAINER LIST REMOVE") {
				node = make_shared<NODES::CONTAINER::LIST::Remove>();
			}
			else if (type == "CONTAINER LIST CLEAR") {
				node = make_shared<NODES::CONTAINER::LIST::Clear>();
			}
			else if (type == "CONTAINER LIST PUSH") {
				node = make_shared<NODES::CONTAINER::LIST::Push>();
			}
			else if (type == "CONTAINER LIST SIZE") {
				node = make_shared<NODES::CONTAINER::LIST::Size>();
			}
			else if (type == "EXEC LOOP SUBSAMPLE") {
				node = make_shared<NODES::EXEC::LOOP::Subsample>();
			}
			else if (type == "EXEC LOOP WHILE") {
				node = make_shared<NODES::EXEC::LOOP::While>();
			}
			else if (type == "EXEC LOOP FOR") {
				node = make_shared<NODES::EXEC::LOOP::For>();
			}
			else if (type == "EXEC IF") {
				node = make_shared<NODES::EXEC::If>();
			}
			else if (type == "EXEC IF ELSE") {
				node = make_shared<NODES::EXEC::If_Else>();
			}
			else if (type == "HOOK INPUT KEY") {
				node = make_shared<NODES::HOOK::INPUT::Key>();
			}
			else if (type == "HOOK INPUT MOUSE") {
				node = make_shared<NODES::HOOK::INPUT::Mouse>();
			}
			else if (type == "HOOK INPUT MOUSE POS") {
				node = make_shared<NODES::HOOK::INPUT::Mouse_Pos>();
			}
			else if (type == "HOOK INPUT MOUSE WHEEL") {
				node = make_shared<NODES::HOOK::INPUT::Mouse_Wheel>();
			}
			else if (type == "HOOK DISPLAY") {
				node = make_shared<NODES::HOOK::Display>();
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
				for (Ptr_S<Node> node : FILE.node_singletons) {\
					if (node->node_type == type) {\
						exists = true;\
						break;\
					}\
				}
				if (type == "SINGLETON BACKGROUND") {
					bool exists = NODE_EXISTS(NODES::Node_Type::SINGLETON_BACKGROUND)
					if (!exists) {
						node = make_shared<NODES::SINGLETON::Background>();
						FILE.node_singletons.push(node);
					}
				}
				else if (type == "SINGLETON 2D CAMERA") {
					bool exists = NODE_EXISTS(NODES::Node_Type::SINGLETON_2D_CAMERA)
					if (!exists) {
						node = make_shared<NODES::SINGLETON::Camera_2D>();
						FILE.node_singletons.push(node);
					}
				}
				else if (type == "SINGLETON 3D CAMERA") {
					bool exists = NODE_EXISTS(NODES::Node_Type::SINGLETON_3D_CAMERA)
					if (!exists) {
						node = make_shared<NODES::SINGLETON::Camera_3D>();
						FILE.node_singletons.push(node);
					}
				}
				else if (type == "SINGLETON EULER TICK") {
					bool exists = NODE_EXISTS(NODES::Node_Type::SINGLETON_EULER_TICK)
					if (!exists) {
						node = make_shared<NODES::SINGLETON::Euler_Tick>();
						FILE.node_singletons.push(node);
						FILE.euler_tick = static_pointer_cast<NODES::SINGLETON::Euler_Tick>(node);
					}
				}
				else if (type == "SINGLETON INIT") {
					bool exists = NODE_EXISTS(NODES::Node_Type::SINGLETON_INIT)
					if (!exists) {
						node = make_shared<NODES::SINGLETON::Init>();
						FILE.node_singletons.push(node);
						FILE.init = static_pointer_cast<NODES::SINGLETON::Init>(node);
					}
				}
			}
			else if (type.startsWith("VARIABLE")) {
				const QString name = type.remove(0, 9);
				if (under_mouse and under_mouse->type() == Graphics_Item_Type::E_NODE and static_cast<Node*>(under_mouse)->node_type == NODES::Node_Type::VARIABLE_GET) {
					auto existing = static_cast<NODES::VARIABLE::Get*>(under_mouse);
					FILE.variable_refs[existing->var].remove(existing->shared_from_this());
					FILE.variable_refs[name].push(existing->shared_from_this());
					existing->h_setVar(name);
				}
				else if (under_mouse and under_mouse->type() == Graphics_Item_Type::E_NODE and static_cast<Node*>(under_mouse)->node_type == NODES::Node_Type::VARIABLE_SET) {
					auto existing = static_cast<NODES::VARIABLE::Set*>(under_mouse);
					FILE.variable_refs[existing->var].remove(existing->shared_from_this());
					FILE.variable_refs[name].push(existing->shared_from_this());
					existing->h_setVar(name);
					H_GROUP(1);
				}
				else {
					auto def_node = make_shared<NODES::VARIABLE::Set>();
					FILE.variable_refs[name].push(def_node);
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
	viewport()->update();
}

void Node_Editor::addNode(Ptr_S<Node> node, const F64_V2& pos) {
	FILE.nodes.push(node);
	editor_ptr->scene->addItem(node.get());
	node->setPos(pos.x, pos.y);
}

void Node_Editor::moveNode(Ptr_S<Node> node, const F64_V2& new_pos) {
	node->setPos(new_pos.x, new_pos.y);
}

void Node_Editor::deleteNode(Ptr_S<Node> node) {
	switch (node->node_type) {
		case NODES::Node_Type::VARIABLE_GET: {
			auto node_def = static_pointer_cast<NODES::VARIABLE::Get>(node);
			FILE.variable_refs[node_def->var].remove(node_def->shared_from_this());
			break;
		}
		case NODES::Node_Type::VARIABLE_SET: {
			auto node_def = static_pointer_cast<NODES::VARIABLE::Set>(node);
			FILE.variable_refs[node_def->var].remove(node_def->shared_from_this());
			break;
		}
	}
	FILE.nodes.remove(node->shared_from_this());
	editor_ptr->scene->removeItem(node.get());
}

void Node_Editor::connectPorts(Port* port_l, Port* port_r) {
	if (port_r->type() == Graphics_Item_Type::E_DATA_I) {
		auto d_port_r = static_cast<PORT::Data_I*>(port_r);
		auto d_port_l = static_cast<PORT::Data_O*>(port_l);
		d_port_r->connect(d_port_l);
	}
	else {
		auto d_port_l = static_cast<PORT::Exec_O*>(port_l);
		auto d_port_r = static_cast<PORT::Exec_I*>(port_r);
		d_port_l->connect(d_port_r);
	}
}

void Node_Editor::disconnectPort(Port* port) {
	const int type = port->type();
	switch (type) {
		case Graphics_Item_Type::E_DATA_I: {
			auto port_r = static_cast<NODE::PORT::Data_I*>(port);
			port_r->disconnect();
			break;
		}
		case Graphics_Item_Type::E_DATA_O: {
			auto port_l = static_cast<NODE::PORT::Data_O*>(port);
			port_l->disconnect();
			break;
		}
		case Graphics_Item_Type::E_EXEC_O: {
			auto port_l = static_cast<NODE::PORT::Exec_O*>(port);
			port_l->disconnect();
			break;
		}
		case Graphics_Item_Type::E_EXEC_I: {
			auto port_r = static_cast<NODE::PORT::Exec_I*>(port);
			port_r->disconnect();
			break;
		}
	}
}

void Node_Editor::h_addNode(Ptr_S<Node> node, const F64_V2& pos) {
	H_PUSH(make_shared<Add_Node>(node, pos));
}

void Node_Editor::h_moveNode(Ptr_S<Node> node, const F64_V2& from, const F64_V2& to) {
	H_PUSH(make_shared<Move_Node>(node, from, to));
}

void Node_Editor::h_deleteNode(Ptr_S<Node> node) {
	H_PUSH(make_shared<Delete_Node>(node));
}

void Node_Editor::h_connectPorts(Port* port_l, Port* port_r) {
	H_PUSH(make_shared<Connect>(port_l, port_r));
}

void Node_Editor::h_disconnectPort(Port* port) {
	H_PUSH(make_shared<Disconnect>(port));
}

Node_Editor::Add_Node::Add_Node(Ptr_S<Node> node, const F64_V2& pos) :
	CORE::CMD("Add Node"),
	node(node),
	pos(pos)
{}

void Node_Editor::Add_Node::execute() const {
	editor_ptr->addNode(node, pos);
}

void Node_Editor::Add_Node::undo() {
	editor_ptr->deleteNode(node);
}

Node_Editor::Move_Node::Move_Node(Ptr_S<Node> node, const F64_V2& from, const F64_V2& to) :
	CORE::CMD("Move Node"),
	node(node),
	from(from),
	to(to)
{}

void Node_Editor::Move_Node::execute() const {
	editor_ptr->moveNode(node, to);
}

void Node_Editor::Move_Node::undo() {
	editor_ptr->moveNode(node, from);
}

Node_Editor::Delete_Node::Delete_Node(Ptr_S<Node> node) :
	CORE::CMD("Delete Node"),
	node(node)
{
	pos = F64_V2(node->pos().x(), node->pos().y());

	// TODO may cause issues if history is forked
	for (Port* port : node->inputs) {
		if (port->connected()) {
			if (port->type() == Graphics_Item_Type::E_DATA_I) {
				auto d_port = static_cast<PORT::Data_I*>(port);
				connections[d_port].push(d_port->connection->getDataO());
			}
			else {
				auto d_port = static_cast<PORT::Exec_I*>(port);
				for (Connection* conn : d_port->connections) {
					connections[d_port].push(conn->getExecO());
				}
			}
		}
	}
	for (Port* port : node->outputs) {
		if (port->connected()) {
			if (port->type() == Graphics_Item_Type::E_EXEC_O) {
				auto d_port = static_cast<PORT::Exec_O*>(port);
				connections[d_port].push(d_port->connection->getExecI());
			}
			else {
				auto d_port = static_cast<PORT::Data_O*>(port);
				for (Connection* conn : d_port->connections) {
					connections[d_port].push(conn->getDataI());
				}
			}
		}
	}
}

void Node_Editor::Delete_Node::execute() const {
	editor_ptr->deleteNode(node);

	for (Port* port : node->inputs) {
		if (port->connected()) {
			port->disconnect();
		}
	}
	for (Port* port : node->outputs) {
		if (port->connected()) {
			port->disconnect();
		}
	}
	if (node->node_type == NODES::Node_Type::SCRIPT) {
		static_pointer_cast<NODES::SCRIPT::Script>(node)->onUnload();
	}
}

void Node_Editor::Delete_Node::undo() {
	editor_ptr->addNode(node, pos);

	for (auto& [port, ports] : connections) {
		const int type = port->type();
		switch (type) {
			case Graphics_Item_Type::E_DATA_I:
			case Graphics_Item_Type::E_EXEC_I: {
				for (Port* other : ports) {
					editor_ptr->connectPorts(other, port);
				}
				break;
			}
			case Graphics_Item_Type::E_DATA_O:
			case Graphics_Item_Type::E_EXEC_O: {
				for (Port* other : ports) {
					editor_ptr->connectPorts(port, other);
				}
				break;
			}
		}
	}
	if (node->node_type == NODES::Node_Type::SCRIPT) {
		static_pointer_cast<NODES::SCRIPT::Script>(node)->onLoad();
	}
}

Node_Editor::Connect::Connect(Port* port_l, Port* port_r) :
	CORE::CMD("Connect Nodes"),
	port_l(port_l),
	port_r(port_r)
{}

void Node_Editor::Connect::execute() const {
	editor_ptr->connectPorts(port_l, port_r);
}

void Node_Editor::Connect::undo() {
	if (port_r->connected() and port_r->type() == Graphics_Item_Type::E_DATA_I) {
		auto d_port_r = static_cast<NODE::PORT::Data_I*>(port_r);
		d_port_r->disconnect();
	}
	else if (port_l->connected()) {
		auto d_port_l = static_cast<NODE::PORT::Exec_O*>(port_l);
		d_port_l->disconnect();
	}
}

Node_Editor::Disconnect::Disconnect(Port* port) :
	CORE::CMD("Disconnect Nodes"),
	port(port)
{
	const int type = port->type();
	switch (type) {
		case Graphics_Item_Type::E_DATA_I: {
		auto port_r = static_cast<NODE::PORT::Data_I*>(port);
		connections.push(port_r->connection->port_l);
			break;
		}
		case Graphics_Item_Type::E_DATA_O: {
			auto port_l = static_cast<NODE::PORT::Data_O*>(port);
			for (auto conn : port_l->connections) {
				connections.push(conn->port_r);
			}
			break;
		}
		case Graphics_Item_Type::E_EXEC_O: {
			auto port_l = static_cast<NODE::PORT::Exec_O*>(port);
			connections.push(port_l->connection->port_r);
			break;
		}
		case Graphics_Item_Type::E_EXEC_I: {
			auto port_r = static_cast<NODE::PORT::Exec_I*>(port);
			for (auto conn : port_r->connections) {
				connections.push(conn->port_l);
			}
			break;
		}
	}
}

void Node_Editor::Disconnect::execute() const {
	editor_ptr->disconnectPort(port);
}

void Node_Editor::Disconnect::undo() {
	const int type = port->type();
	switch (type) {
		case Graphics_Item_Type::E_DATA_I: {
			auto port_r = static_cast<NODE::PORT::Data_I*>(port);
			editor_ptr->connectPorts(connections.ptr(0), port_r);
			break;
		}
		case Graphics_Item_Type::E_DATA_O: {
			auto port_l = static_cast<NODE::PORT::Data_O*>(port);
			for (auto conn : connections) {
				editor_ptr->connectPorts(port_l, conn);
			}
			break;
		}
		case Graphics_Item_Type::E_EXEC_O: {
			auto port_l = static_cast<NODE::PORT::Exec_O*>(port);
			editor_ptr->connectPorts(port_l, connections.ptr(0));
			break;
		}
		case Graphics_Item_Type::E_EXEC_I: {
			auto port_r = static_cast<NODE::PORT::Exec_I*>(port);
			for (auto conn : connections) {
				editor_ptr->connectPorts(conn, port_r);
			}
			break;
		}
	}
}
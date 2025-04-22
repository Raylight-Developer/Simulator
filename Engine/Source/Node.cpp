#include "Node.hpp"

Node::Node() :
	QGraphicsItem(),
	node_type("ERROR"),
	label("NODE"),
	rect(QRectF(0, 0, 200, 200))
{
	setZValue(1);
	setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
	header_color = QColor(25, 25, 25);
}

Node::Node(const QString& node_type, const QString& label) :
	QGraphicsItem(),
	node_type(node_type),
	label(label),
	rect(QRectF(0, 0, 200, 200))
{
	setZValue(1);
	setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
	header_color = QColor(25, 25, 25);
}

Node::~Node() {
	inputs.clear();
	outputs.clear();
}

void Node::save(CORE::Lace& lace, const U64& index) const {
	lace NL << "┌Node [ " << index << " ] " << label;
	lace++;
	lace NL PTR(shared_from_this().get());
	lace NL << "Type " << node_type;
	lace NL << "( " << pos() << " )";
	lace--;
	lace NL << "└Node";
}

int Node::type() const {
	return Graphics_Item_Type::E_NODE;
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}

	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);

	painter->setBrush(header_color);
	painter->drawRoundedRect(QRectF(rect.topLeft(), QSize(rect.width(), 20)), 5, 5);

	painter->setPen(Qt::white);
	painter->drawText(QRectF(rect.topLeft(), QSize(rect.width(), 20)), Qt::AlignCenter, label);
}

QRectF Node::boundingRect() const {
	return rect;
}

NODE::Port::Port(Node* node) :
	QGraphicsItem(node),
	node(node),
	onConnRequested(nullptr),
	onDisconnection(nullptr),
	rect(QRectF(0, 0, 10, 10))
{
	setZValue(10);
}

bool NODE::Port::requestConnection(Connection* connection) {
	if (onConnRequested) {
		return onConnRequested(this, connection);
	}
	return true;
}

void NODE::Port::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(Qt::black);
	painter->setPen(Qt::white);

	painter->drawEllipse(rect);
}

QRectF NODE::Port::boundingRect() const {
	return rect.marginsAdded(QMarginsF(5, 5, 5, 5));
}

NODE::Connection::Connection(Port* source_port) :
	QGraphicsItem(source_port),
	port_l(source_port),
	port_r(nullptr)
{
	setZValue(-5);
	color = QColor(255, 255, 255);

	pos_l = mapFromItem(port_l, port_l->boundingRect().center());
	pos_r = pos_l;

	if (auto t_port_l = dynamic_cast<PORT::Data_O*>(port_l)) {
		color = VARIABLE::toColor(t_port_l->var_type);
	}
	else if (auto t_port_l = dynamic_cast<PORT::Data_I*>(port_l)) {
		color = VARIABLE::toColor(t_port_l->var_type);
	}
}

NODE::Connection::Connection(Port* port_l, Port* port_r) :
	QGraphicsItem(port_l),
	port_l(port_l),
	port_r(port_r)
{
	setZValue(5);
	color = QColor(255, 255, 255);

	pos_l = mapFromItem(port_l, port_l->boundingRect().center());
	pos_r = mapFromItem(port_r, port_r->boundingRect().center());

	if (auto t_port_l = dynamic_cast<PORT::Data_O*>(port_l)) {
		color = VARIABLE::toColor(t_port_l->var_type);
	}
}

int NODE::Connection::type() const {
	return Graphics_Item_Type::E_CONN;
}

void NODE::Connection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setPen(QPen(color, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	if (port_l and port_r) {
		//if (reroutes.empty());
		pos_l = mapFromItem(port_l, port_l->boundingRect().center());
		pos_r = mapFromItem(port_r, port_r->boundingRect().center());

		QPainterPath path;
		if (pos_l.x() < pos_r.x() + 5) {
			path.moveTo(pos_l + QPointF(color == QColor(255,255,255) ? 7.5 : 2, 0));
			path.lineTo(pos_l + QPointF((pos_r.x() - pos_l.x()) / 2.0, 0));
			path.lineTo(pos_r + QPointF((pos_l.x() - pos_r.x()) / 2.0, 0));
			path.lineTo(pos_r - QPointF(color == QColor(255,255,255) ? 2.5 : 2, 0));
		}
		else {
			path.moveTo(pos_l + QPointF(color == QColor(255,255,255) ? 7.5 : 2, 0));
			path.lineTo(pos_l + QPointF(10, 0));
			path.lineTo(QPointF(pos_l.x(), pos_r.y()) + QPointF(10, -100));
			path.lineTo(pos_r + QPointF(-10, -100));
			path.lineTo(pos_r + QPointF(-10, 0));
			path.lineTo(pos_r - QPointF(color == QColor(255,255,255) ? 2.5 : 2, 0));
		}

		painter->drawPath(path);
	}
	else {
		QPainterPath path;
		path.moveTo(pos_l);
		path.lineTo(pos_r);

		painter->drawPath(path);
	}
}

QRectF NODE::Connection::boundingRect() const {
	const QPointF point_a = pos_l;
	const QPointF point_b = pos_r;

	const qreal left   = qMin(point_a.x(), point_b.x());
	const qreal top    = qMin(point_a.y(), point_b.y());
	const qreal right  = qMax(point_a.x(), point_b.x());
	const qreal bottom = qMax(point_a.y(), point_b.y());

	return QRectF(left, top, right - left, bottom - top);
}

void NODE::Connection::updateL(const QPointF& point) {
	pos_l = mapToParent(point) - port_l->scenePos();
}

void NODE::Connection::updateR(const QPointF& point) {
	pos_r = mapToParent(point) - port_l->scenePos();
}

NODE::PORT::Data_I* NODE::Connection::getDataI() const {
	return static_cast<PORT::Data_I*>(port_r);
}

NODE::PORT::Data_O* NODE::Connection::getDataO() const {
	return static_cast<PORT::Data_O*>(port_l);
}

NODE::PORT::Exec_O* NODE::Connection::getExecO() const {
	return static_cast<PORT::Exec_O*>(port_l);
}

NODE::PORT::Exec_I* NODE::Connection::getExecI() const {
	return static_cast<PORT::Exec_I*>(port_r);
}

NODE::PORT::Data_I::Data_I(Node* parent, const QString& label) :
	Port(parent),
	label(label),
	var_type(VARIABLE::Type::NONE),
	color(VARIABLE::toColor(var_type)),
	variable(Variable()),
	onTypeChanged(nullptr),
	connection(nullptr)
{
	parent->inputs.push(this);
	rect.moveCenter(parent->rect.topLeft() + QPointF(0, 20 + parent->inputs.size() * 20));
}

NODE::PORT::Data_I::Data_I(Node* parent, const QString& label, const VARIABLE::Type& var_type) :
	Port(parent),
	label(label),
	var_type(var_type),
	color(VARIABLE::toColor(var_type)),
	variable(Variable()),
	onTypeChanged(nullptr),
	connection(nullptr)
{
	parent->inputs.push(this);
	rect.moveCenter(parent->rect.topLeft() + QPointF(0, 20 + parent->inputs.size() * 20));
}

NODE::PORT::Data_I::Data_I(Node* parent, const QString& label, const Variable& default_variable) :
	Port(parent),
	label(label),
	var_type(default_variable.type),
	color(VARIABLE::toColor(default_variable.type)),
	variable(default_variable),
	onTypeChanged(nullptr),
	connection(nullptr)
{
	parent->inputs.push(this);
	rect.moveCenter(parent->rect.topLeft() + QPointF(0, 20 + parent->inputs.size() * 20));
}

NODE::PORT::Data_I::~Data_I() {
	if (connected()) {
		disconnect();
	}
}

bool NODE::PORT::Data_I::connected() const {
	return connection != nullptr;
}

bool NODE::PORT::Data_I::canConnect(Data_O* port) {
	auto temp = make_unique<Connection>(port, this);
	if (port->requestConnection(temp.get()) and requestConnection(temp.get())) {
		return true;
	}
	return false;
}

void NODE::PORT::Data_I::connect(Data_O* port) {
	connection = make_unique<Connection>(port, this);
	port->connections.push(connection.get());
}

void NODE::PORT::Data_I::disconnect() {
	auto port_l = connection->getDataO();
	port_l->connections.remove(connection.get());
	connection.reset();

	if (port_l->onDisconnection) {
		port_l->onDisconnection(this);
	}

	if (onDisconnection) {
		onDisconnection(this);
	}
}

void NODE::PORT::Data_I::setType(const VARIABLE::Type& type) {
	var_type = type;
	variable = Variable(var_type);
	color = VARIABLE::toColor(type);
	if (connection) {
		connection->color = toColor(var_type);
		auto other = static_cast<Data_O*>(connection->port_l);
		if (other->var_type != var_type) {
			other->setType(var_type);
		}
	}
	if (onTypeChanged) {
		onTypeChanged(this, var_type);
	}
	update();
}

Variable NODE::PORT::Data_I::getData() const {
	if (connection) {
		return connection->getDataO()->getData();
	}
	return variable;
}

bool NODE::PORT::Data_I::requestConnection(Connection* connection) {
	if (var_type == VARIABLE::Type::BLOCKED) {
		return false;
	}
	if (onConnRequested) {
		return onConnRequested(this, connection);
	}
	if (static_cast<Data_O*>(connection->port_l)->var_type == var_type) {
		return true;
	}
	return false;
}

int NODE::PORT::Data_I::type() const {
	return Graphics_Item_Type::E_DATA_I;
}

void NODE::PORT::Data_I::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);
	painter->drawEllipse(rect);

	painter->drawText(rect.bottomRight() + QPointF(5, 0), label);

	painter->setPen(QPen(Qt::white, 0.5));
	switch (var_type) {
	case VARIABLE::Type::VEC2:
	case VARIABLE::Type::MAT2: {
		painter->drawLine(rect.center() - QPointF(3.5, 3.5), rect.center() + QPointF(3.5, 3.5));
		break;
	}
	case VARIABLE::Type::VEC3:
	case VARIABLE::Type::MAT3: {
		painter->drawLine(rect.center(), rect.center() + QPointF(4.9, 0));
		painter->drawLine(rect.center(), rect.center() + QPointF(-2.45,  4.32));
		painter->drawLine(rect.center(), rect.center() + QPointF(-2.45, -4.32));
		break;

	}
	case VARIABLE::Type::VEC4:
	case VARIABLE::Type::MAT4: {
		painter->drawLine(rect.center() - QPointF(3.5, 3.5), rect.center() + QPointF(3.5, 3.5));
		painter->drawLine(rect.center() - QPointF(-3.5, 3.5), rect.center() + QPointF(-3.5, 3.5));
		break;
	}
	}
}

NODE::PORT::Data_O::Data_O(Node* parent, const QString& label) :
	Port(parent),
	label(label),
	var_type(VARIABLE::Type::NONE),
	color(VARIABLE::toColor(var_type)),
	onTypeChanged(nullptr)
{
	parent->outputs.push(this);
	rect.moveCenter(parent->rect.topRight() + QPointF(0, 20 + parent->outputs.size() * 20));
}

NODE::PORT::Data_O::Data_O(Node* parent, const QString& label, const VARIABLE::Type& var_type) :
	Port(parent),
	label(label),
	var_type(var_type),
	color(VARIABLE::toColor(var_type)),
	onTypeChanged(nullptr)
{
	parent->outputs.push(this);
	rect.moveCenter(parent->rect.topRight() + QPointF(0, 20 + parent->outputs.size() * 20));
}

NODE::PORT::Data_O::~Data_O() {
	if (connected()) {
		disconnect();
	}
}

void NODE::PORT::Data_O::disconnect() {
	for (Connection* connection : connections) {
		auto port_r = connection->getDataI();
		port_r->connection.reset();
		if (port_r->onDisconnection) {
			port_r->onDisconnection(this);
		}
	}
	connections.clear();
	if (onDisconnection) {
		onDisconnection(this);
	}
}

bool NODE::PORT::Data_O::connected() const {
	return !connections.empty();
}

void NODE::PORT::Data_O::setType(const VARIABLE::Type& type) {
	var_type = type;
	color = VARIABLE::toColor(type);
	for (Connection* conn : connections) {
		conn->color = toColor(var_type);
		auto other = static_cast<Data_I*>(conn->port_r);
		if (other->var_type != var_type) {
			other->setType(var_type);
		}
	}
	if (onTypeChanged) {
		onTypeChanged(this, var_type);
	}
	update();
}

Variable NODE::PORT::Data_O::getData() const {
	return node->getData(this);
}

bool NODE::PORT::Data_O::requestConnection(Connection* connection) {
	if (var_type == VARIABLE::Type::BLOCKED) {
		return false;
	}
	if (onConnRequested) {
		return onConnRequested(this, connection);
	}
	if (static_cast<Data_I*>(connection->port_r)->var_type == var_type) {
		return true;
	}
	return false;
}

int NODE::PORT::Data_O::type() const {
	return Graphics_Item_Type::E_DATA_O;
}

void NODE::PORT::Data_O::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);

	painter->drawEllipse(rect);
	const qreal width = - QFontMetrics(QApplication::font()).horizontalAdvance(label) - 5;
	painter->drawText(rect.bottomLeft() + QPointF(width, 0), label);

	painter->setPen(QPen(Qt::white, 0.5));
	switch (var_type) {
	case VARIABLE::Type::VEC2:
	case VARIABLE::Type::MAT2: {
		painter->drawLine(rect.center() - QPointF(3.5, 3.5), rect.center() + QPointF(3.5, 3.5));
		break;
	}
	case VARIABLE::Type::VEC3:
	case VARIABLE::Type::MAT3: {
		painter->drawLine(rect.center(), rect.center() + QPointF(-4.9, 0));
		painter->drawLine(rect.center(), rect.center() + QPointF(2.45,  4.32));
		painter->drawLine(rect.center(), rect.center() + QPointF(2.45, -4.32));
		break;

	}
	case VARIABLE::Type::VEC4:
	case VARIABLE::Type::MAT4: {
		painter->drawLine(rect.center() - QPointF(3.5, 3.5), rect.center() + QPointF(3.5, 3.5));
		painter->drawLine(rect.center() - QPointF(-3.5, 3.5), rect.center() + QPointF(-3.5, 3.5));
		break;
	}
	}
}

NODE::PORT::Exec_O::Exec_O(Node* parent, const QString& label) :
	Port(parent),
	label(label),
	connection(nullptr)
{
	parent->outputs.push(this);
	rect.moveCenter(parent->rect.topRight() + QPointF(0, 20 + parent->outputs.size() * 20));
}

NODE::PORT::Exec_O::~Exec_O() {
	if (connected()) {
		disconnect();
	}
}

bool NODE::PORT::Exec_O::connected() const {
	return connection != nullptr;
}

bool NODE::PORT::Exec_O::canConnect(Exec_I* port) {
	auto temp = make_unique<Connection>(this, port);
	if (requestConnection(temp.get()) and port->requestConnection(temp.get())) {
		return true;
	}
	return false;
}

void NODE::PORT::Exec_O::connect(Exec_I* port) {
	connection = make_unique<Connection>(this, port);
	port->connections.push(connection.get());
}

void NODE::PORT::Exec_O::disconnect() {
	auto port_r = connection->getExecI();
	port_r->connections.remove(connection.get());
	connection.reset();

	if (port_r->onDisconnection) {
		port_r->onDisconnection(this);
	}

	if (onDisconnection) {
		onDisconnection(this);
	}
}

void NODE::PORT::Exec_O::exec() const {
	if (connection) {
		connection->getExecI()->node->exec(this);
	}
}

int NODE::PORT::Exec_O::type() const {
	return Graphics_Item_Type::E_EXEC_O;
}

void NODE::PORT::Exec_O::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(Qt::black);
	painter->setPen(QPen(Qt::white, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	QPainterPath path;
	path.moveTo(rect.topLeft());
	path.lineTo(rect.topRight() - QPointF(2.5, 0));
	path.lineTo(rect.center() + QPointF(7.5, 0));
	path.lineTo(rect.bottomRight() - QPointF(2.5, 0));
	path.lineTo(rect.bottomLeft());
	path.lineTo(rect.center() - QPointF(2.5, 0));
	path.lineTo(rect.topLeft());
	painter->drawPath(path);

	const qreal width = - QFontMetrics(QApplication::font()).horizontalAdvance(label) - 5;
	painter->drawText(rect.bottomLeft() + QPointF(width, 0), label);
}

NODE::PORT::Exec_I::Exec_I(Node* parent, const QString& label) :
	Port(parent),
	label(label)
{
	parent->inputs.push(this);
	rect.moveCenter(parent->rect.topLeft() + QPointF(0, 20 + parent->inputs.size() * 20));
}

NODE::PORT::Exec_I::~Exec_I() {
	if (connected()) {
		disconnect();
	}
}

void NODE::PORT::Exec_I::disconnect() {
	for (Connection* connection : connections) {
		auto port_l = connection->getExecO();
		port_l->connection.reset();
		if (port_l->onDisconnection) {
			port_l->onDisconnection(this);
		}
	}
	connections.clear();
	if (onDisconnection) {
		onDisconnection(this);
	}
}

bool NODE::PORT::Exec_I::connected() const {
	return !connections.empty();
}

int NODE::PORT::Exec_I::type() const {
	return Graphics_Item_Type::E_EXEC_I;
}

void NODE::PORT::Exec_I::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(Qt::black);
	painter->setPen(QPen(Qt::white, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	QPainterPath path;
	path.moveTo(rect.topLeft());
	path.lineTo(rect.topRight() - QPointF(2.5, 0));
	path.lineTo(rect.center() + QPointF(7.5, 0));
	path.lineTo(rect.bottomRight() - QPointF(2.5, 0));
	path.lineTo(rect.bottomLeft());
	path.lineTo(rect.center() - QPointF(2.5, 0));
	path.lineTo(rect.topLeft());
	painter->drawPath(path);

	painter->drawText(rect.bottomRight() + QPointF(5, 0), label);
}

#include "Session.hpp"
#include "Window.hpp"
#include "Nodes.hpp"
tuple<Node*, U64> Node::load(const Token_Array& tokens) {
	const string  r_label = f_join(tokens[0], 4);
	const U64     r_ptr = stoU64(tokens[1][1]);
	const string  r_type = tokens[2][1];
	const QPointF r_pos = QPointF(stoF64(tokens[3][1]), stoF64(tokens[3][2]));

	Node* node = nullptr;

	if (r_type == "SINGLETON::EULER_TICK") {
		node = new NODES::SINGLETON::Euler_Tick();
	}
	else if (r_type == "SINGLETON::RESET") {
		node = new NODES::SINGLETON::Reset();
	}

	if (node) {
		node->label = qstr(r_label);

		SESSION->window->node_editor->scene->addItem(node);
		node->setPos(r_pos);
	}
	return tie(node, r_ptr);
}
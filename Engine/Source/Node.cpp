#include "Node.hpp"

NODE::Node::Node(const QString& label) :
	QGraphicsItem(),
	label(label),
	rect(QRectF(0, 0, 200, 200))
{
	setZValue(1);
	setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
}

NODE::Node::~Node() {
	for (Port* port : inputs) {
		delete port;
	}
	for (Port* port : outputs) {
		delete port;
	}
}

void NODE::Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(150, 200, 255), 3.0));
	}

	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);

	painter->setBrush(QColor(25, 25, 25));
	painter->drawRoundedRect(QRectF(rect.topLeft(), QSize(rect.width(), 20)), 5, 5);

	painter->setPen(Qt::white);
	painter->drawText(QRectF(rect.topLeft(), QSize(rect.width(), 20)), Qt::AlignCenter, label);
}

QRectF NODE::Node::boundingRect() const {
	return rect;
}

NODE::Port::Port(Node* node) :
	QGraphicsItem(node),
	node(node),
	conn_request(nullptr),
	disconnection(nullptr),
	rect(QRectF(0, 0, 10, 10))
{
	setZValue(10);
}

bool NODE::Port::onConnRequested(Connection* connection) {
	if (conn_request) {
		return conn_request(this, connection);
	}
	return true;
}

void NODE::Port::onDisconnected() {
	if (disconnection) {
		disconnection(this);
	}
}

void NODE::Port::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
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
	setZValue(5);
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

NODE::Connection::~Connection() {
	if (auto port = dynamic_cast<PORT::Exec_I*>(port_r)) {
		auto it = std::find(port->connections.begin(), port->connections.end(), this);
		if (it != port->connections.end()) {
			port->connections.erase(it);
		}
	}
	if (auto port = dynamic_cast<PORT::Exec_O*>(port_l)) {
		port->connection = nullptr;
	}
	if (auto port = dynamic_cast<PORT::Data_I*>(port_r)) {
		port->connection = nullptr;
	}
	if (auto port = dynamic_cast<PORT::Data_O*>(port_l)) {
		auto it = std::find(port->connections.begin(), port->connections.end(), this);
		if (it != port->connections.end()) {
			port->connections.erase(it);
		}
	}
}

void NODE::Connection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setPen(QPen(color, 2.0));
	if (port_l and port_r) {
		pos_l = mapFromItem(port_l, port_l->boundingRect().center());
		pos_r = mapFromItem(port_r, port_r->boundingRect().center());

		QPainterPath path;
		path.moveTo(pos_l);
		path.lineTo(pos_l + QPointF((pos_r.x() - pos_l.x())/2.0, 0));
		path.lineTo(pos_r + QPointF((pos_l.x() - pos_r.x())/2.0, 0));
		path.lineTo(pos_r);

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

NODE::PORT::Exec_I* NODE::Connection::getExecI() const {
	return static_cast<PORT::Exec_I*>(port_r);
}

NODE::PORT::Exec_O* NODE::Connection::getExecO() const {
	return static_cast<PORT::Exec_O*>(port_l);
}

NODE::PORT::Data_I* NODE::Connection::getDataI() const {
	return static_cast<PORT::Data_I*>(port_r);
}

NODE::PORT::Data_O* NODE::Connection::getDataO() const {
	return static_cast<PORT::Data_O*>(port_l);
}

NODE::PORT::Exec_I::Exec_I(Node* parent, const QString& label) :
	Port(parent),
	label(label)
{
	parent->inputs.push_back(this);
	rect.moveTopLeft(parent->rect.topLeft() + QPointF(-5, 20 + parent->inputs.size() * 20));
}

NODE::PORT::Exec_I::~Exec_I() {
	for (Connection* connection : connections) {
		static_cast<Exec_O*>(connection->port_l)->connection = nullptr;
		delete connection;
	}
}

bool NODE::PORT::Exec_I::connected() const {
	return !connections.empty();
}

void NODE::PORT::Exec_I::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);
	painter->drawRoundedRect(rect, 1, 1);

	painter->drawText(rect.bottomRight() + QPointF(10, 0), label);
}

NODE::PORT::Exec_O::Exec_O(Node* parent, const QString& label) :
	Port(parent),
	label(label),
	connection(nullptr)
{
	parent->outputs.push_back(this);
	rect.moveCenter(parent->rect.topRight() + QPointF(0, 20 + parent->outputs.size() * 20));
}

NODE::PORT::Exec_O::~Exec_O() {
	if (connection) {
		if (Exec_I* port = dynamic_cast<Exec_I*>(connection->port_r)) {
			port->connections.erase(std::find(port->connections.begin(), port->connections.end(), connection));
		}
		delete connection;
		connection = nullptr;
	}
}

bool NODE::PORT::Exec_O::connected() const {
	return connection != nullptr;
}

void NODE::PORT::Exec_O::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);

	painter->drawRoundedRect(rect, 1, 1);
	const qreal width = - QFontMetrics(QApplication::font()).horizontalAdvance(label) - 10;
	painter->drawText(rect.bottomLeft() + QPointF(width, 0), label);
}

NODE::PORT::Data_I::Data_I(Node* parent, const QString& label) :
	Port(parent),
	label(label),
	var_type(VARIABLE::Type::NONE),
	color(VARIABLE::toColor(var_type)),
	connection(nullptr)
{
	parent->inputs.push_back(this);
	rect.moveCenter(parent->rect.topLeft() + QPointF(0, 20 + parent->inputs.size() * 20));
}

NODE::PORT::Data_I::Data_I(Node* parent, const QString& label, const VARIABLE::Type& var_type) :
	Port(parent),
	label(label),
	var_type(var_type),
	color(VARIABLE::toColor(var_type)),
	connection(nullptr)
{
	parent->inputs.push_back(this);
	rect.moveCenter(parent->rect.topLeft() + QPointF(0, 20 + parent->inputs.size() * 20));
}


NODE::PORT::Data_I::~Data_I() {
	if (connection) {
		if (Data_O* port = dynamic_cast<Data_O*>(connection->port_r)) {
			port->connections.erase(std::find(port->connections.begin(), port->connections.end(), connection));
		}
		delete connection;
		connection = nullptr;
	}
}

bool NODE::PORT::Data_I::connected() const {
	return connection != nullptr;
}

void NODE::PORT::Data_I::setType(const VARIABLE::Type& type) {
	var_type = type;
	color = VARIABLE::toColor(type);
}

Variable NODE::PORT::Data_I::getData() const {
	if (connection) {
		connection->getDataO()->getData();
	}
	return variable;
}

void NODE::PORT::Data_I::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);
	painter->drawEllipse(rect);

	painter->drawText(rect.bottomRight() + QPointF(10, 0), label);
}

NODE::PORT::Data_O::Data_O(Node* parent, const QString& label) :
	Port(parent),
	label(label),
	var_type(VARIABLE::Type::NONE),
	color(VARIABLE::toColor(var_type))
{
	parent->outputs.push_back(this);
	rect.moveCenter(parent->rect.topRight() + QPointF(0, 20 + parent->outputs.size() * 20));
}

NODE::PORT::Data_O::Data_O(Node* parent, const QString& label, const VARIABLE::Type& var_type) :
	Port(parent),
	label(label),
	var_type(var_type),
	color(VARIABLE::toColor(var_type))
{
	parent->outputs.push_back(this);
	rect.moveCenter(parent->rect.topRight() + QPointF(0, 20 + parent->outputs.size() * 20));
}

NODE::PORT::Data_O::~Data_O() {
	for (Connection* connection : connections) {
		static_cast<Data_I*>(connection->port_l)->connection = nullptr;
		delete connection;
	}
}

bool NODE::PORT::Data_O::connected() const {
	return !connections.empty();
}

void NODE::PORT::Data_O::setType(const VARIABLE::Type& type) {
	var_type = type;
	color = VARIABLE::toColor(type);
}

Variable NODE::PORT::Data_O::getData() const {
	return node->getData(this);
}

void NODE::PORT::Data_O::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);

	painter->drawEllipse(rect);
	const qreal width = - QFontMetrics(QApplication::font()).horizontalAdvance(label) - 10;
	painter->drawText(rect.bottomLeft() + QPointF(width, 0), label);
}
#include "Node.hpp"

NODE::Node::Node(const QString& label) :
	label(label)
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

void NODE::Node::addInputData(const QString& label, const VARIABLE::Type& type, const VARIABLE::Modifier& modifier) {
	PORT::Data_I* port = new PORT::Data_I(this, label, type, modifier);
	inputs.push_back(port);
}

void NODE::Node::addInputExec(const QString& label) {
	PORT::Exec_I* port = new PORT::Exec_I(this, label);
	inputs.push_back(port);
}

void NODE::Node::addOutputData(const QString& label, const VARIABLE::Type& type, const VARIABLE::Modifier& modifier) {
	PORT::Data_O* port = new PORT::Data_O(this, label, type, modifier);
	outputs.push_back(port);
}

void NODE::Node::addOutputExec(const QString& label) {
	PORT::Exec_O* port = new PORT::Exec_O(this, label);
	outputs.push_back(port);
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
	node(node)
{
	setZValue(10);
}

void NODE::Port::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
}

QRectF NODE::Port::boundingRect() const {
	return rect.marginsAdded(QMarginsF(5, 5, 5, 5));
}

NODE::Connection::Connection(Port* port_l, Port* port_r) :
	port_l(port_l),
	port_r(port_r)
{
	setZValue(5);
}

NODE::Connection::~Connection() {
	pos_l = mapFromItem(port_l, port_l->boundingRect().topRight());
	if (port_l and port_r) {
		pos_r = mapFromItem(port_r, port_r->boundingRect().center());
	}
	else {
		pos_r = pos_l;
	}

}

void NODE::Connection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setPen(QPen(port_l->color, 2.0));
	if (port_l and port_r) {
		pos_l = mapFromItem(port_l, port_l->boundingRect().topRight());
		pos_r = mapFromItem(port_r, port_r->boundingRect().topLeft());

		QPainterPath path;
		path.moveTo(pos_l + QPointF(0, 15));
		path.lineTo(pos_l + QPointF((pos_r.x() - pos_l.x())/2.0, 15));
		path.lineTo(pos_r + QPointF((pos_l.x() - pos_r.x())/2.0, 15));
		path.lineTo(pos_r + QPointF(0, 15));

		painter->drawPath(path);
	}
	else {
		QPainterPath path;
		path.moveTo(pos_l + QPointF(0, 15));
		path.lineTo(pos_r);

		painter->drawPath(path);
	}
}

QRectF NODE::Connection::boundingRect() const {
	const QPointF point_a = pos_l + QPointF(0, 15);
	const QPointF point_b = pos_r + QPointF(0, 15);

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

NODE::PORT::Exec_I::Exec_I(Node* parent, const QString& label) :
	Port(parent),
	label(label)
{}

NODE::PORT::Exec_I::~Exec_I() {
	for (Connection* connection : connections) {
		static_cast<Exec_O*>(connection->port_l)->connection = nullptr;
		delete connection;
	}
}

void NODE::PORT::Exec_I::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);
	painter->drawRoundedRect(QRectF(rect.topLeft() + QPointF(0,5), QSizeF(10,10)), 2, 2);

	painter->drawText(rect.bottomLeft() + QPointF(20, -4), label);
}

NODE::PORT::Exec_O::Exec_O(Node* parent, const QString& label) :
	Port(parent),
	label(label)
{}

NODE::PORT::Exec_O::~Exec_O() {
	if (connection) {
		if (Exec_I* port = dynamic_cast<Exec_I*>(connection->port_r)) {
			port->connections.erase(std::find(port->connections.begin(), port->connections.end(), connection));
		}
		delete connection;
		connection = nullptr;
	}
}

void NODE::PORT::Exec_O::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);

	painter->drawRoundedRect(QRectF(rect.topRight() + QPointF(-10,5), QSizeF(10,10)), 2, 2);
	const QFontMetrics fontMetrics(painter->font());
	painter->drawText(rect.bottomLeft() + QPointF(5, -4), label);
}

NODE::PORT::Data_I::Data_I(Node* parent, const QString& label, const VARIABLE::Type& type, const VARIABLE::Modifier& modifier) :
	Port(parent),
	label(label),
	type(type),
	modifier(modifier)
{}

NODE::PORT::Data_I::~Data_I() {
	if (connection) {
		if (Data_O* port = dynamic_cast<Data_O*>(connection->port_r)) {
			port->connections.erase(std::find(port->connections.begin(), port->connections.end(), connection));
		}
		delete connection;
		connection = nullptr;
	}
}

void NODE::PORT::Data_I::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);
	painter->drawEllipse(QRectF(rect.topLeft() + QPointF(0,5), QSizeF(10,10)));

	painter->drawText(rect.bottomLeft() + QPointF(20, -4), label);
}

NODE::PORT::Data_O::Data_O(Node* parent, const QString& label, const VARIABLE::Type& type, const VARIABLE::Modifier& modifier) :
	Port(parent),
	label(label),
	type(type),
	modifier(modifier)
{}
	
NODE::PORT::Data_O::~Data_O() {
	for (Connection* connection : connections) {
		static_cast<Data_I*>(connection->port_l)->connection = nullptr;
		delete connection;
	}
}

void NODE::PORT::Data_O::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	painter->setBrush(color);
	painter->setPen(Qt::white);

	painter->drawEllipse(QRectF(rect.topRight() + QPointF(-10,5), QSizeF(10,10)));
	const QFontMetrics fontMetrics(painter->font());
	painter->drawText(rect.bottomLeft() + QPointF(5, -4), label);
}
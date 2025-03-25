#include "Nodes.hpp"

#include "Session.hpp"
#include "Viewport.hpp"

NODES::Arithmetic::Arithmetic() :
	Node("Arithmetic"),
	var_type(VARIABLE::Type::NONE),
	allowed_types({ VARIABLE::Type::NONE, VARIABLE_INTEGRALS })
{
	rect.setWidth(100);
	rect.setHeight(80);

	i_a = new PORT::Data_I(this, "A", VARIABLE::Type::NONE);
	i_b = new PORT::Data_I(this, "B", VARIABLE::Type::NONE);
	out = new PORT::Data_O(this, "O", VARIABLE::Type::NONE);

	i_a->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	i_b->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	out->onConnRequested = [this](Port* port, Connection* conn){ return onConnRequested(port, conn); };
	i_a->onDisconnection = [this](Port* port){ onDisconnection(port); };
	i_b->onDisconnection = [this](Port* port){ onDisconnection(port); };
	out->onDisconnection = [this](Port* port){ onDisconnection(port); };
	i_a->onTypeChanged = [this](Port* port, const VARIABLE::Type& var_type){ setType(var_type); };
	i_b->onTypeChanged = [this](Port* port, const VARIABLE::Type& var_type){ setType(var_type); };
	out->onTypeChanged = [this](Port* port, const VARIABLE::Type& var_type){ setType(var_type); };

	i_a->variable = Variable(0LL);
	i_b->variable = Variable(0LL);

	enums = new GUI::Options(); // TODO verify delete
	enums->setFixedSize(40, 20);
	enums->addItems({ "+", "-", "*", "/" });

	auto pw_enums = new GUI::Graphics_Widget(enums, this);
	pw_enums->setPos(30, 30);
}

void NODES::Arithmetic::setType(const VARIABLE::Type& type) {
	if (var_type != type) {
		var_type = type;
		i_a->setType(type);
		i_b->setType(type);
		out->setType(type);
	}
}

bool NODES::Arithmetic::onConnRequested(Port* port, Connection* conn) {
	const VARIABLE::Type& incoming_type = (port == out) ? conn->getDataI()->var_type : conn->getDataO()->var_type;
	if (allowed_types.contains(incoming_type)) {
		if (var_type == VARIABLE::Type::NONE) {
			setType(incoming_type);
			conn->color = VARIABLE::toColor(incoming_type);
			return true;
		}
		else if (var_type == incoming_type or incoming_type == VARIABLE::Type::NONE) {
			return true;
		}
	}
	return false;
}

void NODES::Arithmetic::onDisconnection(Port* port) {
	if (not i_a->connected() and not i_b->connected() and not out->connected()) {
		setType(VARIABLE::Type::NONE);
	}
}

Variable NODES::Arithmetic::getData(const Port* port) const {
	switch (enums->currentIndex()) {
		case 0: return i_a->getData() + i_b->getData();
		case 1: return i_a->getData() - i_b->getData();
		case 2: return i_a->getData() * i_b->getData();
		case 3: return i_a->getData() / i_b->getData();
	}
	return Variable(0.0);
}

NODES::Trigonometry::Trigonometry() :
	Node("Trigonometry")
{
	rect.setWidth(140);
	rect.setHeight(60);

	in = new PORT::Data_I(this, "I", VARIABLE::Type::FLOAT);
	out = new PORT::Data_O(this, "O", VARIABLE::Type::FLOAT);

	in->onConnRequested  = [this](Port* port, Connection* conn){ return call_connRequest(port, conn); };
	out->onConnRequested = [this](Port* port, Connection* conn){ return call_connRequest(port, conn); };

	enums = new GUI::Options(); // TODO verify delete
	enums->setFixedSize(80, 20);
	enums->addItems({ "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "COT", "SEC", "CSC", "COTH", "SECH", "CSCH" });

	auto* proxyWidget = new GUI::Graphics_Widget(enums, this);
	proxyWidget->setPos(30, 30);
}

bool NODES::Trigonometry::call_connRequest(Port* port, Connection* conn) {
	const VARIABLE::Type& incoming_type = (port == out) ? conn->getDataI()->var_type : conn->getDataO()->var_type;
	if (incoming_type == VARIABLE::Type::FLOAT or incoming_type == VARIABLE::Type::NONE) {
		return true;
	}
	return false;
}

Variable NODES::Trigonometry::getData(const Port* port) const {
	const dvec1 x = in->getData().get<dvec1>();
	switch (enums->currentIndex()) {
		case  0: return sin(x);
		case  1: return cos(x);
		case  2: return tan(x);
		case  3: return asin(x);
		case  4: return acos(x);
		case  5: return atan(x);
		case  6: return sinh(x);
		case  7: return cosh(x);
		case  8: return tanh(x);
		case  9: return 1.0 / tan(x);
		case 10: return 1.0 / cos(x);
		case 11: return 1.0 / sin(x);
		case 12: return cosh(x) / sinh(x);
		case 13: return 1.0 / cosh(x);
		case 14: return 1.0 / sinh(x);
	}
	return Variable(x);
}

NODES::INPUT::Integer::Integer() :
	Node("Integer")
{
	rect.setWidth(60);
	rect.setHeight(60);

	out = new PORT::Data_O(this, "", VARIABLE::Type::INT);
	value = 0;

	input = new GUI::Value_Input();
	input->setFixedSize(40, 20);
	input->setText("0");
	input->setValidator(new QIntValidator(input));

	auto* proxyWidget = new GUI::Graphics_Widget(input, this);
	proxyWidget->setPos(10, 30);

	QObject::connect(input, &GUI::Value_Input::textEdited, [this](const QString& val) { value = val.toInt(); });
}

Variable NODES::INPUT::Integer::getData(const Port* port) const {
	return Variable(value);
}

NODES::INPUT::Double::Double() :
	Node("Double")
{
	rect.setWidth(80);
	rect.setHeight(60);

	out = new PORT::Data_O(this, "", VARIABLE::Type::FLOAT);
	value = 0.0;

	input = new GUI::Value_Input();
	input->setFixedSize(60, 20);
	input->setText("0");
	input->setValidator(new QDoubleValidator(input));

	auto* proxyWidget = new GUI::Graphics_Widget(input, this);
	proxyWidget->setPos(10, 30);

	QObject::connect(input, &GUI::Value_Input::textEdited, [this](const QString& val) { value = val.toDouble(); });
}

Variable NODES::INPUT::Double::getData(const Port* port) const {
	return Variable(value);
}

NODES::INPUT::Bool::Bool() :
	Node("Bool")
{
	rect.setWidth(40);
	rect.setHeight(60);

	out = new PORT::Data_O(this, "", VARIABLE::Type::BOOL);
	value = false;

	input = new GUI::Toggle();
	input->setFixedSize(20, 20);

	auto* proxyWidget = new GUI::Graphics_Widget(input, this);
	proxyWidget->setPos(10, 30);

	QObject::connect(input, &GUI::Toggle::toggled, [this](bool checked) { value = checked; });
}

Variable NODES::INPUT::Bool::getData(const Port* port) const {
	return Variable(value);
}

NODES::INPUT::String::String() :
	Node("String")
{
	rect.setWidth(140);
	rect.setHeight(60);

	out = new PORT::Data_O(this, "", VARIABLE::Type::STRING);
	value = "";

	input = new GUI::Value_Input();
	input->setFixedSize(120, 20);
	input->setText("");

	auto* proxyWidget = new GUI::Graphics_Widget(input, this);
	proxyWidget->setPos(10, 30);

	QObject::connect(input, &GUI::Value_Input::textEdited, [this](const QString& val) { value = val; });
}

Variable NODES::INPUT::String::getData(const Port* port) const {
	return Variable(value);
}

NODES::INPUT::Vec2::Vec2() :
	Node("Vec2")
{
	rect.setWidth(80);
	rect.setHeight(80);

	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC2);
	value = dvec2(0.0, 0.0);

	input_x = new GUI::Value_Input();
	input_x->setFixedSize(60, 20);
	input_x->setText("0");
	input_x->setValidator(new QDoubleValidator(input_x));

	input_y = new GUI::Value_Input();
	input_y->setFixedSize(60, 20);
	input_y->setText("0");
	input_y->setValidator(new QDoubleValidator(input_y));

	auto* proxyWidgetX = new GUI::Graphics_Widget(input_x, this);
	proxyWidgetX->setPos(10, 30);

	auto* proxyWidgetY = new GUI::Graphics_Widget(input_y, this);
	proxyWidgetY->setPos(10, 50);

	QObject::connect(input_x, &GUI::Value_Input::textEdited, [this](const QString& val) { value.x = val.toDouble(); });
	QObject::connect(input_y, &GUI::Value_Input::textEdited, [this](const QString& val) { value.y = val.toDouble(); });
}

Variable NODES::INPUT::Vec2::getData(const Port* port) const {
	return Variable(value);
}

NODES::INPUT::Vec3::Vec3() :
	Node("Vec3")
{
	rect.setWidth(80);
	rect.setHeight(100);

	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC3);
	value = dvec3(0.0, 0.0, 0.0);

	input_x = new GUI::Value_Input();
	input_x->setFixedSize(60, 20);
	input_x->setText("0");
	input_x->setValidator(new QDoubleValidator(input_x));

	input_y = new GUI::Value_Input();
	input_y->setFixedSize(60, 20);
	input_y->setText("0");
	input_y->setValidator(new QDoubleValidator(input_y));
	
	input_z = new GUI::Value_Input();
	input_z->setFixedSize(60, 20);
	input_z->setText("0");
	input_z->setValidator(new QDoubleValidator(input_z));

	auto* proxyWidgetX = new GUI::Graphics_Widget(input_x, this);
	proxyWidgetX->setPos(10, 30);

	auto* proxyWidgetY = new GUI::Graphics_Widget(input_y, this);
	proxyWidgetY->setPos(10, 50);
	
	auto* proxyWidgetZ = new GUI::Graphics_Widget(input_z, this);
	proxyWidgetZ->setPos(10, 70);

	QObject::connect(input_x, &GUI::Value_Input::textEdited, [this](const QString& val) { value.x = val.toDouble(); });
	QObject::connect(input_y, &GUI::Value_Input::textEdited, [this](const QString& val) { value.y = val.toDouble(); });
	QObject::connect(input_z, &GUI::Value_Input::textEdited, [this](const QString& val) { value.z = val.toDouble(); });
}

Variable NODES::INPUT::Vec3::getData(const Port* port) const {
	return Variable(value);
}

NODES::INPUT::Vec4::Vec4() :
	Node("Vec4")
{
	rect.setWidth(80);
	rect.setHeight(120);

	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC4);
	value = dvec4(0.0, 0.0, 0.0, 0.0);

	input_x = new GUI::Value_Input();
	input_x->setFixedSize(60, 20);
	input_x->setText("0");
	input_x->setValidator(new QDoubleValidator(input_x));

	input_y = new GUI::Value_Input();
	input_y->setFixedSize(60, 20);
	input_y->setText("0");
	input_y->setValidator(new QDoubleValidator(input_y));
	
	input_z = new GUI::Value_Input();
	input_z->setFixedSize(60, 20);
	input_z->setText("0");
	input_z->setValidator(new QDoubleValidator(input_z));
	
	input_w = new GUI::Value_Input();
	input_w->setFixedSize(60, 20);
	input_w->setText("0");
	input_w->setValidator(new QDoubleValidator(input_w));

	auto* proxyWidgetX = new GUI::Graphics_Widget(input_x, this);
	proxyWidgetX->setPos(10, 30);

	auto* proxyWidgetY = new GUI::Graphics_Widget(input_y, this);
	proxyWidgetY->setPos(10, 50);

	auto* proxyWidgetZ = new GUI::Graphics_Widget(input_z, this);
	proxyWidgetZ->setPos(10, 70);

	auto* proxyWidgetW = new GUI::Graphics_Widget(input_w, this);
	proxyWidgetW->setPos(10, 90);

	QObject::connect(input_x, &GUI::Value_Input::textEdited, [this](const QString& val) { value.x = val.toDouble(); });
	QObject::connect(input_y, &GUI::Value_Input::textEdited, [this](const QString& val) { value.y = val.toDouble(); });
	QObject::connect(input_z, &GUI::Value_Input::textEdited, [this](const QString& val) { value.z = val.toDouble(); });
	QObject::connect(input_w, &GUI::Value_Input::textEdited, [this](const QString& val) { value.w = val.toDouble(); });
}

Variable NODES::INPUT::Vec4::getData(const Port* port) const {
	return Variable(value);
}

NODES::CAST::MAKE::Vec2::Vec2() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(40);

	i_x = new PORT::Data_I(this, "X", VARIABLE::Type::FLOAT);
	i_y = new PORT::Data_I(this, "Y", VARIABLE::Type::FLOAT);
	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC2);
	i_x->rect.moveCenter(QPointF( 0, 10));
	i_y->rect.moveCenter(QPointF( 0, 30));
	out->rect.moveCenter(QPointF(30, 20));
}

void NODES::CAST::MAKE::Vec2::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Vec2::getData(const Port* port) const {
	return Variable(dvec2(i_x->getData().get<dvec1>(), i_y->getData().get<dvec1>()));
}

NODES::CAST::MAKE::Vec3::Vec3() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(60);

	i_x = new PORT::Data_I(this, "X", VARIABLE::Type::FLOAT);
	i_y = new PORT::Data_I(this, "Y", VARIABLE::Type::FLOAT);
	i_z = new PORT::Data_I(this, "Z", VARIABLE::Type::FLOAT);
	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC3);
	i_x->rect.moveCenter(QPointF( 0, 10));
	i_y->rect.moveCenter(QPointF( 0, 30));
	i_z->rect.moveCenter(QPointF( 0, 50));
	out->rect.moveCenter(QPointF(30, 30));
}

void NODES::CAST::MAKE::Vec3::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Vec3::getData(const Port* port) const {
	return Variable(dvec3(i_x->getData().get<dvec1>(), i_y->getData().get<dvec1>(), i_z->getData().get<dvec1>()));
}

NODES::CAST::MAKE::Vec4::Vec4() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_x = new PORT::Data_I(this, "X", VARIABLE::Type::FLOAT);
	i_y = new PORT::Data_I(this, "Y", VARIABLE::Type::FLOAT);
	i_z = new PORT::Data_I(this, "Z", VARIABLE::Type::FLOAT);
	i_w = new PORT::Data_I(this, "W", VARIABLE::Type::FLOAT);
	out = new PORT::Data_O(this, "", VARIABLE::Type::VEC4);
	i_x->rect.moveCenter(QPointF( 0, 10));
	i_y->rect.moveCenter(QPointF( 0, 30));
	i_z->rect.moveCenter(QPointF( 0, 50));
	i_w->rect.moveCenter(QPointF( 0, 70));
	out->rect.moveCenter(QPointF(30, 40));
}

void NODES::CAST::MAKE::Vec4::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Vec4::getData(const Port* port) const {
	return Variable(dvec4(i_x->getData().get<dvec1>(), i_y->getData().get<dvec1>(), i_z->getData().get<dvec1>(), i_w->getData().get<dvec1>()));
}

NODES::CAST::MAKE::Quat::Quat() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_w = new PORT::Data_I(this, "W", VARIABLE::Type::FLOAT);
	i_x = new PORT::Data_I(this, "X", VARIABLE::Type::FLOAT);
	i_y = new PORT::Data_I(this, "Y", VARIABLE::Type::FLOAT);
	i_z = new PORT::Data_I(this, "Z", VARIABLE::Type::FLOAT);
	out = new PORT::Data_O(this, "", VARIABLE::Type::QUAT);
	i_w->rect.moveCenter(QPointF( 0, 10));
	i_x->rect.moveCenter(QPointF( 0, 30));
	i_y->rect.moveCenter(QPointF( 0, 50));
	i_z->rect.moveCenter(QPointF( 0, 70));
	out->rect.moveCenter(QPointF(30, 40));
}

void NODES::CAST::MAKE::Quat::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Quat::getData(const Port* port) const {
	return Variable(dquat(i_w->getData().get<dvec1>(), i_x->getData().get<dvec1>(), i_y->getData().get<dvec1>(), i_z->getData().get<dvec1>()));
}

NODES::CAST::MAKE::Mat2::Mat2() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(40);

	i_a = new PORT::Data_I(this, "A", VARIABLE::Type::VEC2);
	i_b = new PORT::Data_I(this, "B", VARIABLE::Type::VEC2);
	out = new PORT::Data_O(this, "", VARIABLE::Type::MAT2);
	i_a->rect.moveCenter(QPointF( 0, 10));
	i_b->rect.moveCenter(QPointF( 0, 30));
	out->rect.moveCenter(QPointF(30, 20));
}

void NODES::CAST::MAKE::Mat2::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Mat2::getData(const Port* port) const {
	return Variable(dmat2(i_a->getData().get<dvec2>(), i_b->getData().get<dvec2>()));
}

NODES::CAST::MAKE::Mat3::Mat3() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(60);

	i_a = new PORT::Data_I(this, "A", VARIABLE::Type::VEC3);
	i_b = new PORT::Data_I(this, "B", VARIABLE::Type::VEC3);
	i_c = new PORT::Data_I(this, "C", VARIABLE::Type::VEC3);
	out = new PORT::Data_O(this, "", VARIABLE::Type::MAT3);
	i_a->rect.moveCenter(QPointF( 0, 10));
	i_b->rect.moveCenter(QPointF( 0, 30));
	i_c->rect.moveCenter(QPointF( 0, 50));
	out->rect.moveCenter(QPointF(30, 30));
}

void NODES::CAST::MAKE::Mat3::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Mat3::getData(const Port* port) const {
	return Variable(dmat3(i_a->getData().get<dvec3>(), i_b->getData().get<dvec3>(), i_c->getData().get<dvec3>()));
}

NODES::CAST::MAKE::Mat4::Mat4() :
	Node("Make")
{
	rect.setWidth(30);
	rect.setHeight(80);

	i_a = new PORT::Data_I(this, "A", VARIABLE::Type::VEC4);
	i_b = new PORT::Data_I(this, "B", VARIABLE::Type::VEC4);
	i_c = new PORT::Data_I(this, "C", VARIABLE::Type::VEC4);
	i_d = new PORT::Data_I(this, "D", VARIABLE::Type::VEC4);
	out = new PORT::Data_O(this, "", VARIABLE::Type::MAT4);
	i_a->rect.moveCenter(QPointF( 0, 10));
	i_b->rect.moveCenter(QPointF( 0, 30));
	i_c->rect.moveCenter(QPointF( 0, 50));
	i_d->rect.moveCenter(QPointF( 0, 70));
	out->rect.moveCenter(QPointF(30, 40));
}

void NODES::CAST::MAKE::Mat4::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	if (isSelected()) {
		painter->setPen(QPen(QColor(255, 140, 80), 2.0));
	}
	painter->setBrush(QColor(40, 40, 40));
	painter->drawRoundedRect(rect, 5, 5);
}

Variable NODES::CAST::MAKE::Mat4::getData(const Port* port) const {
	return Variable(dmat4(i_a->getData().get<dvec4>(), i_b->getData().get<dvec4>(), i_c->getData().get<dvec4>(), i_d->getData().get<dvec4>()));
}

NODES::EXEC::Euler_Tick::Euler_Tick() :
	Node("Tick")
{
	delta = 0.016;
	rect.setWidth(60);
	rect.setHeight(80);

	exec_out = new PORT::Exec_O(this, "Tick");
	delta_out = new PORT::Data_O(this, "Delta", VARIABLE::Type::FLOAT);
}

void NODES::EXEC::Euler_Tick::exec(const dvec1& delta) {
	this->delta = delta;
	exec_out->exec();
}

Variable NODES::EXEC::Euler_Tick::getData(const Port* port) const {
	return Variable(delta);
}

NODES::RENDERING::DIM_2D::Line::Line() :
	Node("2D Line")
{
	VAO, VBO, EBO = 0;

	header_color = QColor(75, 25, 25);
	rect.setWidth(80);
	rect.setHeight(140);

	exec_in  = new PORT::Exec_I(this, "Draw");
	exec_out = new PORT::Exec_O(this, "");

	vert_a = new PORT::Data_I(this, "Pos A", VARIABLE::Type::VEC2);
	vert_b = new PORT::Data_I(this, "Pos B", VARIABLE::Type::VEC2);
	width  = new PORT::Data_I(this, "Width", VARIABLE::Type::FLOAT);
	color  = new PORT::Data_I(this, "Color", VARIABLE::Type::VEC4);

	vert_a->variable = Variable(dvec2(-200, -200));
	vert_b->variable = Variable(dvec2( 200,  200));
	width->variable  = Variable(3.0);
	color->variable  = Variable(dvec4(1, 1, 1, 1));
	init();
}

void NODES::RENDERING::DIM_2D::Line::init() {
	const GLfloat vertices[8] = { 0 };
	const GLuint indices[6] = {
		0, 1, 2,
		0, 2, 3
	};
	GL->glGenVertexArrays(1, &VAO);
	GL->glGenBuffers(1, &VBO);
	GL->glGenBuffers(1, &EBO);

	GL->glBindVertexArray(VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void NODES::RENDERING::DIM_2D::Line::render() {
	// Update vertices
	const vec2 v1      = d_to_f(vert_a->getData().get<dvec2>());
	const vec2 v2      = d_to_f(vert_b->getData().get<dvec2>());
	const vec1 radius  = d_to_f(width ->getData().get<dvec1>());
	const vec4 u_color = d_to_f(color ->getData().get<dvec4>());

	vec2 lineDir = d_to_f(glm::normalize(v2 - v1));
	vec2 perpDir = vec2(-lineDir.y, lineDir.x);

	vec2 np1_top    = v1 + perpDir * radius * 0.5f;
	vec2 np1_bottom = v1 - perpDir * radius * 0.5f;
	vec2 np2_top    = v2 + perpDir * radius * 0.5f;
	vec2 np2_bottom = v2 - perpDir * radius * 0.5f;

	const GLfloat vertices[] = {
		np1_top.x, np1_top.y,
		np1_bottom.x, np1_bottom.y,
		np2_bottom.x, np2_bottom.y,
		np2_top.x, np2_top.y
	};
	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// Render
	const GLuint Shader = SESSION.viewport->SP_2D_Line;
	GL->glUseProgram(Shader);
	GL->glUniform2uiv(GL->glGetUniformLocation(Shader, "uResolution"), 1, glm::value_ptr(SESSION.viewport->resolution));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(d_to_f(SESSION.viewport->center_2d)));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uZoom"), d_to_f(SESSION.viewport->zoom_2d));

	GL->glUniform4fv (GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(u_color));

	GL->glBindVertexArray(VAO);
	GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}

void NODES::RENDERING::DIM_2D::Line::exec(const Port* port) {
	render();
	exec_out->exec();
}

NODES::RENDERING::DIM_2D::Triangle::Triangle() :
	Node("2D Tri")
{
	VAO, VBO = 0;

	header_color = QColor(75, 25, 25);
	rect.setWidth(80);
	rect.setHeight(140);

	exec_in  = new PORT::Exec_I(this, "Draw");
	exec_out = new PORT::Exec_O(this, "");

	vert_a = new PORT::Data_I(this, "Pos A", VARIABLE::Type::VEC2);
	vert_b = new PORT::Data_I(this, "Pos B", VARIABLE::Type::VEC2);
	vert_c = new PORT::Data_I(this, "Pos C", VARIABLE::Type::VEC2);
	color  = new PORT::Data_I(this, "Color", VARIABLE::Type::VEC4);

	vert_a->variable = Variable(dvec2(  0,  57.777));
	vert_b->variable = Variable(dvec2(-50, -28.868));
	vert_c->variable = Variable(dvec2( 50, -28.868));
	color->variable  = Variable(dvec4(1, 1, 1, 1));
	init();
}

void NODES::RENDERING::DIM_2D::Triangle::init() {
	const GLfloat vertices[6] = { 0 };
	GL->glGenVertexArrays(1, &VAO);
	GL->glGenBuffers(1, &VBO);

	GL->glBindVertexArray(VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void NODES::RENDERING::DIM_2D::Triangle::render() {
	// Update vertices
	const vec2 v1      = d_to_f(vert_a->getData().get<dvec2>());
	const vec2 v2      = d_to_f(vert_b->getData().get<dvec2>());
	const vec2 v3      = d_to_f(vert_c->getData().get<dvec2>());
	const vec4 u_color = d_to_f(color ->getData().get<dvec4>());

	const GLfloat vertices[6] = {
		v1.x, v1.y,
		v2.x, v2.y,
		v3.x, v3.y
	};
	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// Render
	const GLuint Shader = SESSION.viewport->SP_2D_Triangle;
	GL->glUseProgram(Shader);
	GL->glUniform2uiv(GL->glGetUniformLocation(Shader, "uResolution"), 1, glm::value_ptr(SESSION.viewport->resolution));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(d_to_f(SESSION.viewport->center_2d)));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uZoom"), d_to_f(SESSION.viewport->zoom_2d));

	GL->glUniform4fv (GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(u_color));

	GL->glBindVertexArray(VAO);
	GL->glDrawArrays(GL_TRIANGLES, 0, 3);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}

void NODES::RENDERING::DIM_2D::Triangle::exec(const Port* port) {
	render();
	exec_out->exec();
}

NODES::RENDERING::DIM_2D::Rectangle::Rectangle() :
	Node("2D Rect")
{
	VAO, VBO, EBO = 0;

	header_color = QColor(75, 25, 25);
	rect.setWidth(80);
	rect.setHeight(160);

	exec_in  = new PORT::Exec_I(this, "Draw");
	exec_out = new PORT::Exec_O(this, "");

	vert_a = new PORT::Data_I(this, "Pos A", VARIABLE::Type::VEC2);
	vert_b = new PORT::Data_I(this, "Pos B", VARIABLE::Type::VEC2);
	vert_c = new PORT::Data_I(this, "Pos C", VARIABLE::Type::VEC2);
	vert_d = new PORT::Data_I(this, "Pos D", VARIABLE::Type::VEC2);
	color  = new PORT::Data_I(this, "Color", VARIABLE::Type::VEC4);

	vert_a->variable = Variable(dvec2(-100, -100));
	vert_b->variable = Variable(dvec2(-100,  100));
	vert_c->variable = Variable(dvec2( 100,  100));
	vert_d->variable = Variable(dvec2( 100, -100));
	color->variable  = Variable(dvec4(1, 1, 1, 1));
	init();
}

void NODES::RENDERING::DIM_2D::Rectangle::init() {
	const GLfloat vertices[8] = { 0 };
	const GLuint indices[6] = {
		0, 1, 2,
		0, 2, 3
	};
	GL->glGenVertexArrays(1, &VAO);
	GL->glGenBuffers(1, &VBO);
	GL->glGenBuffers(1, &EBO);

	GL->glBindVertexArray(VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void NODES::RENDERING::DIM_2D::Rectangle::render() {
	// Update vertices
	const vec2 v1      = d_to_f(vert_a->getData().get<dvec2>());
	const vec2 v2      = d_to_f(vert_b->getData().get<dvec2>());
	const vec2 v3      = d_to_f(vert_c->getData().get<dvec2>());
	const vec2 v4      = d_to_f(vert_d->getData().get<dvec2>());
	const vec4 u_color = d_to_f(color ->getData().get<dvec4>());

	const GLfloat vertices[8] = {
		v1.x, v1.y,
		v2.x, v2.y,
		v3.x, v3.y,
		v4.x, v4.y
	};
	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// Render
	const GLuint Shader = SESSION.viewport->SP_2D_Rectangle;
	GL->glUseProgram(Shader);
	GL->glUniform2uiv(GL->glGetUniformLocation(Shader, "uResolution"), 1, glm::value_ptr(SESSION.viewport->resolution));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(d_to_f(SESSION.viewport->center_2d)));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uZoom"), d_to_f(SESSION.viewport->zoom_2d));

	GL->glUniform4fv (GL->glGetUniformLocation(Shader, "uColor"), 1, glm::value_ptr(u_color));

	GL->glBindVertexArray(VAO);
	GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}

void NODES::RENDERING::DIM_2D::Rectangle::exec(const Port* port) {
	render();
	exec_out->exec();
}

NODES::RENDERING::DIM_2D::Circle::Circle() :
	Node("2D Circle")
{
	VAO, VBO, EBO = 0;

	header_color = QColor(75, 25, 25);
	rect.setWidth(80);
	rect.setHeight(120);

	exec_in  = new PORT::Exec_I(this, "Draw");
	exec_out = new PORT::Exec_O(this, "");

	center = new PORT::Data_I(this, "Center", VARIABLE::Type::VEC2);
	radius = new PORT::Data_I(this, "Radius", VARIABLE::Type::FLOAT);
	color  = new PORT::Data_I(this, "Color" , VARIABLE::Type::VEC4);

	center->variable = Variable(dvec2(0, 0));
	radius->variable = Variable(50.0);
	color->variable  = Variable(dvec4(1, 1, 1, 1));
	init();
}

void NODES::RENDERING::DIM_2D::Circle::init() {
	const GLfloat vertices[8] = {
		-1, -1,
		-1,  1,
		 1,  1,
		 1, -1
	};
	const GLuint indices[6] = {
		0, 1, 2,
		0, 2, 3
	};
	GL->glGenVertexArrays(1, &VAO);
	GL->glGenBuffers(1, &VBO);
	GL->glGenBuffers(1, &EBO);

	GL->glBindVertexArray(VAO);

	GL->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GL->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	GL->glEnableVertexAttribArray(0);

	GL->glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL->glBindVertexArray(0);
}

void NODES::RENDERING::DIM_2D::Circle::render() {
	const vec4 u_color  = d_to_f(color ->getData().get<dvec4>());
	const vec2 u_center = d_to_f(center->getData().get<dvec2>());
	const vec1 u_radius = d_to_f(radius->getData().get<dvec1>());

	// Render
	const GLuint Shader = SESSION.viewport->SP_2D_Circle;
	GL->glUseProgram(Shader);
	GL->glUniform2uiv(GL->glGetUniformLocation(Shader, "uResolution"), 1, glm::value_ptr(SESSION.viewport->resolution));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(d_to_f(SESSION.viewport->center_2d)));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uZoom"), d_to_f(SESSION.viewport->zoom_2d));

	GL->glUniform4fv (GL->glGetUniformLocation(Shader, "uColor" ), 1, glm::value_ptr(u_color));
	GL->glUniform2fv (GL->glGetUniformLocation(Shader, "uPosition"), 1, glm::value_ptr(u_center));
	GL->glUniform1f  (GL->glGetUniformLocation(Shader, "uRadius"), u_radius);

	GL->glBindVertexArray(VAO);
	GL->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GL->glBindVertexArray(0);
	GL->glUseProgram(0);
}

void NODES::RENDERING::DIM_2D::Circle::exec(const Port* port) {
	render();
	exec_out->exec();
}
#include "Nodes/Singleton/Background.hpp"

#include "Session.hpp"

NODES::SINGLETON::Background::Background() :
	Node(Node_Type::SINGLETON_BACKGROUND, "Background")
{
	rect.setWidth(120);
	rect.setHeight(80);

	ei_exec  = EXEC_I("");
	di_color = DATA_I("Color", Variable(Color(1,0,1,1)));

	eo_exec = EXEC_O("");
}

void NODES::SINGLETON::Background::exec(const Port* port) {
	const F32_V4 u_color = to_F32(di_color->GET_DATA(Color)->rgba());
	GL->glClearColor(u_color.r, u_color.g, u_color.b, u_color.a);
	GL->glClear(GL_COLOR_BUFFER_BIT);
	eo_exec->exec();
}
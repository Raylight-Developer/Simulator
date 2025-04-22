#include "Nodes/Singleton/Background.hpp"

#include "Session.hpp"

NODES::SINGLETON::Background::Background() :
	Node("SINGLETON::BACKGROUND", "Background")
{
	rect.setWidth(120);
	rect.setHeight(80);

	exec_in  = EXEC_I("");
	exec_out = EXEC_O("");

	color_in = DATA_I("Color", Variable(Color(1,0,1,1)));
}

void NODES::SINGLETON::Background::exec(const Port* port) {
	const F32_V4 u_color = to_F32(color_in->GET_DATA(Color).rgba());
	GL->glClearColor(u_color.r, u_color.g, u_color.b, u_color.a);
	GL->glClear(GL_COLOR_BUFFER_BIT);
	exec_out->exec();
}
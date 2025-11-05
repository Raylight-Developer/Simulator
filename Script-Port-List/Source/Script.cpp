#include "Script.hpp"

Script::Script(Session* session) : SCRIPT("Base Script", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(140);
	rect.setHeight(500);

	di_x = EXEC_O("Exec");
	
	di_a = DATA_O("F64" , VAR_TYPE::DOUBLE);
	di_b = DATA_O("I64" , VAR_TYPE::INT);
	di_c = DATA_O("Quat", VAR_TYPE::QUAT);
	di_d = DATA_O("Color", VAR_TYPE::COLOR);

	di_e = DATA_O("Vec2", VAR_TYPE::VEC2);
	di_f = DATA_O("Vec3", VAR_TYPE::VEC3);
	di_g = DATA_O("Vec4", VAR_TYPE::VEC4);
	di_h = DATA_O("Mat2", VAR_TYPE::MAT2);
	di_i = DATA_O("Mat3", VAR_TYPE::MAT3);
	di_j = DATA_O("Mat4", VAR_TYPE::MAT4);
	
	di_k = DATA_O("Bool"  , VAR_TYPE::BOOL);
	di_l = DATA_O("String", VAR_TYPE::STRING);

	LOGL(<< "Loaded Base Script");
}

void Script::onUnload() {
	LOGL(<< "Unloaded Base Script");
}

void Script::exec(const Exec_I* port) {
	execAllDownstream();
}

Ptr_S<Variable>Script::getData(const Data_O* port) {
	return make_shared<Variable>();
}
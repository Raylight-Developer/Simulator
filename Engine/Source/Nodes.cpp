#include "Nodes.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"
#include "Viewport.hpp"

void Node::save(CORE::Lace& lace, const U64& index) const {
	lace NL << "┌Node [ " << index << " ] " << label;
	lace++;
	lace NL PTR(shared_from_this().get());
	lace NL << "Type " << NODES::toString(node_type);
	lace NL << "( " << pos() << " )";
	lace NL << "┌In( " << inputs.size() << " )";
	lace++;
	for (Port* port : inputs) {
		lace NL PTR(port);
	}
	lace--;
	lace NL << "└In";
	lace NL << "┌Out( " << outputs.size() << " )";
	lace++;
	for (Port* port : outputs) {
		lace NL PTR(port);
	}
	lace--;
	lace NL << "└Out";

	lace NL << "┌Data";
	lace++;
	saveDetail(lace);
	lace--;
	lace NL << "└Data";

	lace--;
	lace NL << "└Node";
}

void Node::load(File* file, const Token_Array& tokens) {
	const string  r_label = f_join(tokens[0], 4);
	const U64     r_ptr   = stoU64(tokens[1][1]);
	const string  r_type  = tokens[2][1];
	const QPointF r_pos   = QPointF(stoF64(tokens[3][1]), stoF64(tokens[3][2]));

	const NODES::Node_Type r_node_type  = NODES::toEnum(r_type);

	Ptr_S<Node> node = NODES::node_get_map.at(r_node_type)();

	if (node == nullptr and r_node_type == NODES::Node_Type::SCRIPT) {
		Token_Array detail_data = File::getBlock("┌Data", "└Data", tokens);
		const string script_path = f_join(detail_data[0]);

		node = Ptr_S<NODES::SCRIPT::Script>(NODES::SCRIPT::loadScript(qstr(script_path)));
	}

	if (node) {
		node->label = qstr(r_label);

		SESSION->window->node_editor->scene->addItem(node.get());
		node->setPos(r_pos);

		file->pointer_map.set(r_ptr, to_U(node.get()));
		file->nodes.push(node);

		Token_Array inputs  = File::getBlock("┌In(" , "└In" , tokens);
		Token_Array outputs = File::getBlock("┌Out(", "└Out", tokens);

		for (U64 i = 0; i < inputs.size(); i++) {
			file->pointer_map.set(stoU64(inputs[i][1]), to_U(node->inputs[i]));
		}
		for (U64 i = 0; i < outputs.size(); i++) {
			file->pointer_map.set(stoU64(outputs[i][1]), to_U(node->outputs[i]));
		}

		Token_Array detail_data = File::getBlock("┌Data", "└Data", tokens);
		node->loadDetail(detail_data);
	}
}

string NODES::toString(const Node_Type& value) {
	for (auto& [e, name] : enum_str_map) {
		if (e == value) {
			return string(name);
		}
	}
	return "NONE";
}

NODES::Node_Type NODES::toEnum(const string_view& name) {
	for (auto& [e, str] : enum_str_map) {
		if (str == name) {
			return e;
		}
	}
	return Node_Type::NONE;
}
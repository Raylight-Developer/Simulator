#include "File.hpp"

#include "Session.hpp"

#define NULL_REF "*NULL"

File::File() :
	background_shader("")
{}

File::~File() {
}

U64 File::ptrVal(const void* key) const {
	return pointer_map.getVal(to_U(key));
}

U64 File::ptrKey(const void* val) const {
	return pointer_map.getKey(to_U(val));
}

void File::loadNewFile(const string& file_path) {
	SESSION->window->variable_editor->list->clear();
	SESSION->window->node_editor->selection.clear();

	SESSION->history.group_undo_stack.clear();
	SESSION->history.group_redo_stack.clear();
	SESSION->history.redo_stack.clear();
	SESSION->history.undo_stack.clear();

	pointer_map.clear();

	euler_tick.reset();
	init.reset();

	variables.clear();
	variable_refs.clear();

	NODES::SCRIPT::unloadScripts();

	node_singletons.clear();
	nodes.clear();

	loadFile(file_path);
	for (auto& [k, f] : SIM_HOOK.onInit) {
		f();
	}
	if (FILE.init) {
		FILE.init->exec();
	}
}

void File::loadFile(const string& file_path) {
	this->file_path = file_path;
	LOGL(<< MSG_BLUE("[File]") >> "Loading ASCII File from:" >> file_path);
	LOG++;
	ifstream in_file(file_path, ios::binary);

	if (!in_file.is_open()) {
		LOGL(<< MSG_RED("[File]") >> "Error Opening File");
	}
	else {

		Token_Array token_data;
		Tokens line_data;
		string line;
		while (getline(in_file, line)) {
			token_data.push_back(f_split(line));
			line_data.push_back(line);
		}
		in_file.close();
		LOGL(<< MSG_GREEN("[File]") >> "Parsing...");
		load(token_data, line_data);
	}
	LOGL(<< MSG_GREEN("[File]") >> "Loaded");
	LOG--;
}

bool File::saveFile(const string& file_path) {
	CORE::Lace lace;
	save(lace);
	return writeToFile(file_path, lace.str());
}

void File::load(const Token_Array& token_data, const Tokens& line_data) {
	LOG++;

	const unordered_map<string, function<void(const Token_Array&, const Tokens&)>> actions = {
		{"└Header"       , [this](const Token_Array& tokens, const Tokens& line_data) { loadHeader    (tokens, line_data); }},
		{"└Scripts"      , [this](const Token_Array& tokens, const Tokens& line_data) { loadScripts   (tokens, line_data); }},
		{"└Variables"    , [this](const Token_Array& tokens, const Tokens& line_data) { loadVariables (tokens, line_data); }},
		{"└Node-Groups"  , [this](const Token_Array& tokens, const Tokens& line_data) { loadNodeGroups(tokens, line_data); }},
		{"└Node-Tree"    , [this](const Token_Array& tokens, const Tokens& line_data) { loadNodeTree  (tokens, line_data); }},
		{"└Build"        , [this](const Token_Array& tokens, const Tokens& line_data) { loadBuild     (tokens, line_data); }},
		{"└Background**" , [this](const Token_Array& tokens, const Tokens& line_data) { loadBackground(tokens, line_data); }}
	};

	Token_Array block_buffer;
	Tokens block_lines;
	for (U64 i = 0; i < token_data.size(); i++) {
		const Tokens& tokens = token_data[i];

		block_buffer.push_back(tokens);
		block_lines.push_back(line_data[i]);
		if (!tokens.empty()) {
			const auto it = actions.find(tokens[0]);
			if (it != actions.end()) {
				it->second(block_buffer, block_lines);
				block_buffer.clear();
				block_lines.clear();
			}
		}
	}
	LOG--;
}

void File::loadHeader(const Token_Array& token_data, const Tokens& line_data) {
	LOGL(<< MSG_BLUE("[Header]"));
	LOG++;
	for (const Tokens& tokens : token_data) {
		if (tokens[0] == "Version") {
			Tokens version = f_split(tokens[1], ".");
			const U16 file_major_version = stoU16(version[0]);
			const U16 file_minor_version = stoU16(version[1]);
			const U16 file_patch_version = stoU16(version[2]);
			if (SESSION->major_version != file_major_version or SESSION->minor_version != file_minor_version or SESSION->patch_version != file_patch_version) {
				LOGL(<< WARNING << "Version Mismatch: SYSTEM [" <<
					SESSION->major_version << "." <<
					SESSION->minor_version << "." <<
					SESSION->patch_version << "] FILE [" <<
					file_major_version << "." <<
					file_minor_version << "." <<
					file_patch_version << "]"
				);
			}


			LOGL(<< "Version:" >> tokens[1]);
		}
	}
	LOG--;
}

void File::loadScripts(const Token_Array& token_data, const Tokens& line_data) {
	LOGL(<< MSG_BLUE("[Scripts]"));
	LOG++;
	LOG--;
}

void File::loadVariables(const Token_Array& token_data, const Tokens& line_data) {
	LOGL(<< MSG_BLUE("[Variables]"));
	LOG++;
	const CORE::Stack<Token_Array> var_data = getBlocks("┌Variable", "└Variable", token_data, false);
	for (const Token_Array& data : var_data) {
		const QString var_name = qstr(f_join(data[0]));
		variables[var_name] = make_shared<Variable>(Variable::load(data[1]));
		SESSION->window->variable_editor->list->addItem(var_name);
	}
	LOG--;
}

void File::loadNodeGroups(const Token_Array& token_data, const Tokens& line_data) {
	LOGL(<< MSG_BLUE("[Node-Groups]"));
	LOG++;
	LOG--;
}

void File::loadNodeTree(const Token_Array& token_data, const Tokens& line_data) {
	LOGL(<< MSG_BLUE("[Node-Tree]"));
	LOG++;
	const CORE::Stack<Token_Array> node_data = getBlocks("┌Node", "└Node", token_data, true);
	for (const Token_Array& data : node_data) {
		Node::load(this, data);
	}
	LOG--;
}

void File::loadBuild(const Token_Array& token_data, const Tokens& line_data) {
	LOGL(<< MSG_BLUE("[Build]"));
	LOG++;

	{
		const CORE::Stack<Token_Array> connection_data = getBlocks("┌Node-Exec", "└Node-Exec", token_data, false);
		for (const Token_Array& data : connection_data) {
			for (const Tokens& conn : data) {
				auto data_o = reinterpret_cast<NODE::PORT::Exec_O*>(pointer_map.getVal(stoU64(conn[1])));
				auto data_i = reinterpret_cast<NODE::PORT::Exec_I*>(pointer_map.getVal(stoU64(conn[4])));
				data_o->connect(data_i);
			}
		}
	}

	{
		const CORE::Stack<Token_Array> connection_data = getBlocks("┌Node-Data", "└Node-Data", token_data, false);
		for (const Token_Array& data : connection_data) {
			for (const Tokens& conn : data) {
				auto data_o = reinterpret_cast<NODE::PORT::Data_O*>(pointer_map.getVal(stoU64(conn[1])));
				auto data_i = reinterpret_cast<NODE::PORT::Data_I*>(pointer_map.getVal(stoU64(conn[4])));
				data_i->connect(data_o);
			}
		}
	}

	LOG--;
}

void File::loadBackground(const Token_Array& token_data, const Tokens& line_data) {
	LOGL(<< MSG_BLUE("[Node-Tree]"));
	LOG++;

	background_shader = f_join(line_data, "\n", 1, 1);
	if (GL) {
		const auto confirm = OpenGL::compileFragShaderFromStr("./Shaders/Screen.vert", background_shader);
		if (background_shader != "" && confirm) {
			if (SESSION->viewport->gl_data["BG Shader"] != 0) {
				GL->glDeleteProgram(SESSION->viewport->gl_data["BG Shader"]);
			}
			SESSION->viewport->gl_data["BG Shader"] = confirm.data;
		}
		else {
			if (SESSION->viewport->gl_data["BG Shader"] != 0) {
				GL->glDeleteProgram(SESSION->viewport->gl_data["BG Shader"]);
			}
			const auto confirm = OpenGL::compileFragShader("./Shaders/Screen.vert", "./Shaders/Background.frag");
			if (confirm) {
				SESSION->viewport->gl_data["BG Shader"] = confirm.data;
			}
		}
	}

	LOG--;
}

void File::save(CORE::Lace& lace) {
	saveHeader(lace);
	saveScripts(lace);
	saveVariables(lace);
	saveNodeGroups(lace);
	saveNodeTree(lace);
	saveBuild(lace);
	saveBackground(lace);
}

void File::saveHeader(CORE::Lace& lace) {
	lace << "┌Header";
	lace++;
	lace NL << "Version" >> SESSION->major_version << "." << SESSION->minor_version << "." << SESSION->patch_version;
	lace--;
	lace NL << "└Header";
}

void File::saveScripts(CORE::Lace& lace) {
	lace NL << "┌Scripts( " << scripts.size() << " )";
	lace++;
	U64 i = 0;
	for (const auto script : scripts) {
		lace NL << "┌Script [ " << i << " ]";
		lace++;
		lace NL PTR(script);
		lace--;
		lace NL << "└Script";
		i++;
	}
	lace--;
	lace NL << "└Scripts";
}

void File::saveVariables(CORE::Lace& lace) {
	lace NL << "┌Variables( " << variables.size() << " )";
	lace++;
	U64 i = 0;
	for (const auto& [var_name, var] : variables) {
		lace NL << "┌Variable [ " << i << " ]";
		lace++;
		lace NL << var_name;
		lace NL;
		var->save(lace);
		lace--;
		lace NL << "└Variable";
		i++;
	}
	lace--;
	lace NL << "└Variables";
}

void File::saveNodeGroups(CORE::Lace& lace) {
	lace NL << "┌Node-Groups( 0 )";
	lace++;

	lace--;
	lace NL << "└Node-Groups";
}

void File::saveNodeTree(CORE::Lace& lace) {
	lace NL << "┌Node-Tree( " << nodes.size() << " )";
	lace++;
	U64 index = 0;
	for (const Ptr_S<Node>& node : nodes) {
		node->save(lace, index);
		index++;
	}
	lace--;
	lace NL << "└Node-Tree";
}

void File::saveBuild(CORE::Lace& lace) {
	lace NL << "┌Build";
	lace++;
	lace NL << "┌Node-Data";
	lace++;
	for (const Ptr_S<Node>& node : nodes) {
		for (Port* port : node->inputs) {
			if (port->connected()) {
				if (port->type() == Graphics_Item_Type::E_DATA_I) {
					auto d_port = static_cast<NODE::PORT::Data_I*>(port);
					lace NL PTR(d_port->connection->getDataO()) << " - " PTR(port);
				}
			}
		}
	}
	lace--;
	lace NL << "└Node-Data";
	lace NL << "┌Node-Exec";
	lace++;
	for (const Ptr_S<Node>& node : nodes) {
		for (Port* port : node->outputs) {
			if (port->connected()) {
				if (port->type() == Graphics_Item_Type::E_EXEC_O) {
					auto d_port = static_cast<NODE::PORT::Exec_O*>(port);
					lace NL PTR(port) << " - " PTR(d_port->connection->getExecI());
				}
			}
		}
	}
	lace--;
	lace NL << "└Node-Exec";
	lace--;
	lace NL << "└Build";
}

void File::saveBackground(CORE::Lace& lace) {
	lace NL << "┌Background**";
	lace NL << background_shader;
	lace NL << "└Background**";
}

Token_Array File::getBlock(const string& open, const string& close, const Token_Array& tokens, const bool& include_open_close) {
	Token_Array block;
	bool is_processing = false;
	for (const Tokens& tokens : tokens) {
		if (tokens[0] == open) {
			is_processing = true;
			if (include_open_close) {
				block.push_back(tokens);
			}
		}
		else if (tokens[0] == close) {
			if (include_open_close) {
				block.push_back(tokens);
			}
			return block;
		}
		else if (is_processing) {
			block.push_back(tokens);
		}
	}
	return block;
}

CORE::Stack<Token_Array> File::getBlocks(const string& open, const string& close, const Token_Array& tokens, const bool& include_open_close) {
	bool is_processing = false;
	CORE::Stack<Token_Array> blocks;
	Token_Array buffer;
	for (const Tokens& tokens : tokens) {
		if (tokens[0] == open) {
			is_processing = true;
			if (include_open_close) {
				buffer.push_back(tokens);
			}
		}
		else if (tokens[0] == close) {
			is_processing = false;
			if (include_open_close) {
				buffer.push_back(tokens);
			}
			blocks.push(buffer);
			buffer.clear();
		}
		else if (is_processing) {
			buffer.push_back(tokens);
		}
	}
	return blocks;
}
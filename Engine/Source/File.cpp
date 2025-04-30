#include "File.hpp"

#include "Session.hpp"

#define NULL_REF "*NULL"

File::File() {}

File::~File() {
}

U64 File::ptrVal(const void* key) const {
	return pointer_map.getVal(to_U(key));
}

U64 File::ptrKey(const void* val) const {
	return pointer_map.getKey(to_U(val));
}

void File::loadFile(const string& file_path) {
	LOGL(<< MSG_BLUE("[File]") >> "Loading ASCII File from:" >> file_path);
	LOG++;
	ifstream in_file(file_path, ios::binary);

	if (!in_file.is_open()) {
		LOGL(<< MSG_RED("[File]") >> "Error Opening File");
	}
	else {

		Token_Array token_data;
		string line;
		while (getline(in_file, line)) {
			Tokens tokens = f_split(line);
			if (!tokens.empty()) {
				token_data.push_back(tokens);
			}
		}
		in_file.close();
		LOGL(<< MSG_GREEN("[File]") >> "Parsing...");
		load(token_data);
	}
	LOGL(<< MSG_GREEN("[File]") >> "Loaded");
	LOG--;
}

bool File::saveFile(const string& file_path) {
	CORE::Lace lace;
	save(lace);
	return writeToFile(file_path, lace.str());
}

void File::load(const Token_Array& token_data) {
	LOG++;

	const unordered_map<string, function<void(const Token_Array&)>> actions = {
		{"└Header"     , [this](const Token_Array& tokens) { loadHeader    (tokens); }},
		{"└Scripts"    , [this](const Token_Array& tokens) { loadScripts   (tokens); }},
		{"└Variables"  , [this](const Token_Array& tokens) { loadVariables (tokens); }},
		{"└Node-Groups", [this](const Token_Array& tokens) { loadNodeGroups(tokens); }},
		{"└Node-Tree"  , [this](const Token_Array& tokens) { loadNodeTree  (tokens); }},
		{"└Build"      , [this](const Token_Array& tokens) { loadBuild     (tokens); }}
	};

	Token_Array block_buffer;
	for (U64 i = 0; i < token_data.size(); i++) {
		const Tokens& tokens = token_data[i];

		block_buffer.push_back(tokens);

		const auto it = actions.find(tokens[0]);
		if (it != actions.end()) {
			it->second(block_buffer);
			block_buffer.clear();
		}
	}
	LOG--;
}

void File::loadHeader(const Token_Array& token_data) {
	LOGL(<< MSG_BLUE("[Header]"));
	LOG++;
	for (const Tokens& tokens : token_data) {
		if (tokens[0] == "Version") {
			Tokens version = f_split(tokens[1], ".");
			const U16 file_major_version = stoU16(version[0]);
			const U16 file_minor_version = stoU16(version[1]);
			const U16 file_patch_version = stoU16(version[2]);
			if (SESSION->major_version != file_major_version or SESSION->minor_version != file_minor_version or SESSION->patch_version != file_patch_version) {
				LOGL(<< WARNING("Version Mismatch: SYSTEM [" <<
					SESSION->major_version << "." <<
					SESSION->minor_version << "." <<
					SESSION->patch_version << "] FILE [" <<
					file_major_version << "." <<
					file_minor_version << "." <<
					file_patch_version << "]"
				));
			}


			LOGL(<< "Version:" >> tokens[1]);
		}
	}
	LOG--;
}

void File::loadScripts(const Token_Array& token_data) {
	LOGL(<< MSG_BLUE("[Scripts]"));
	LOG++;
	LOG--;
}

void File::loadVariables(const Token_Array& token_data) {
	LOGL(<< MSG_BLUE("[Variables]"));
	LOG++;
	LOG--;
}

void File::loadNodeGroups(const Token_Array& token_data) {
	LOGL(<< MSG_BLUE("[Node-Groups]"));
	LOG++;
	LOG--;
}

void File::loadNodeTree(const Token_Array& token_data) {
	LOGL(<< MSG_BLUE("[Node-Tree]"));
	LOG++;
	const CORE::Stack<Token_Array> node_data = getBlocks("┌Node", "└Node", token_data, true);
	for (const Token_Array& data : node_data) {
		Node::load(this,data);
	}
	LOG--;
}

void File::loadBuild(const Token_Array& token_data) {
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

void File::save(CORE::Lace& lace) {
	saveHeader(lace);
	saveScripts(lace);
	saveVariables(lace);
	saveNodeGroups(lace);
	saveNodeTree(lace);
	saveBuild(lace);
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

	lace--;
	lace NL << "└Scripts";
}

void File::saveVariables(CORE::Lace& lace) {
	lace NL << "┌Variables( " << variables.size() << " )";
	lace++;

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
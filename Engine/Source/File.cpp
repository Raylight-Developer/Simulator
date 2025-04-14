#include "File.hpp"

#include "Session.hpp"

#define NULL_REF "*NULL"

File::File() {
	euler_tick = make_shared<NODES::SINGLETON::Euler_Tick>();
	nodes.push(euler_tick);
}

File::~File() {
}

U64 File::ptrVal(const void* key) const {
	return pointer_map.getVal(to_U(key));
}

U64 File::ptrKey(const void* val) const {
	return pointer_map.getKey(to_U(val));
}

File File::loadFile(const string& file_path) {
	File file;
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
		file.load(token_data);
	}
	LOGL(<< MSG_GREEN("[File]") >> "Loaded");
	LOG--;
	return file;
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
		{"└Variables"  , [this](const Token_Array& tokens) { loadVariables (tokens); }},
		{"└Node-Groups", [this](const Token_Array& tokens) { loadNodeGroups(tokens); }},
		{"└Node-Tree"  , [this](const Token_Array& tokens) { loadNodeTree  (tokens); }},
		{"└Build"      , [this](const Token_Array& tokens) { loadBuild     (tokens); }},
		{"└Scripts"    , [this](const Token_Array& tokens) { loadScripts   (tokens); }}
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
	LOG--;
}

void File::loadBuild(const Token_Array& token_data) {
	LOGL(<< MSG_BLUE("[Build]"));
	LOG++;
	LOG--;
}

void File::loadScripts(const Token_Array& token_data) {
	LOGL(<< MSG_BLUE("[Scripts]"));
	LOG++;
	LOG--;
}

void File::save(CORE::Lace& lace) {
	saveHeader(lace);
	saveBuild(lace);
}

void File::saveHeader(CORE::Lace& lace) {
	lace << "┌Header";
	lace++;
	lace NL << "Version" >> SESSION->major_version << "." << SESSION->minor_version << "." << SESSION->patch_version;
	lace--;
	lace NL << "└Header";
}

void File::saveBuild(CORE::Lace& lace) {
	lace NL << "┌Build";
	lace++;
	lace--;
	lace NL << "└Build";
}
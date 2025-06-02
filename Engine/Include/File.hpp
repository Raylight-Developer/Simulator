#pragma once

#include "KL.hpp"

#include "Nodes.hpp"
#include "Variable.hpp"
#include "Scripting.hpp"

struct File {
	CORE::BiMap<U64, U64> pointer_map;

	Ptr_S<NODES::SINGLETON::Euler_Tick> euler_tick;
	Ptr_S<NODES::SINGLETON::Init> init;
	
	CORE::Stack<Ptr_S<Node>> nodes;
	CORE::Stack<Ptr_S<Node>> node_singletons;

	CORE::UMap<QString, Ptr_S<Variable>> variables;
	CORE::UMap<QString, CORE::Stack<Ptr_S<Node>>> variable_refs;

	CORE::Stack<NODES::SCRIPT::Script*> scripts;
	CORE::UMap<NODES::SCRIPT::Script*, HINSTANCE> dlls;

	string background_shader;
	string file_path;

	File();
	~File();

	U64 ptrVal(const void* key) const;
	U64 ptrKey(const void* val) const;

	void loadNewFile(const string& file_path);
	void loadFile(const string& file_path);
	bool saveFile(const string& file_path);

	void load          (const Token_Array& token_data);
	void loadHeader    (const Token_Array& token_data);
	void loadScripts   (const Token_Array& token_data);
	void loadVariables (const Token_Array& token_data);
	void loadNodeGroups(const Token_Array& token_data);
	void loadNodeTree  (const Token_Array& token_data);
	void loadBuild     (const Token_Array& token_data);
	void loadBackground(const Token_Array& token_data);

	void save          (CORE::Lace& lace);
	void saveHeader    (CORE::Lace& lace);
	void saveScripts   (CORE::Lace& lace);
	void saveVariables (CORE::Lace& lace);
	void saveNodeGroups(CORE::Lace& lace);
	void saveNodeTree  (CORE::Lace& lace);
	void saveBuild     (CORE::Lace& lace);
	void saveBackground(CORE::Lace& lace);

	static Token_Array getBlock(const string& open, const string& close, const Token_Array& tokens, const bool& include_open_close = false);
	static CORE::Stack<Token_Array> getBlocks(const string& open, const string& close, const Token_Array& tokens, const bool& include_open_close = false);
};
#pragma once

#include "KL.hpp"

#include "Nodes.hpp"

struct File {
	CORE::BiMap<U64, U64> pointer_map;

	Ptr_S<NODES::SINGLETON::Euler_Tick> euler_tick;
	Ptr_S<NODES::SINGLETON::Reset> reset;
	
	CORE::Stack<Ptr_S<Node>> nodes;

	File();
	~File();

	U64 ptrVal(const void* key) const;
	U64 ptrKey(const void* val) const;

	static File loadFile(const string& file_path);
	bool        saveFile(const string& file_path);

	void load          (const Token_Array& token_data);
	void loadHeader    (const Token_Array& token_data);
	void loadVariables (const Token_Array& token_data);
	void loadNodeGroups(const Token_Array& token_data);
	void loadNodeTree  (const Token_Array& token_data);
	void loadBuild     (const Token_Array& token_data);
	void loadScripts   (const Token_Array& token_data);

	void save      (CORE::Lace& lace);
	void saveHeader(CORE::Lace& lace);
	void saveBuild (CORE::Lace& lace);
};
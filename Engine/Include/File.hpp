#pragma once

#include "KL.hpp"

#include "Nodes.hpp"

struct File {
	U16 major_version, minor_version, patch_version;
	KL::BiMap<U64, U64> pointer_map;

	NODES::SINGLETON::Euler_Tick* euler_tick;
	
	KL::Stack<Node*> nodes;

	File();
	~File();

	U64 ptrVal(const void* key) const;
	U64 ptrKey(const void* val) const;

	static File loadFile(const string& file_path);
	bool        saveFile(const string& file_path);

	void load      (const Token_Array& token_data);
	void loadHeader(const Token_Array& token_data);
	void loadBuild (const Token_Array& token_data);

	void save      (KL::Lace& lace);
	void saveHeader(KL::Lace& lace);
	void saveBuild (KL::Lace& lace);
};
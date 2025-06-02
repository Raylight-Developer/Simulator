#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

namespace VAR {
	enum struct Type;
}
struct Variable;

namespace VAR {
	enum struct Type {
		NONE,
		DOUBLE, INT,
		BOOL, STRING,
		VEC2, VEC3, VEC4, COLOR, QUAT, MAT2, MAT3, MAT4
		//TRANSFORM_2D, TRANSFORM_3D
	};
	enum struct Container {
		NONE, LIST
	};
	QColor toColor(const VAR::Type& type);
}

#define VAR_TYPE VAR::Type
#define VAR_CONTAINER VAR::Container

struct Variable {
	any data;
	VAR::Type type;
	VAR::Container container;

	Variable();

	Variable(const F64&      data);
	Variable(const I64&      data);
	Variable(const bool&     data);
	Variable(const QString&  data);
	Variable(const F64_V2&   data);
	Variable(const F64_V3&   data);
	Variable(const F64_V4&   data);
	Variable(const Color&    data);
	Variable(const F64_Quat& data);
	Variable(const F64_M2&   data);
	Variable(const F64_M3&   data);
	Variable(const F64_M4&   data);

	Variable(const vector<F64>&      data);
	Variable(const vector<I64>&      data);
	Variable(const vector<bool>&     data);
	Variable(const vector<QString>&  data);
	Variable(const vector<F64_V2>&   data);
	Variable(const vector<F64_V3>&   data);
	Variable(const vector<F64_V4>&   data);
	Variable(const vector<Color>&    data);
	Variable(const vector<F64_Quat>& data);
	Variable(const vector<F64_M2>&   data);
	Variable(const vector<F64_M3>&   data);
	Variable(const vector<F64_M4>&   data);

	Variable(const VAR::Type& type, const VAR::Container& container = VAR::Container::NONE);

	void save(CORE::Lace& lace) const;
	static Variable load(const Tokens& tokens);

	bool empty() const;

	Variable listAtIndex(const U64& index);
	void listClear();
	void listCreate(const U64& size, const Variable& value);
	void listInsert(const U64& index, const Variable& value);
	void listModify(const U64& index, const Variable& value);
	void listRemove(const U64& index);
	void listPush(const Variable& value);
	U64 listSize() const;

	QString str() const;
	string getSingleVar() const;

	template <typename T>
	inline T* get() {
		return any_cast<T>(&data);
	}
};

namespace VAR {
	static const vector<pair<VAR::Type, string_view>> type_enum_str_map {{
		{ VAR::Type::NONE   , "NONE"   },
		{ VAR::Type::DOUBLE , "DOUBLE" },
		{ VAR::Type::INT    , "INT"    },
		{ VAR::Type::BOOL   , "BOOL"   },
		{ VAR::Type::STRING , "STRING" },
		{ VAR::Type::VEC2   , "VEC2"   },
		{ VAR::Type::VEC3   , "VEC3"   },
		{ VAR::Type::VEC4   , "VEC4"   },
		{ VAR::Type::COLOR  , "COLOR"  },
		{ VAR::Type::QUAT   , "QUAT"   },
		{ VAR::Type::MAT2   , "MAT2"   },
		{ VAR::Type::MAT3   , "MAT3"   },
		{ VAR::Type::MAT4   , "MAT4"   }
	}};

	string toString(const VAR::Type& value);
	VAR::Type toType(const string_view& name);

	static const vector<pair<VAR::Container, string_view>> container_enum_str_map {{
		{ VAR::Container::NONE , "NONE" },
		{ VAR::Container::LIST , "LIST" }
	}};

	string toString(const VAR::Container& value);
	VAR::Container toContainer(const string_view& name);
}
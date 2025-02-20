#include "Variable.hpp"

Variable::Variable() :
	data(nullptr),
	type(VARIABLE::Type::NONE),
	modifier(VARIABLE::Modifier::SINGLE)
{}

Variable::Variable(const any& data, const VARIABLE::Type& type, const VARIABLE::Modifier& modifier) :
	data(data),
	type(type),
	modifier(modifier)
{}

Variable::Variable(const string& data) : data(data) {
	modifier = VARIABLE::Modifier::SINGLE; type = VARIABLE::Type::STRING;
}
Variable::Variable(const dvec1& data) : data(data) {
	modifier = VARIABLE::Modifier::SINGLE; type = VARIABLE::Type::DOUBLE;
}
Variable::Variable(const bool& data) : data(data) {
	modifier = VARIABLE::Modifier::SINGLE; type = VARIABLE::Type::BOOL;
}
Variable::Variable(const uint64& data) : data(data) {
	modifier = VARIABLE::Modifier::SINGLE; type = VARIABLE::Type::UINT;
}
Variable::Variable(const int64& data) : data(data) {
	modifier = VARIABLE::Modifier::SINGLE; type = VARIABLE::Type::INT;
}
Variable::Variable(vector<dvec1> data) : data(data) {
	modifier = VARIABLE::Modifier::VECTOR; type = VARIABLE::Type::DOUBLE;
}

Variable Variable::operator+(const Variable & other) const {
	if (type == other.type) {
		switch (type) {
		case VARIABLE::Type::DOUBLE: return Variable(getDouble() + other.getDouble(), type);
		}
	}
	switch (type) {
	case VARIABLE::Type::DOUBLE: {
		switch (other.type) {
		case VARIABLE::Type::INT: {
			return Variable(getDouble() + other.getInt(), type);
		}
		case VARIABLE::Type::UINT: {
			return Variable(getDouble() + other.getUint(), type);
		}
		}
	}
	}
	return Variable();
}
Variable Variable::operator-(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
		case VARIABLE::Type::DOUBLE: return Variable(getDouble() - other.getDouble(), type);
		}
	}
	return Variable();
}

Variable Variable::operator*(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
		case VARIABLE::Type::DOUBLE: return Variable(getDouble() * other.getDouble(), type);
		}
	}
	return Variable();
}

Variable Variable::operator/(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
		case VARIABLE::Type::DOUBLE: return Variable(getDouble() / other.getDouble(), type);
		}
	}
	return Variable();
}

Variable Variable::pow(const Variable& other) const {
	if (type == other.type) {
		switch (type) {
		case VARIABLE::Type::DOUBLE: return Variable(std::pow(getDouble(), other.getDouble()), type);
		}
	}
	return Variable();
}

int64 Variable::getInt() const {
	return any_cast<int64>(data);
}

uint64 Variable::getUint() const {
	return any_cast<uint64>(data);
}

dvec1 Variable::getDouble() const {
	switch (type) {
	case VARIABLE::Type::DOUBLE: return any_cast<dvec1>(data);
	case VARIABLE::Type::UINT: return static_cast<dvec1>(any_cast<uint64>(data));
	case VARIABLE::Type::INT: return static_cast<dvec1>(any_cast<int64>(data));
	}
	return 0.0;
}

string Variable::getStr() const {
	return any_cast<string>(data);
}

vector<dvec1> Variable::getDoubleVector() const {
	return any_cast<vector<dvec1>>(data);
}

string Variable::to_string() const {
	switch (type) {
	case VARIABLE::Type::DOUBLE:    return std::to_string(any_cast<dvec1>(data));
	case VARIABLE::Type::UINT:      return std::to_string(static_cast<dvec1>(any_cast<uint64>(data)));
	case VARIABLE::Type::INT:       return std::to_string(static_cast<dvec1>(any_cast<int64>(data)));
	}
	return "";
}
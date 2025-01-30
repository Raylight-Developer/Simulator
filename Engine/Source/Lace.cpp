#include "Lace.hpp"

CORE::Lace::Lace() :
	character(" ")
{
	data = stringstream();
	current_tab = 0;
}

CORE::Lace::Lace(const string& character) :
	character(character)
{
	data = stringstream();
	current_tab = 0;
}

CORE::Lace& CORE::Lace::operator<<(const CORE::Lace_S& val) {
	uint16 count = val.count;
	while (count--)
		data << " ";
	return *this;
}

CORE::Lace& CORE::Lace::operator<<(const CORE::Lace_NL& val) {
	uint16 count = val.count;
	uint16 tabs = current_tab;
	while (count--)
		data << "\n";
	if (val.count)
		while (tabs--)
			data << character;
	return *this;
}

CORE::Lace& CORE::Lace::operator<<(const CORE::Lace_TAB& val) {
	uint16 count = current_tab + val.count;
	while (count--)
		data << "\t";
	return *this;
}

CORE::Lace& CORE::Lace::operator<<(const CORE::Lace_CHR& val) {
	uint16 count = val.count;
	while (count--)
		data << character;
	return *this;
}

CORE::Lace& CORE::Lace::operator<<(const CORE::Lace_DEL& val) {
	const string temp_data = data.str();
	data.clear();
	if (val.count < temp_data.size())
		data << temp_data.substr(val.count);
	return *this;
}

CORE::Lace& CORE::Lace::operator<<(const CORE::Lace_POP& val) {
	const string temp_data = data.str();
	data.clear();
	if (val.count < temp_data.size())
		data << temp_data.substr(0, temp_data.size() - 1 - val.count);
	return *this;
}

CORE::Lace& CORE::Lace::operator<<(const CORE::Lace& value) {
	data << value.data.str();
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const CORE::Lace& value) {
	data << " " << value.data.str();
	return *this;
}

CORE::Lace&  CORE::Lace::operator+=(const uint16& value) {
	current_tab += value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator-=(const uint16& value) {
	current_tab -= value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator++(int) {
	current_tab++;
	return *this;
}

CORE::Lace&  CORE::Lace::operator--(int) {
	current_tab--;
	return *this;
}

CORE::Lace& CORE::Lace::clear() {
	data = stringstream();
	current_tab = 0;
	return *this;
}

string CORE::Lace::str() const {
	return data.str();
}

CORE::Lace&  CORE::Lace::operator<< (const stringstream& value) {
	data << value.str();
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const bool& value) {
	if (value == true) data << "true";
	else data << "false";
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const string& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const char* value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const int8& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const int16& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const int32& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const int64& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const uint8& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const uint16& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const uint32& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<< (const uint64& value) {
	data << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>> (const bool& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>> (const char* value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const float& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const double& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const int8& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const int16& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const int32& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const int64& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const uint8& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const uint16& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const uint32& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator>>(const uint64& value) {
	data << " " << value;
	return *this;
}

CORE::Lace&  CORE::Lace::operator<<(const vector<string>& value) {
	for (string val : value)
		data << val << " ";
	return *this;
}

template<>
string CORE::f_readBinary<string>(const vector<std::byte>& data, const uint64& start, const uint64& size) {
	return string(reinterpret_cast<const char*>(&data[start]), size);
}

template<>
vector<Byte> CORE::f_toBinary<string>(const string& value) {
	vector<Byte> byteVector;
	byteVector.reserve(value.size());
	for (char ch : value) {
		byteVector.push_back(static_cast<Byte>(ch));
	}
	return byteVector;
}

CORE::Bin_Lace::Bin_Lace() {
	internal_data = {};
}

CORE::Bin_Lace& CORE::Bin_Lace::operator<<(const CORE::Bin_Lace& value) {
	internal_data.reserve(value.internal_data.size() + internal_data.size());
	internal_data.insert(internal_data.end(), value.internal_data.begin(), value.internal_data.end());
	return *this;
}

const char* CORE::Bin_Lace::data() const {
	return reinterpret_cast<const char*>(internal_data.data());
}

uint64 CORE::Bin_Lace::size() const {
	return internal_data.size();
}
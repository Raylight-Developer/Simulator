#pragma once

#include "Include.hpp"

// FWD DECL OTHER

// FWD DECL THIS
namespace CORE {
	class Lace;
	class Bin_Lace;

	class Lace_S;
	class Lace_NL;
	class Lace_TAB;
	class Lace_CHR;
	class Lace_DEL;
	class Lace_POP;
}

// DECL
namespace CORE {
	class Lace_S { //------------Add Space(s) to Lace------------
		friend class Lace;
		uint16 count;
	public:
		Lace_S(const uint16& count = 1) : count(count) {};
	};

	class Lace_NL { //------------Add New Line(s) and/or Global Tab To Lace------------
		friend class Lace;
		uint16 count;
		bool use_global_tabs;
	public:
		Lace_NL(const uint16& count = 1, const bool& use_global_tabs = true) : count(count), use_global_tabs(use_global_tabs) {}
	};

	class Lace_TAB { //------------Add Tab(s) to Lace------------
		friend class Lace;
		uint16 count;
	public:
		Lace_TAB(const uint16& count = 1) : count(count) {}
	};

	class Lace_CHR { //------------Add Char(s) to Lace------------
		friend class Lace;
		uint16 count;
	public:
		Lace_CHR(const uint16& count = 1) : count(count) {}
	};

	class Lace_DEL { //------------Remove first Char(s) from Lace------------
		friend class Lace;
		uint16 count;
	public:
		Lace_DEL(const uint16& count = 1) : count(count) {}
	};

	class Lace_POP { //------------Remove last Char(s) from Lace------------
		friend class Lace;
		uint16 count;
	public:
		Lace_POP(const uint16& count = 1) : count(count) {}
	};

	class Lace { //------------Utility for string manipulation------------
		stringstream data;
		uint16 current_tab; // Global Tabbing to be transferred through new lines
		const string character;
	public:

		Lace();
		Lace(const string& character);

		Lace& operator<< (const Lace& value);
		Lace& operator>> (const Lace& value);

		Lace& operator+= (const uint16& value);
		Lace& operator-= (const uint16& value);
		Lace& operator++ (int);
		Lace& operator-- (int);

		Lace& operator<<(const Lace_S& val);
		Lace& operator<<(const Lace_NL& val);
		Lace& operator<<(const Lace_TAB& val);
		Lace& operator<<(const Lace_CHR& val);
		Lace& operator<<(const Lace_DEL& val);
		Lace& operator<<(const Lace_POP& val);

		Lace& clear();
		string str() const;

		// Feed directly
		Lace& operator<< (const bool& value);
		Lace& operator<< (const char* value);
		Lace& operator<< (const string& value);
		Lace& operator<< (const stringstream& value);

		Lace& operator<< (const int8& value);
		Lace& operator<< (const int16& value);
		Lace& operator<< (const int32& value);
		Lace& operator<< (const int64& value);
		Lace& operator<< (const uint8& value);
		Lace& operator<< (const uint16& value);
		Lace& operator<< (const uint32& value);
		Lace& operator<< (const uint64& value);

		// Feed Single Units With Space Before
		Lace& operator>> (const bool& value);
		Lace& operator>> (const char* value);
		Lace& operator>> (const float& value);
		Lace& operator>> (const double& value);
		Lace& operator>> (const int8& value);
		Lace& operator>> (const int16& value);
		Lace& operator>> (const int32& value);
		Lace& operator>> (const int64& value);
		Lace& operator>> (const uint8& value);
		Lace& operator>> (const uint16& value);
		Lace& operator>> (const uint32& value);
		Lace& operator>> (const uint64& value);

		// Vectors
		Lace& operator<< (const vector<string>& value);
	};

	template<typename T>
	T f_readBinary(const vector<Byte>& data, const uint64& start) {
		T value;
		std::memcpy(&value, data.data() + start, sizeof(T));
		return value;
	};

	template<typename T>
	T f_readBinary(const vector<Byte>& data, const uint64& start, const uint64& size) {
		T value;
		std::memcpy(&value, data.data() + start, size);
		return value;
	}

	template<>
	string f_readBinary<string>(const vector<Byte>& data, const uint64& start, const uint64& size);

	template<typename T>
	vector<Byte> f_toBinary(const T& value) {
		vector<Byte> data;
		const uint64 size = sizeof(T); // - 1 Careful: removing null terminator
		const Byte* byte_data = reinterpret_cast<const Byte*>(&value);

		data.reserve(size);
		data.insert(data.end(), byte_data, byte_data + size);
		return data;
	};

	template<>
	vector<Byte> f_toBinary<string>(const string& value);

	class Bin_Lace { //------------Utility for binary manipulation------------
		vector<Byte> internal_data;
	public:
		Bin_Lace();

		Bin_Lace& operator<< (const Bin_Lace& value);

		const char* data() const;
		uint64 size() const;

		template <typename T>
		Bin_Lace& operator<< (const T& value) {
			vector<Byte> bytes = f_toBinary(value);
			const uint64 size = bytes.size();

			internal_data.reserve(internal_data.size() + size);
			internal_data.insert(internal_data.end(), bytes.begin(), bytes.end());
			return *this;
		};
	};
}

#define ENDL << CORE::Lace_NL()

#define ANSI_RESET  << "\033[0m"

#define ANSI_BLACK  << "\033[90m"
#define ANSI_R      << "\033[91m"
#define ANSI_G      << "\033[92m"
#define ANSI_YELLOW << "\033[93m"
#define ANSI_B      << "\033[94m"
#define ANSI_PURPLE << "\033[95m"
#define ANSI_CYAN   << "\033[96m"
#define ANSI_WHITE  << "\033[97m"
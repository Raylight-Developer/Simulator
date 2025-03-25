#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace ARITHMETIC {
		enum struct Type { ADD, SUB, MUL, DIV };
	}
	namespace ALGEBRA {
		enum struct Type { ABS, POW, SQRT, LOGARITHM, MOD };
	}
	namespace TRIGONOMETRY {
		enum struct Type { SIN, COS, TAN, ASIN, ACOS, ATAN, SINH, COSH, TANH, COT, SEC, CSC, COTH, SECH, CSCH };
	}
	namespace ROUNDING {
		enum struct Type { ROUND, FLOOR, CEIL };
	}
	namespace MAPPING {
		enum struct Type { MAP_RANGE, CURVE };
	}
	namespace CONVERSION {
		enum struct Type { DEG_TO_RAD, RAD_TO_DEG };
	}
	namespace INTERPOLATION {
		enum struct Type { LERP, EASE };
	}
	namespace BOOLEAN_COMPARISON {
		enum struct Type { EQUAL, GT, LT, GEQ, LEQ, SIGN, COMPARE };
	}
	namespace BOOLEAN {
		enum struct Type { IF, IF_ELSE, SWITCH, AND, OR, NOT };
	}
	namespace EXEC {
		enum struct Type { SEQUENCE, COUNTER, START, TICK, FOR_INDEX, FOR_ELEMENT, WHILE };
	}
	namespace SCRIPT {
	}
	namespace UTILS {
		enum struct Type { RNG_GEN, RNG_DISTRIBUTION };
	}
	namespace INPUT {
		enum struct Type { DOUBLE, VEC2 };
	}
	namespace CAST {
		namespace MAKE {
			enum struct Type { VEC2 };
		}
		namespace BREAK {

		}
	}

	namespace CONTAINER {
		namespace VECTOR {
			enum struct Type { AT, PUSH, POP, INSERT, REMOVE, SIZE };
		}
		namespace DEQUE {
			enum struct Type { AT, PUSH, POP, PUSH_FRONT, POP_FRONT, INSERT, REMOVE, SIZE };
		}
		namespace MAP {
			enum struct Type { AT, SET, REMOVE, SIZE };
		}
	}

	namespace RENDERING {
		namespace DIM_2D {
			namespace PRIMITIVE {
				enum struct Type { CIRCLE };
			}
		}
		namespace DIM_3D {
			namespace PRIMITIVE {
				enum struct Type { SPHERE, CYLINDER, CONE, TORUS, CUBOID };
			}
		}
	}
}

namespace NODES {
	struct Arithmetic : Node {
		const set<VARIABLE::Type> allowed_types;
		VARIABLE::Type var_type;

		PORT::Data_I* i_a;
		PORT::Data_I* i_b;
		PORT::Data_O* out;

		GUI::Options* enums;

		Arithmetic();

		void setType(const VARIABLE::Type& type);

		bool onConnRequested(Port* port, Connection* conn);
		void onDisconnection(Port* port);
		//void onTypeChanged(Port* port, const VARIABLE::Type& var_type);

		Variable getData(const Port* port) const override;
	};
	struct Trigonometry : Node {
		PORT::Data_I* in;
		PORT::Data_O* out;

		GUI::Options* enums;

		Trigonometry();
		bool call_connRequest(Port* port, Connection* conn);

		Variable getData(const Port* port) const override;
	};
	namespace INPUT {
		struct Integer : Node {
			PORT::Data_O* out;
			GUI::Value_Input* input;
			int64 value;

			Integer();

			Variable getData(const Port* port) const override;
		};
		struct Double : Node {
			PORT::Data_O* out;
			GUI::Value_Input* input;
			dvec1 value;

			Double();

			Variable getData(const Port* port) const override;
		};
		struct Bool : Node {
			PORT::Data_O* out;
			GUI::Toggle* input;
			bool value;

			Bool();

			Variable getData(const Port* port) const override;
		};
		struct String : Node {
			PORT::Data_O* out;
			GUI::Value_Input* input;
			QString value;

			String();

			Variable getData(const Port* port) const override;
		};
		struct Vec2 : Node {
			PORT::Data_O* out;
			GUI::Value_Input* input_x;
			GUI::Value_Input* input_y;
			dvec2 value;

			Vec2();

			Variable getData(const Port* port) const override;
		};
		struct Vec3 : Node {
			PORT::Data_O* out;
			GUI::Value_Input* input_x;
			GUI::Value_Input* input_y;
			GUI::Value_Input* input_z;
			dvec3 value;

			Vec3();

			Variable getData(const Port* port) const override;
		};
		struct Vec4 : Node {
			PORT::Data_O* out;
			GUI::Value_Input* input_x;
			GUI::Value_Input* input_y;
			GUI::Value_Input* input_z;
			GUI::Value_Input* input_w;
			dvec4 value;

			Vec4();

			Variable getData(const Port* port) const override;
		};
	}

	namespace CAST {
		namespace MAKE {
			struct Vec2 : Node {
				PORT::Data_I* i_x;
				PORT::Data_I* i_y;
				PORT::Data_O* out;

				Vec2();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Vec3 : Node {
				PORT::Data_I* i_x;
				PORT::Data_I* i_y;
				PORT::Data_I* i_z;
				PORT::Data_O* out;

				Vec3();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Vec4 : Node {
				PORT::Data_I* i_x;
				PORT::Data_I* i_y;
				PORT::Data_I* i_z;
				PORT::Data_I* i_w;
				PORT::Data_O* out;

				Vec4();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Quat : Node {
				PORT::Data_I* i_w;
				PORT::Data_I* i_x;
				PORT::Data_I* i_y;
				PORT::Data_I* i_z;
				PORT::Data_O* out;

				Quat();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat2 : Node {
				PORT::Data_I* i_a;
				PORT::Data_I* i_b;
				PORT::Data_O* out;

				Mat2();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat3 : Node {
				PORT::Data_I* i_a;
				PORT::Data_I* i_b;
				PORT::Data_I* i_c;
				PORT::Data_O* out;

				Mat3();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat4 : Node {
				PORT::Data_I* i_a;
				PORT::Data_I* i_b;
				PORT::Data_I* i_c;
				PORT::Data_I* i_d;
				PORT::Data_O* out;

				Mat4();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
		}
	}

	namespace EXEC {
		struct Euler_Tick : Node {
			dvec1 delta;
			PORT:: Exec_O* exec_out;
			PORT:: Data_O* delta_out;

			Euler_Tick();

			void exec(const dvec1& delta);
			Variable getData(const Port* port) const override;
		};
	}

	namespace RENDERING {
		namespace DIM_2D {
			struct Line : Node {
				PORT::Exec_I* exec_in;
				PORT::Exec_O* exec_out;

				PORT::Data_I* vert_a;
				PORT::Data_I* vert_b;
				PORT::Data_I* width;
				PORT::Data_I* color;

				Line();

				GLuint VAO, VBO, EBO;
				void init();
				void render();

				void exec(const Port* port) override;
			};
			struct Triangle : Node {
				PORT::Exec_I* exec_in;
				PORT::Exec_O* exec_out;

				PORT::Data_I* vert_a;
				PORT::Data_I* vert_b;
				PORT::Data_I* vert_c;
				PORT::Data_I* color;

				Triangle();

				GLuint VAO, VBO;
				void init();
				void render();

				void exec(const Port* port) override;
			};
			struct Rectangle : Node {
				PORT::Exec_I* exec_in;
				PORT::Exec_O* exec_out;

				PORT::Data_I* vert_a;
				PORT::Data_I* vert_b;
				PORT::Data_I* vert_c;
				PORT::Data_I* vert_d;
				PORT::Data_I* color;

				Rectangle();

				GLuint VAO, VBO, EBO;
				void init();
				void render();

				void exec(const Port* port) override;
			};
			struct Circle : Node {
				PORT::Exec_I* exec_in;
				PORT::Exec_O* exec_out;

				PORT::Data_I* center;
				PORT::Data_I* radius;
				PORT::Data_I* color;

				Circle();

				GLuint VAO, VBO, EBO;
				void init();
				void render();

				void exec(const Port* port) override;
			};
		}
	}
}
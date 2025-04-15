#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace VARIABLES {
		struct Constant;
		struct Get;
		struct Set;
	}
	namespace CAST {
		namespace MAKE {
			struct Vec2;
			struct Vec3;
			struct Vec4;
			struct Quat;
			struct Mat2;
			struct Mat3;
			struct Mat4;
		}
		namespace BREAK {

		}
	}

	struct Arithmetic;
	struct Trigonometry;

	namespace ALGEBRA {
		enum struct Type { ABS, POW, SQRT, LOGARITHM, MOD };
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
	namespace UTILS {
		enum struct Type { RNG_GEN, RNG_DISTRIBUTION };
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

	namespace BOOLEAN {
		enum struct Type { IF, IF_ELSE, SWITCH, AND, OR, NOT };
		struct Compare;
		struct If;
		struct If_Else;
		struct Select;
	}
	namespace EXEC {
		struct Input_Key;
		struct Input_Mouse;
		enum struct Type { SEQUENCE, COUNTER, START, TICK, FOR_INDEX, FOR_ELEMENT, WHILE };
	}
	namespace SINGLETON {
		struct Euler_Tick;
		struct Background;
		struct Camera_2D;
		struct Camera_3D;
	}
	namespace RENDERING {
		namespace DIM_2D {
			namespace PRIMITIVE {
				struct Line;
				struct Triangle;
				struct Rectangle;
				struct Circle;
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
	namespace VARIABLES {
		struct Constant : Node {
			PORT::Data_O* out;

			CORE::Stack<GUI::Graphics_Widget*> proxies;
			GUI::Options* enums;
			QRectF expanded;
			Variable value;

			Constant();

			Variable getData(const Port* port) const override;

			struct Set_Type : Self<Set_Type>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
			struct Set_Value : Self<Set_Value>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
		struct Get : Node {
			PORT::Data_O* out;
			GUI::Label* label;
			QString var;

			Get();
			void setVar(const QString name);

			Variable getData(const Port* port) const override;

			struct Set_Variable : Self<Set_Variable>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
		struct Set : Node {
			PORT::Exec_I* exec_in;
			PORT::Exec_O* exec_out;
			PORT::Data_I* in;
			PORT::Data_O* out;
			GUI::Label* label;
			QString var;

			Set();

			void h_setVar(const QString name);
			void setVar(const QString name);

			void exec(const Port* port) override;
			Variable getData(const Port* port) const override;

			struct Set_Variable : Self<Set_Variable>, CORE::CMD {
				Set* node;
				QString from, to;

				Set_Variable(Set* node, const QString& from, const QString& to);

				void execute() const final override;
				void undo() final override;
			};
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

	struct Arithmetic : Node {
		PORT::Data_I* i_a;
		PORT::Data_I* i_b;
		PORT::Data_O* out;

		GUI::Options* enums;

		Arithmetic();

		Variable getData(const Port* port) const override;

		struct Set_Mode : Self<Set_Mode>, CORE::CMD {
			//TODO
			void execute() const final override;
			void undo() final override;
		};
	};
	struct Trigonometry : Node {
		PORT::Data_I* in;
		PORT::Data_O* out;

		GUI::Options* enums;

		Trigonometry();

		Variable getData(const Port* port) const override;

		struct Set_Mode : Self<Set_Mode>, CORE::CMD {
			//TODO
			void execute() const final override;
			void undo() final override;
		};
	};

	namespace BOOLEAN {
		struct Compare : Node {
			PORT::Data_I* in_a;
			PORT::Data_I* in_b;
			PORT::Data_O* out;

			GUI::Options* enums;

			Compare();

			bool onConnRequested(Port* port, Connection* conn);
			void onDisconnection(Port* port);
			void cascade(Port* port, const VAR_TYPE& var_type);

			Variable getData(const Port* port) const override;

			struct Set_Mode : Self<Set_Mode>, CORE::CMD {
				//TODO
				void execute() const final override;
				void undo() final override;
			};
		};
		struct If : Node {
			PORT::Exec_I* in;
			PORT::Data_I* condition;
			PORT::Exec_O* out;

			If();

			void exec(const Port* port) override;
		};
		struct If_Else : Node {
			PORT::Exec_I* in;
			PORT::Data_I* condition;
			PORT::Exec_O* out_a;
			PORT::Exec_O* out_b;

			If_Else();

			void exec(const Port* port) override;
		};
		struct Select : Node {
			PORT::Data_I* condition;
			PORT::Data_I* i_true;
			PORT::Data_I* i_false;
			PORT::Data_O* out;

			Select();

			bool onConnRequested(Port* port, Connection* conn);
			void onDisconnection(Port* port);

			Variable getData(const Port* port) const override;
		};
	}

	namespace EXEC {
		struct Input_Key : Node {
			PORT:: Exec_O* exec_press;
			PORT:: Exec_O* exec_release;
			PORT:: Data_O* key;

			Input_Key();

			Variable getData(const Port* port) const override;
		};
		struct Input_Mouse : Node {
			PORT:: Exec_O* exec_press;
			PORT:: Exec_O* exec_release;
			PORT:: Data_O* button;

			Input_Mouse();

			Variable getData(const Port* port) const override;
		};
	}

	namespace SINGLETON {
		struct Euler_Tick : Node {
			F64 delta;
			PORT:: Exec_O* exec_out;
			PORT:: Data_O* o_delta;
			PORT:: Data_O* o_calls;
			PORT:: Data_O* o_runtime;

			Euler_Tick();

			void exec(const F64& delta);
			Variable getData(const Port* port) const override;
		};
		struct Background : Node {
			PORT:: Exec_I* exec_in;
			PORT:: Exec_O* exec_out;

			PORT:: Data_I* color_in;

			Background();

			void exec(const Port* port) override;
		};
		struct Camera_2D : Node {
			PORT:: Exec_I* exec_in;
			PORT:: Exec_O* exec_out;

			PORT:: Data_I* center;
			PORT:: Data_I* zoom;

			Camera_2D();

			void exec(const Port* port) override;
		};
		struct Camera_3D : Node {
			PORT:: Exec_I* exec_in;
			PORT:: Exec_O* exec_out;

			Camera_3D();

			void exec(const Port* port) override;
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

				void render();

				void exec(const Port* port) override;
			};
		}
	}
}
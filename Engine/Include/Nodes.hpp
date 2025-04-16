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
/*
#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	struct Temp : Node {
		void exec(const Port* port) override;
		Variable getData(const Port* port) const override;
	};
}
*/

#include "Nodes/Variables/Constant.hpp"
#include "Nodes/Variables/Get.hpp"
#include "Nodes/Variables/Set.hpp"

#include "Nodes/Singleton/Background.hpp"
#include "Nodes/Singleton/Euler_Tick.hpp"

#include "Nodes/Rendering/2D/Line.hpp"
#include "Nodes/Rendering/2D/Circle.hpp"
#include "Nodes/Rendering/2D/Triangle.hpp"
#include "Nodes/Rendering/2D/Rectangle.hpp"

namespace NODES {
	namespace CAST {
		namespace MAKE {
			struct Vec2 : Node {
				Ptr_U<PORT::Data_I> i_x;
				Ptr_U<PORT::Data_I> i_y;
				Ptr_U<PORT::Data_O> out;

				Vec2();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Vec3 : Node {
				Ptr_U<PORT::Data_I> i_x;
				Ptr_U<PORT::Data_I> i_y;
				Ptr_U<PORT::Data_I> i_z;
				Ptr_U<PORT::Data_O> out;

				Vec3();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Vec4 : Node {
				Ptr_U<PORT::Data_I> i_x;
				Ptr_U<PORT::Data_I> i_y;
				Ptr_U<PORT::Data_I> i_z;
				Ptr_U<PORT::Data_I> i_w;
				Ptr_U<PORT::Data_O> out;

				Vec4();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Quat : Node {
				Ptr_U<PORT::Data_I> i_w;
				Ptr_U<PORT::Data_I> i_x;
				Ptr_U<PORT::Data_I> i_y;
				Ptr_U<PORT::Data_I> i_z;
				Ptr_U<PORT::Data_O> out;

				Quat();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat2 : Node {
				Ptr_U<PORT::Data_I> i_a;
				Ptr_U<PORT::Data_I> i_b;
				Ptr_U<PORT::Data_O> out;

				Mat2();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat3 : Node {
				Ptr_U<PORT::Data_I> i_a;
				Ptr_U<PORT::Data_I> i_b;
				Ptr_U<PORT::Data_I> i_c;
				Ptr_U<PORT::Data_O> out;

				Mat3();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat4 : Node {
				Ptr_U<PORT::Data_I> i_a;
				Ptr_U<PORT::Data_I> i_b;
				Ptr_U<PORT::Data_I> i_c;
				Ptr_U<PORT::Data_I> i_d;
				Ptr_U<PORT::Data_O> out;

				Mat4();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
		}
	}

	struct Arithmetic : Node {
		Ptr_U<PORT::Data_I> i_a;
		Ptr_U<PORT::Data_I> i_b;
		Ptr_U<PORT::Data_O> out;

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
		Ptr_U<PORT::Data_I> in;
		Ptr_U<PORT::Data_O> out;

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
			Ptr_U<PORT::Data_I> in_a;
			Ptr_U<PORT::Data_I> in_b;
			Ptr_U<PORT::Data_O> out;

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
			Ptr_U<PORT::Exec_I> in;
			Ptr_U<PORT::Data_I> condition;
			Ptr_U<PORT::Exec_O> out;

			If();

			void exec(const Port* port) override;
		};
		struct If_Else : Node {
			Ptr_U<PORT::Exec_I> in;
			Ptr_U<PORT::Data_I> condition;
			Ptr_U<PORT::Exec_O> out_a;
			Ptr_U<PORT::Exec_O> out_b;

			If_Else();

			void exec(const Port* port) override;
		};
		struct Select : Node {
			Ptr_U<PORT::Data_I> condition;
			Ptr_U<PORT::Data_I> i_true;
			Ptr_U<PORT::Data_I> i_false;
			Ptr_U<PORT::Data_O> out;

			Select();

			bool onConnRequested(Port* port, Connection* conn);
			void onDisconnection(Port* port);

			Variable getData(const Port* port) const override;
		};
	}

	namespace EXEC {
		struct Input_Key : Node {
			Ptr_U<PORT::Exec_O> exec_press;
			Ptr_U<PORT::Exec_O> exec_release;
			Ptr_U<PORT::Data_O> key;

			Input_Key();

			Variable getData(const Port* port) const override;
		};
		struct Input_Mouse : Node {
			Ptr_U<PORT::Exec_O> exec_press;
			Ptr_U<PORT::Exec_O> exec_release;
			Ptr_U<PORT::Data_O> button;

			Input_Mouse();

			Variable getData(const Port* port) const override;
		};
	}

	namespace SINGLETON {
		struct Camera_2D : Node {
			Ptr_U<PORT::Exec_I> exec_in;
			Ptr_U<PORT::Exec_O> exec_out;

			Ptr_U<PORT::Data_I> center;
			Ptr_U<PORT::Data_I> zoom;

			Camera_2D();

			void exec(const Port* port) override;
		};
		struct Camera_3D : Node {
			Ptr_U<PORT::Exec_I> exec_in;
			Ptr_U<PORT::Exec_O> exec_out;

			Camera_3D();

			void exec(const Port* port) override;
		};
	}
}
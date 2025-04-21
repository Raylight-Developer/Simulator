#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES::VARIABLES {
	struct Constant;
	struct Get;
	struct Set;
}
#include "Nodes/Variables/Constant.hpp"
#include "Nodes/Variables/Get.hpp"
#include "Nodes/Variables/Set.hpp"

namespace NODES::MATH {
	struct Arithmetic;
	struct Trigonometry;
}
#include "Nodes/Math/Trigonometry.hpp"
#include "Nodes/Math/Arithmetic.hpp"
namespace NODES::MATH::ALGEBRA {
	enum struct Type { ABS, POW, SQRT, LOGARITHM, MOD };
}
namespace NODES::MATH::ROUNDING {
	enum struct Type { ROUND, FLOOR, CEIL };
}

namespace NODES::CAST {
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

namespace NODES::MAPPING {
	enum struct Type { MAP_RANGE, CURVE };
}
namespace NODES::CONVERSION {
	enum struct Type { DEG_TO_RAD, RAD_TO_DEG };
}
namespace NODES::INTERPOLATION {
	enum struct Type { LERP, EASE };
}
namespace NODES::UTILS {
	enum struct Type { RNG_GEN, RNG_DISTRIBUTION };
}
namespace NODES::CONTAINER {
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

namespace NODES::BOOLEAN {
	enum struct Type { IF, IF_ELSE, SWITCH, AND, OR, NOT };
	struct Compare;
	struct Select;
}
#include "Nodes/Boolean/Compare.hpp"
#include "Nodes/Boolean/Select.hpp"

namespace NODES::EXEC {
	struct If;
	struct If_Else;
	struct Reset;
	struct Subsample;
	struct Input_Key;
	struct Input_Mouse;
	enum struct Type { SEQUENCE, COUNTER, START, TICK, FOR_INDEX, FOR_ELEMENT, WHILE };
}
#include "Nodes/Exec/Subsample.hpp"
#include "Nodes/Exec/If_Else.hpp"
#include "Nodes/Exec/If.hpp"

namespace NODES::SINGLETON {
	struct Euler_Tick;
	struct Background;
	struct Camera_2D;
	struct Camera_3D;
}
#include "Nodes/Singleton/Background.hpp"
#include "Nodes/Singleton/Euler_Tick.hpp"
#include "Nodes/Singleton/Reset.hpp"

namespace NODES::RENDERING {
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
#include "Nodes/Rendering/2D/Line.hpp"
#include "Nodes/Rendering/2D/Circle.hpp"
#include "Nodes/Rendering/2D/Triangle.hpp"
#include "Nodes/Rendering/2D/Rectangle.hpp"

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

namespace NODES {
	namespace CAST {
		namespace MAKE {
			struct Vec2 : Node {	
				PORT_DATA_I i_x;
				PORT_DATA_I i_y;
				PORT_DATA_O out;

				Vec2();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Vec3 : Node {
				PORT_DATA_I i_x;
				PORT_DATA_I i_y;
				PORT_DATA_I i_z;
				PORT_DATA_O out;

				Vec3();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Vec4 : Node {
				PORT_DATA_I i_x;
				PORT_DATA_I i_y;
				PORT_DATA_I i_z;
				PORT_DATA_I i_w;
				PORT_DATA_O out;

				Vec4();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Quat : Node {
				PORT_DATA_I i_w;
				PORT_DATA_I i_x;
				PORT_DATA_I i_y;
				PORT_DATA_I i_z;
				PORT_DATA_O out;

				Quat();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat2 : Node {
				PORT_DATA_I i_a;
				PORT_DATA_I i_b;
				PORT_DATA_O out;

				Mat2();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat3 : Node {
				PORT_DATA_I i_a;
				PORT_DATA_I i_b;
				PORT_DATA_I i_c;
				PORT_DATA_O out;

				Mat3();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
			struct Mat4 : Node {
				PORT_DATA_I i_a;
				PORT_DATA_I i_b;
				PORT_DATA_I i_c;
				PORT_DATA_I i_d;
				PORT_DATA_O out;

				Mat4();

				void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
				Variable getData(const Port* port) const override;
			};
		}
	}

	namespace SINGLETON {
		struct Camera_2D : Node {
			PORT_EXEC_I exec_in;
			PORT_EXEC_O exec_out;

			PORT_DATA_I center;
			PORT_DATA_I zoom;

			Camera_2D();

			void exec(const Port* port) override;
		};
		struct Camera_3D : Node {
			PORT_EXEC_I exec_in;
			PORT_EXEC_O exec_out;

			Camera_3D();

			void exec(const Port* port) override;
		};
	}
}
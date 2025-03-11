#pragma once

#include "Include.hpp"

#include "Node.hpp"

namespace NODES {
	namespace ARITHMETIC {
		enum struct Type { ADD, SUB, MUL, DIV, MOD };
	}
	namespace ALGEBRA {
		enum struct Type { ABS, POW, SQRT, LOG };
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
		enum struct Type { DEG_RAD, RAD_DEG };
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
	namespace LOOP {
		enum struct Type { FOR_INDEX, FOR_ELEMENT, WHILE };
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

	namespace RENDERING {
		namespace DIM_2D {
			namespace PRIMITIVE {
				enum struct Type { CIRCLE };
			}
			struct Line;
		}
		namespace DIM_3D {
			namespace PRIMITIVE {
				enum struct Type { SPHERE, CYLINDER, CONE, TORUS, CUBOID };
			}
		}
	}
}
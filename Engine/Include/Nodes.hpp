#pragma once

#include "Include.hpp"

#include "Node.hpp"

namespace NODE {
	namespace NODES {
		namespace ARITHMETIC {
			enum struct Type { ADD, SUB, MUL, DIV };
		}
		namespace ALGEBRA {
			enum struct Type { ABS, POW, SQRT, LOG, MOD };
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
		namespace EXEC {
			enum struct Type { SEQUENCE, COUNTER, SCRIPT, START, TICK, FOR_INDEX, FOR_ELEMENT, WHILE };
		}
		namespace UTILS {
			enum struct Type { RNG_GEN, RNG_DISTRIBUTION };
		}
		namespace CASTING {
			enum struct Type { F_TO_I };
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
}

namespace NODE {
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

		namespace RENDERING {
			namespace DIM_2D {
				struct Line;
			}
		}
	}
}
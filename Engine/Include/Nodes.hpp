#pragma once

#include "KL.hpp"

namespace NODES::VARIABLE {
	struct Constant;
	struct Get;
	struct Set;
}
#include "Nodes/Variables/Constant.hpp"
#include "Nodes/Variables/Get.hpp"
#include "Nodes/Variables/Set.hpp"

namespace NODES::CAST {
	namespace CONVERT {
		struct I64_To_F64;
	}
	namespace MAKE {
		struct Color;
		struct Vec2;
		struct Vec3;
		struct Vec4;
		struct Quat;
		struct Mat2;
		struct Mat3;
		struct Mat4;
	}
	namespace BREAK {
		struct Color;
		struct Vec2;
		struct Vec3;
		struct Vec4;
		struct Quat;
		struct Mat2;
		struct Mat3;
		struct Mat4;
	}
}
#include "Nodes/Cast/Convert/I64_To_F64.hpp"
#include "Nodes/Cast/Break/Break_Vec2.hpp"
#include "Nodes/Cast/Make/Make_Color.hpp"
#include "Nodes/Cast/Make/Make_Vec2.hpp"
#include "Nodes/Cast/Make/Make_Vec3.hpp"
#include "Nodes/Cast/Make/Make_Vec4.hpp"
#include "Nodes/Cast/Make/Make_Quat.hpp"
#include "Nodes/Cast/Make/Make_Mat2.hpp"
#include "Nodes/Cast/Make/Make_Mat3.hpp"
#include "Nodes/Cast/Make/Make_Mat4.hpp"

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

namespace NODES::CONTAINER::LIST {
	struct Access;
	struct Create;
	struct Insert;
	struct Modify;
	struct Remove;
	struct Clear;
	struct Push;
	struct Size;
}
#include "Nodes/Container/List/Access.hpp"
#include "Nodes/Container/List/Create.hpp"
#include "Nodes/Container/List/Insert.hpp"
#include "Nodes/Container/List/Modify.hpp"
#include "Nodes/Container/List/Remove.hpp"
#include "Nodes/Container/List/Clear.hpp"
#include "Nodes/Container/List/Push.hpp"
#include "Nodes/Container/List/Size.hpp"

namespace NODES::BOOLEAN {
	enum struct Type { SWITCH, AND, OR, NOT };
	struct Compare;
	struct Select;
}
#include "Nodes/Boolean/Compare.hpp"
#include "Nodes/Boolean/Select.hpp"

namespace NODES::EXEC {
	namespace LOOP {
		struct Subsample;
		struct While;
		struct For;
	}
	struct If_Else;
	struct If;
	enum struct Type { SEQUENCE, COUNTER, START, TICK, FOR_INDEX, FOR_ELEMENT, WHILE };
}
#include "Nodes/Exec/Loop/Subsample.hpp"
#include "Nodes/Exec/Loop/While.hpp"
#include "Nodes/Exec/Loop/For.hpp"
#include "Nodes/Exec/If_Else.hpp"
#include "Nodes/Exec/If.hpp"

namespace NODES::HOOK {
	namespace INPUT {
		struct Mouse_Wheel;
		struct Mouse_Pos;
		struct Mouse;
		struct Key;
	}
	struct Display;
}
#include "Nodes/Hook/Input/Mouse_Wheel.hpp"
#include "Nodes/Hook/Input/Mouse_Pos.hpp"
#include "Nodes/Hook/Input/Mouse.hpp"
#include "Nodes/Hook/Input/Key.hpp"
#include "Nodes/Hook/Display.hpp"

namespace NODES::SINGLETON {
	struct Euler_Tick;
	struct Background;
	struct Camera_2D;
	struct Camera_3D;
	struct Init;
}
#include "Nodes/Singleton/Camera_2D.hpp"
#include "Nodes/Singleton/Camera_3D.hpp"
#include "Nodes/Singleton/Background.hpp"
#include "Nodes/Singleton/Euler_Tick.hpp"
#include "Nodes/Singleton/Init.hpp"

namespace NODES::RENDERING {
	namespace DIM_2D {
		namespace PRIMITIVE {
			struct Rectangle;
			struct Triangle;
			struct Circle;
			struct Line;
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
		Ptr_S<Variable> getData(const Port* port) override;
	};
}
*/

namespace NODES {
	static const unordered_map<Node_Type, function<Ptr_S<Node>()>> node_get_map = {
		{ Node_Type::NONE                    , []() { return nullptr; }},
		{ Node_Type::SCRIPT                  , []() { return nullptr; }},
		{ Node_Type::VARIABLE_CONSTANT       , []() { return make_shared<VARIABLE::Constant>();           }},
		{ Node_Type::VARIABLE_GET            , []() { return make_shared<VARIABLE::Get>();                }},
		{ Node_Type::VARIABLE_SET            , []() { return make_shared<VARIABLE::Set>();                }},
		{ Node_Type::CAST_CONVERT_I64_TO_F64 , []() { return make_shared<CAST::CONVERT::I64_To_F64>();    }},
		{ Node_Type::CAST_BREAK_VEC2         , []() { return make_shared<CAST::BREAK::Vec2>();            }},
		{ Node_Type::CAST_MAKE_COLOR         , []() { return make_shared<CAST::MAKE::Color>();            }},
		{ Node_Type::CAST_MAKE_VEC2          , []() { return make_shared<CAST::MAKE::Vec2>();             }},
		{ Node_Type::CAST_MAKE_VEC3          , []() { return make_shared<CAST::MAKE::Vec3>();             }},
		{ Node_Type::CAST_MAKE_VEC4          , []() { return make_shared<CAST::MAKE::Vec4>();             }},
		{ Node_Type::CAST_MAKE_QUAT          , []() { return make_shared<CAST::MAKE::Quat>();             }},
		{ Node_Type::CAST_MAKE_MAT2          , []() { return make_shared<CAST::MAKE::Mat2>();             }},
		{ Node_Type::CAST_MAKE_MAT3          , []() { return make_shared<CAST::MAKE::Mat3>();             }},
		{ Node_Type::CAST_MAKE_MAT4          , []() { return make_shared<CAST::MAKE::Mat4>();             }},
		{ Node_Type::MATH_TRIGONOMETRIC      , []() { return make_shared<MATH::Trigonometry>();           }},
		{ Node_Type::MATH_ARITHMETIC         , []() { return make_shared<MATH::Arithmetic>();             }},
		{ Node_Type::CONTAINER_LIST_ACCESS   , []() { return make_shared<CONTAINER::LIST::Access>();      }},
		{ Node_Type::CONTAINER_LIST_CREATE   , []() { return make_shared<CONTAINER::LIST::Create>();      }},
		{ Node_Type::CONTAINER_LIST_INSERT   , []() { return make_shared<CONTAINER::LIST::Insert>();      }},
		{ Node_Type::CONTAINER_LIST_MODIFY   , []() { return make_shared<CONTAINER::LIST::Modify>();      }},
		{ Node_Type::CONTAINER_LIST_REMOVE   , []() { return make_shared<CONTAINER::LIST::Remove>();      }},
		{ Node_Type::CONTAINER_LIST_CLEAR    , []() { return make_shared<CONTAINER::LIST::Clear>();       }},
		{ Node_Type::CONTAINER_LIST_PUSH     , []() { return make_shared<CONTAINER::LIST::Push>();        }},
		{ Node_Type::CONTAINER_LIST_SIZE     , []() { return make_shared<CONTAINER::LIST::Size>();        }},
		{ Node_Type::BOOLEAN_COMPARE         , []() { return make_shared<BOOLEAN::Compare>();             }},
		{ Node_Type::BOOLEAN_SELECT          , []() { return make_shared<BOOLEAN::Select>();              }},
		{ Node_Type::EXEC_LOOP_SUBSAMPLE     , []() { return make_shared<EXEC::LOOP::Subsample>();        }},
		{ Node_Type::EXEC_LOOP_WHILE         , []() { return make_shared<EXEC::LOOP::While>();            }},
		{ Node_Type::EXEC_LOOP_FOR           , []() { return make_shared<EXEC::LOOP::For>();              }},
		{ Node_Type::EXEC_IF_ELSE            , []() { return make_shared<EXEC::If_Else>();                }},
		{ Node_Type::EXEC_IF                 , []() { return make_shared<EXEC::If>();                     }},
		{ Node_Type::HOOK_INPUT_MOUSE_WHEEL  , []() { return make_shared<HOOK::INPUT::Mouse_Wheel>();     }},
		{ Node_Type::HOOK_INPUT_MOUSE_POS    , []() { return make_shared<HOOK::INPUT::Mouse_Pos>();       }},
		{ Node_Type::HOOK_INPUT_MOUSE        , []() { return make_shared<HOOK::INPUT::Mouse>();           }},
		{ Node_Type::HOOK_INPUT_KEY          , []() { return make_shared<HOOK::INPUT::Key>();             }},
		{ Node_Type::HOOK_DISPLAY            , []() { return make_shared<HOOK::Display>();                }},
		{ Node_Type::SINGLETON_BACKGROUND    , []() { return make_shared<SINGLETON::Background>();        }},
		{ Node_Type::SINGLETON_EULER_TICK    , []() { return make_shared<SINGLETON::Euler_Tick>();        }},
		{ Node_Type::SINGLETON_2D_CAMERA     , []() { return make_shared<SINGLETON::Camera_2D>();         }},
		{ Node_Type::SINGLETON_3D_CAMERA     , []() { return make_shared<SINGLETON::Camera_3D>();         }},
		{ Node_Type::SINGLETON_INIT          , []() { return make_shared<SINGLETON::Init>();              }},
		{ Node_Type::RENDER_2D_RECTANGLE     , []() { return make_shared<RENDERING::DIM_2D::Rectangle>(); }},
		{ Node_Type::RENDER_2D_TRIANGLE      , []() { return make_shared<RENDERING::DIM_2D::Triangle>();  }},
		{ Node_Type::RENDER_2D_CIRCLE        , []() { return make_shared<RENDERING::DIM_2D::Circle>();    }},
		{ Node_Type::RENDER_2D_LINE          , []() { return make_shared<RENDERING::DIM_2D::Line>();      }}
	};

	static const vector<pair<Node_Type, string_view>> enum_str_map {{
		{ Node_Type::NONE                    , "NONE"                      },
		{ Node_Type::SCRIPT                  , "SCRIPT"                    },
		{ Node_Type::VARIABLE_CONSTANT       , "VARIABLE::CONSTANT"        },
		{ Node_Type::VARIABLE_GET            , "VARIABLE::GET"             },
		{ Node_Type::VARIABLE_SET            , "VARIABLE::SET"             },
		{ Node_Type::CAST_CONVERT_I64_TO_F64 , "CAST::CONVERT::I64_TO_F64" },
		{ Node_Type::CAST_BREAK_VEC2         , "CAST::BREAK::VEC2"         },
		{ Node_Type::CAST_MAKE_COLOR         , "CAST::MAKE::COLOR"         },
		{ Node_Type::CAST_MAKE_VEC2          , "CAST::MAKE::VEC2"          },
		{ Node_Type::CAST_MAKE_VEC3          , "CAST::MAKE::VEC3"          },
		{ Node_Type::CAST_MAKE_VEC4          , "CAST::MAKE::VEC4"          },
		{ Node_Type::CAST_MAKE_QUAT          , "CAST::MAKE::QUAT"          },
		{ Node_Type::CAST_MAKE_MAT2          , "CAST::MAKE::MAT2"          },
		{ Node_Type::CAST_MAKE_MAT3          , "CAST::MAKE::MAT3"          },
		{ Node_Type::CAST_MAKE_MAT4          , "CAST::MAKE::MAT4"          },
		{ Node_Type::MATH_TRIGONOMETRIC      , "MATH::TRIGONOMETRIC"       },
		{ Node_Type::MATH_ARITHMETIC         , "MATH::ARITHMETIC"          },
		{ Node_Type::CONTAINER_LIST_ACCESS   , "CONTAINER::LIST::ACCESS"   },
		{ Node_Type::CONTAINER_LIST_CREATE   , "CONTAINER::LIST::CREATE"   },
		{ Node_Type::CONTAINER_LIST_INSERT   , "CONTAINER::LIST::INSERT"   },
		{ Node_Type::CONTAINER_LIST_MODIFY   , "CONTAINER::LIST::MODIFY"   },
		{ Node_Type::CONTAINER_LIST_REMOVE   , "CONTAINER::LIST::REMOVE"   },
		{ Node_Type::CONTAINER_LIST_CLEAR    , "CONTAINER::LIST::CLEAR"    },
		{ Node_Type::CONTAINER_LIST_PUSH     , "CONTAINER::LIST::PUSH"     },
		{ Node_Type::CONTAINER_LIST_SIZE     , "CONTAINER::LIST::SIZE"     },
		{ Node_Type::BOOLEAN_COMPARE         , "BOOLEAN::COMPARE"          },
		{ Node_Type::BOOLEAN_SELECT          , "BOOLEAN::SELECT"           },
		{ Node_Type::EXEC_LOOP_SUBSAMPLE     , "EXEC::LOOP::SUBSAMPLE"     },
		{ Node_Type::EXEC_LOOP_WHILE         , "EXEC::LOOP::WHILE"         },
		{ Node_Type::EXEC_LOOP_FOR           , "EXEC::LOOP::FOR"           },
		{ Node_Type::EXEC_IF_ELSE            , "EXEC::IF_ELSE"             },
		{ Node_Type::EXEC_IF                 , "EXEC::IF"                  },
		{ Node_Type::HOOK_INPUT_MOUSE_WHEEL  , "HOOK::INPUT::MOUSE_WHEEL"  },
		{ Node_Type::HOOK_INPUT_MOUSE_POS    , "HOOK::INPUT::MOUSE_POS"    },
		{ Node_Type::HOOK_INPUT_MOUSE        , "HOOK::INPUT::MOUSE"        },
		{ Node_Type::HOOK_INPUT_KEY          , "HOOK::INPUT::KEY"          },
		{ Node_Type::HOOK_DISPLAY            , "HOOK::DISPLAY"             },
		{ Node_Type::SINGLETON_BACKGROUND    , "SINGLETON::BACKGROUND"     },
		{ Node_Type::SINGLETON_EULER_TICK    , "SINGLETON::EULER_TICK"     },
		{ Node_Type::SINGLETON_2D_CAMERA     , "SINGLETON::2D_CAMERA"      },
		{ Node_Type::SINGLETON_3D_CAMERA     , "SINGLETON::3D_CAMERA"      },
		{ Node_Type::SINGLETON_INIT          , "SINGLETON::INIT"           },
		{ Node_Type::RENDER_2D_RECTANGLE     , "RENDERING::2D::RECTANGLE"  },
		{ Node_Type::RENDER_2D_TRIANGLE      , "RENDERING::2D::TRIANGLE"   },
		{ Node_Type::RENDER_2D_CIRCLE        , "RENDERING::2D::CIRCLE"     },
		{ Node_Type::RENDER_2D_LINE          , "RENDERING::2D::LINE"       }
	}};

	string toString(const Node_Type& value);
	Node_Type toEnum(const string_view& name);
}
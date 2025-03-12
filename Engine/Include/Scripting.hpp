#pragma once

#include "Include.hpp"

#include "Node.hpp"

namespace NODE {
	namespace NODES {
		namespace EXEC {
			struct Script;
		}
	}
}

namespace NODE {
	namespace NODES {
		namespace EXEC {
			struct Script : Node {
				Script(const QString& id);
				~Script();
			};
		}
	}
}
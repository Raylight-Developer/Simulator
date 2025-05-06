#pragma once

#include "KL.hpp"

#include "Node.hpp"

using namespace NODE;

namespace NODES {
	namespace HOOK {
		struct Display : Node {
			PORT_DATA_O do_resolution;
			PORT_DATA_O do_camera_pos;
			PORT_DATA_O do_camera_zoom;

			Display();

			Ptr_S<Variable> getData(const Port* port) override;
		};
	}
}
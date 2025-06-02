#include "Script.hpp"

#define NANOSVG_IMPLEMENTATION
#undef FILE
#include "nanosvg.h"

static NSVGimage* image;

Script::Script(Session* session) : SCRIPT("SVG Renderer", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(180);
	rect.setHeight(60);

	ei_exec = EXEC_I("");
	eo_exec = EXEC_O("");

	image = nsvgParseFromFile("D:/Coding/Simulator/Script-SVG-Art-Showcase/Art.svg", "px", 96.0f);

	LOGL(<< "Loaded Base Script");
}

void Script::onUnload() {
	nsvgDelete(image);

	LOGL(<< "Unloaded Base Script");
}

void Script::exec(const Exec_I* port) {
	if (image) {
		const F32 svg_width  = image->width;
		const F32 svg_height = -image->height;
		const F32_V2 svg_center(svg_width * 0.5f, svg_height * 0.5f);

		for (NSVGshape* shape = image->shapes; shape != nullptr; shape = shape->next) {
			// Use fill color
			const U32 colorInt = shape->fill.color;
			const F32_V4 fillColor = {
				((colorInt >> 16) & 0xFF) / 255.0f,
				((colorInt >> 8)  & 0xFF) / 255.0f,
				((colorInt >> 0)  & 0xFF) / 255.0f,
				((colorInt >> 24) & 0xFF) / 255.0f
			};

			const float radius = shape->strokeWidth * 0.5f;

			for (NSVGpath* path = shape->paths; path != nullptr; path = path->next) {
				for (int i = 0; i < path->npts - 1; i++) {
					F32* p = &path->pts[i * 2];
					const F32_V2 a = F32_V2(p[0], -p[1]) - svg_center;
					const F32_V2 b = F32_V2(p[2], -p[3]) - svg_center;
					RENDER::Dim_2D::RoundedLine(a, b, radius, Color(fillColor));
				}
			}
		}
	}

	execAllDownstream();
}
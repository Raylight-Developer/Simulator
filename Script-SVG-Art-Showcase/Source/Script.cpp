#include "Script.hpp"

#define NANOSVG_ALL_COLOR_KEYWORDS
#define NANOSVG_IMPLEMENTATION
#undef FILE
#include "nanosvg.h"

#include "earcut.h"

static NSVGimage* image;

Script::Script(Session* session) : SCRIPT("SVG Renderer", session) {
	SCRIPT_INIT;
}

void Script::onLoad() {
	rect.setWidth(160);
	rect.setHeight(80);

	ei_exec = EXEC_I("");
	di_resolution = DATA_I("Res", Variable(4.0f));

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

		const F32 segmentLength = *di_resolution->GET_DATA(F64);

		for (NSVGshape* shape = image->shapes; shape != nullptr; shape = shape->next) {
			const F32 radius = shape->strokeWidth * 0.35f;
			for (NSVGpath* path = shape->paths; path != nullptr; path = path->next) {
				// Render Path
				for (I32 i = 0; i < path->npts - 1; i += 3) {
					const F32* p = &path->pts[i * 2];

					const F32_V2 p0 = F32_V2(p[0], -p[1]) - svg_center;
					const F32_V2 p1 = F32_V2(p[2], -p[3]) - svg_center;
					const F32_V2 p2 = F32_V2(p[4], -p[5]) - svg_center;
					const F32_V2 p3 = F32_V2(p[6], -p[7]) - svg_center;

					const F32 curveLength = glm::distance(p0, p1) + glm::distance(p1, p2) + glm::distance(p2, p3);
					const I32 steps = max(2, static_cast<I32>(curveLength / segmentLength));

					F32_V2 prev = p0 * 0.09f;
					for (I32 s = 1; s <= steps; ++s) {
						const F32 t = static_cast<F32>(s) / steps;
						const F32_V2 pt = cubicBezier(p0, p1, p2, p3, t) * 0.09f;
						RENDER::Dim_2D::RoundedLine(prev, pt, radius, Color(1,1,1,1));
						prev = pt;
					}
				}
			}
		}
	}

	execAllDownstream();
}

F32_V2 cubicBezier(const F32_V2& p0, const F32_V2& p1, const F32_V2& p2, const F32_V2& p3, const F32& t) {
	const F32 it = 1.0f - t;
	return it * it * it * p0 + 3.0f * it * it * t * p1 + 3.0f * it * t * t * p2 + t * t * t * p3;
}
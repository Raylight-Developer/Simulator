#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"
#include "OpenGL.hpp"

struct Viewport : QOpenGLWidget, QOpenGLFunctions_4_5_Core {
	F64 aspect_ratio;
	T_V2<U64> resolution;

	U64 frame_counter;
	U64 frame_count;

	Timestamp current_time;
	Timestamp start_time;
	Timestamp last_time;
	F64 window_time;

	unordered_map<string, GLuint> gl_data;
	OpenGL::Texture render_tex;

	Viewport();
	~Viewport();

	void f_pipeline();
	void f_tickUpdate();
	void f_compile();

	void f_timings();
	void f_guiUpdate();
	void f_frameUpdate();

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

	void wheelEvent(QWheelEvent* event) override;
};
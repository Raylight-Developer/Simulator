#pragma once

#include "KL.hpp"

struct Viewport : QOpenGLWidget, protected QOpenGLFunctions_4_5_Core {
	dvec1 aspect_ratio;
	uvec2 resolution;

	uint64 frame_counter;
	uint64 frame_count;

	Timestamp current_time;
	Timestamp start_time;
	Timestamp last_time;
	dvec1 window_time;
	dvec1 delta_time;

	unordered_map<uint, bool> inputs;
	dvec2 current_mouse;
	dvec2 last_mouse;

	Viewport(QWidget* parent);
	~Viewport();

	void f_pipeline();

	void f_tickUpdate();

	void f_timings();
	void f_guiUpdate();
	void f_inputLoop();
	void f_frameUpdate();

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

	void mouseReleaseEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
};
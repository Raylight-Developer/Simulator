#include "Viewport.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

Viewport::Viewport() :
	QOpenGLWindow(),

	frame_counter(0),
	frame_count(0),

	resolution(T_V2<U64>(3840U, 2160U)),
	aspect_ratio(to_F64(resolution.x) / to_F64(resolution.y)),

	center_2d(F64_V2(0.0, 0.0)),
	zoom_2d(1.0),
	move_2d(false),

	current_mouse(F64_V2(to_F64(resolution.x / 2ULL), to_F64(resolution.y / 2ULL))),
	last_mouse(current_mouse),

	window_time(0.0),
	delta_time(0.01666666)
{
	SESSION->viewport = this;
}

Viewport::~Viewport() {
}

void Viewport::f_tickUpdate() {
	if (SESSION->active or SESSION->realtime) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		if (FILE.euler_tick) {
			if (SESSION->realtime) {
				FILE.euler_tick->exec(delta_time > 0.025 ? 0.025 : delta_time);
			}
			else {
				FILE.euler_tick->exec(1.0 / SESSION->samples);
			}
		}
		SESSION->current_frame++;
	}
}

void Viewport::f_compile() {
	{
		const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Template.vert", "./Shaders/2D/Template.frag");
		if (confirm) {
			SP_2D_Triangle  = confirm.data;
			SP_2D_Rectangle = confirm.data;
		}
	}
	RENDER::Dim_2D::INIT::Line();
	RENDER::Dim_2D::INIT::Circle();
}

void Viewport::f_pipeline() {
	GL = this;

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, resolution.x, resolution.y);

	f_compile();
}

void Viewport::f_guiUpdate() {
	if (window_time > 1.0) {
		frame_count = frame_counter;
		window_time = 0.0;
		frame_counter = 0;
	}
}

void Viewport::f_inputLoop() {
}

void Viewport::f_timings() {
	current_time = chrono::high_resolution_clock::now();
	delta_time = chrono::duration<double>(current_time - last_time).count();
	last_time = current_time;
	window_time += delta_time;
}

void Viewport::f_frameUpdate() {
	frame_counter++;
}

void Viewport::initializeGL() {
	initializeOpenGLFunctions();
	f_pipeline();
	start_time = chrono::high_resolution_clock::now();
}

void Viewport::paintGL() {
	f_timings();
	f_inputLoop();
	f_tickUpdate();

	f_frameUpdate();
	f_guiUpdate();

	requestUpdate();
}

void Viewport::resizeGL(int w, int h) {
	resolution = T_V2<U64>(to_U64(w), to_U64(h));
	aspect_ratio = to_F64(resolution.x) / to_F64(resolution.y);

	glViewport(0, 0, resolution.x, resolution.y);
}

void Viewport::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::MouseButton::RightButton or event->button() == Qt::MouseButton::MiddleButton) {
		move_2d = false;
	}
}

void Viewport::mousePressEvent(QMouseEvent* event) {
	last_mouse = p_to_d(event->pos());
	if (event->button() == Qt::MouseButton::RightButton or event->button() == Qt::MouseButton::MiddleButton) {
		move_2d = true;
	}
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
	current_mouse = p_to_d(event->pos());
	if (move_2d) {
		const F64_V2 delta = last_mouse - p_to_d(event->pos());
		center_2d += F64_V2(-delta.x, delta.y) / zoom_2d;
		last_mouse = p_to_d(event->pos());
	}
}

void Viewport::keyReleaseEvent(QKeyEvent* event) {
}

void Viewport::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key::Key_R) {
		f_compile();
	}
}

void Viewport::wheelEvent(QWheelEvent* event) {
	const QPoint scrollAmount = event->angleDelta();
	if (scrollAmount.y() > 0) {
		zoom_2d *= 1.1;
	}
	else {
		zoom_2d /= 1.1;
	}
}
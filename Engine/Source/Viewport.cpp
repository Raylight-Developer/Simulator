#include "Viewport.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

Viewport::Viewport(QWidget* parent) :
	QOpenGLWidget(parent),

	frame_counter(0),
	frame_count(0),

	resolution(uvec2(3840U, 2160U)),
	aspect_ratio(u_to_d(resolution.x) / u_to_d(resolution.y)),

	current_mouse(u_to_d(resolution / 2U)),
	last_mouse(current_mouse),

	window_time(0.0),
	delta_time(0.01666666)
{}

Viewport::~Viewport() {
}

void Viewport::f_tickUpdate() {
	glClear(GL_COLOR_BUFFER_BIT);

	FILE.tick.pointer->exec(delta_time);
}

void Viewport::f_guiUpdate() {
	if (window_time > 1.0) {
		frame_count = frame_counter;
		window_time = 0.0;
		frame_counter = 0;
	}
}

void Viewport::f_inputLoop() {
	if (inputs[Qt::Key::Key_Enter]) {
		
	}
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

void Viewport::f_pipeline() {
	GL = this;
	{
		const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Line.vert", "./Shaders/2D/Line.frag");
		if (confirm) {
			NODES::RENDERING::DIM_2D::SP_Line = confirm.data;
		}
	}
	{
		const auto confirm = OpenGL::f_compileFragShader("./Shaders/2D/Rect.vert", "./Shaders/2D/Rect.frag");
		if (confirm) {
			NODES::RENDERING::DIM_2D::SP_Rect = confirm.data;
		}
	}
}

void Viewport::initializeGL() {
	initializeOpenGLFunctions();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, resolution.x, resolution.y);

	f_pipeline();
	start_time = chrono::high_resolution_clock::now();
}

void Viewport::paintGL() {
	f_timings();
	f_inputLoop();
	f_tickUpdate();

	f_frameUpdate();
	f_guiUpdate();

	update();
}

void Viewport::resizeGL(int w, int h) {
	resolution = uvec2(i_to_u(w), i_to_u(h));
	aspect_ratio = u_to_d(resolution.x) / u_to_d(resolution.y);

	glViewport(0, 0, resolution.x, resolution.y);
}

void Viewport::mouseReleaseEvent(QMouseEvent* event) {
	inputs[event->button()] = false;
}

void Viewport::mousePressEvent(QMouseEvent* event) {
	inputs[event->button()] = true;
	last_mouse = p_to_d(event->pos());
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
	current_mouse = p_to_d(event->pos());
}

void Viewport::keyReleaseEvent(QKeyEvent* event) {
	inputs[event->key()] = false;
}

void Viewport::keyPressEvent(QKeyEvent* event) {
	inputs[event->key()] = true;
}

void Viewport::wheelEvent(QWheelEvent* event) {
	const QPoint scrollAmount = event->angleDelta();
	if (scrollAmount.y() > 0) {
	}
	else {
	}
}
#include "Viewport.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

Viewport::Viewport() :
	QOpenGLWidget(),

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
	delta_time(0.01666666),
	playback_delta_time(0.01666666)
{
	QSurfaceFormat format;
	format.setSwapInterval(0);
	QSurfaceFormat::setDefaultFormat(format);
	setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

	setMouseTracking(true);
	SESSION->viewport = this;
	SESSION->hook.viewport_resolution = F64_V2(to_F64(resolution.x), to_F64(resolution.y));
}

Viewport::~Viewport() {
}

void Viewport::f_tickUpdate() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	switch (SESSION->playback_mode) {
		case Playback_Mode::REALTIME: {
			if (FILE.euler_tick) {
				FILE.euler_tick->exec(delta_time > 0.25 ? 0.25 : delta_time);
				SESSION->hook.current_frame++;
			}
			break;
		}
		case Playback_Mode::PLAYING: {
			if (FILE.euler_tick) {
				FILE.euler_tick->exec(playback_delta_time);
				SESSION->hook.current_frame++;
			}
			break;
		}
		case Playback_Mode::O_STOPPED: {
			glBindFramebuffer(GL_FRAMEBUFFER, gl_data["FRAME -1 FBO"]);

			glViewport(0, 0, resolution.x, resolution.y);
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			if (FILE.euler_tick) {
				FILE.euler_tick->exec(1.0 / SESSION->samples);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			SESSION->playback_mode = Playback_Mode::STOPPED;
			break;
		}
		case Playback_Mode::O_RESET: {
			glBindFramebuffer(GL_FRAMEBUFFER, gl_data["FRAME 0 FBO"]);

			glViewport(0, 0, resolution.x, resolution.y);
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			if (FILE.reset) {
				FILE.reset->exec();
			}
			if (FILE.euler_tick) {
				FILE.euler_tick->runtime = 0.0;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			SESSION->playback_mode = Playback_Mode::RESET;
			break;
		}
		case Playback_Mode::STOPPED: {
			const GLuint Shader = gl_data["FBO Shader"];
			glUseProgram(Shader);

			glBindVertexArray(gl_data["FBO VAO"]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gl_data["FRAME -1 FBT"]);
			glUniform1ui(glGetUniformLocation(Shader, "uFboTexture"), 0);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			glUseProgram(0);
			break;
		}
		case Playback_Mode::RESET: {
			const GLuint Shader = gl_data["FBO Shader"];
			glUseProgram(Shader);

			glBindVertexArray(gl_data["FBO VAO"]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gl_data["FRAME 0 FBT"]);
			glUniform1ui(glGetUniformLocation(Shader, "uFboTexture"), 0);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			glUseProgram(0);
			break;
		}
	}
}

void Viewport::f_compile() {
	RENDER::INIT::Fbo();
	RENDER::Dim_2D::INIT::Line();
	RENDER::Dim_2D::INIT::Circle();
	RENDER::Dim_2D::INIT::Triangle();
	RENDER::Dim_2D::INIT::Rectangle();

	gl_data["FRAME -1 FBO"] = 0;
	gl_data["FRAME -1 FBT"] = 0;
	gl_data["FRAME 0 FBO"] = 0;
	gl_data["FRAME 0 FBT"] = 0;
	OpenGL::createFbo(&gl_data["FRAME -1 FBO"], &gl_data["FRAME -1 FBT"], resolution, GL_UNSIGNED_BYTE, GL_LINEAR);
	OpenGL::createFbo(&gl_data["FRAME 0 FBO"], &gl_data["FRAME 0 FBT"], resolution, GL_UNSIGNED_BYTE, GL_LINEAR);
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

	if (SESSION->playback_mode == Playback_Mode::REALTIME || SESSION->playback_mode == Playback_Mode::PLAYING) {
		QPainter painter(this);
		if (frame_count >= 60) {
			painter.setPen(QColor(50, 255, 50));
		}
		else if (frame_count >= 48) {
			painter.setPen(QColor(150, 255, 50));
		}
		else if (frame_count >= 24) {
			painter.setPen(QColor(255, 150, 50));
		}
		else {
			painter.setPen(QColor(255, 50, 50));
		}
		painter.drawText(20, 20, "FPS:");
		painter.setPen(Qt::white);
		painter.drawText(65, 20, QString::number(frame_count));
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

	update();
}

void Viewport::resizeGL(int w, int h) {
	const F64 pixelRatio = devicePixelRatio();
	const int p_w = int(w * pixelRatio);
	const int p_h = int(h * pixelRatio);

	resolution = T_V2<U64>(to_U64(p_w), to_U64(p_h));
	aspect_ratio = to_F64(resolution.x) / to_F64(resolution.y);

	SESSION->hook.viewport_resolution = F64_V2(to_F64(resolution.x), to_F64(resolution.y));

	glViewport(0, 0, resolution.x, resolution.y);

	OpenGL::resizeFbo(&gl_data["FRAME -1 FBO"], &gl_data["FRAME -1 FBT"], resolution, GL_UNSIGNED_BYTE, GL_LINEAR);
	OpenGL::resizeFbo(&gl_data["FRAME 0 FBO"], &gl_data["FRAME 0 FBT"], resolution, GL_UNSIGNED_BYTE, GL_LINEAR);
}

void Viewport::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::MouseButton::RightButton || event->button() == Qt::MouseButton::MiddleButton) {
		move_2d = false;
	}
	SESSION->hook.input_down[qtKey(event->button())] = false;
}

void Viewport::mousePressEvent(QMouseEvent* event) {
	last_mouse = p_to_d(event->pos());
	if (event->button() == Qt::MouseButton::RightButton || event->button() == Qt::MouseButton::MiddleButton) {
		move_2d = true;
	}
	SESSION->hook.input_down[qtKey(event->button())] = true;
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
	current_mouse = p_to_d(event->pos());
	if (move_2d) {
		const F64_V2 delta = last_mouse - p_to_d(event->pos());
		center_2d += F64_V2(-delta.x, delta.y) / zoom_2d;
		last_mouse = p_to_d(event->pos());
	}

	SESSION->hook.mouse_pos = current_mouse;
}

void Viewport::keyReleaseEvent(QKeyEvent* event) {
	//SESSION->hook.input_down[qtKey(event->key())] = false;
}

void Viewport::keyPressEvent(QKeyEvent* event) {
	//SESSION->hook.input_down[qtKey(event->key())] = true;
}

void Viewport::wheelEvent(QWheelEvent* event) {
	const QPoint scrollAmount = event->angleDelta();
	if (scrollAmount.y() > 0) {
		zoom_2d *= 1.1;
	}
	else {
		zoom_2d /= 1.1;
	}
	SESSION->hook.mouse_wheel.x = scrollAmount.x();
	SESSION->hook.mouse_wheel.y = scrollAmount.y();
}
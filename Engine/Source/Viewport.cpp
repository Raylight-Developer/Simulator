#include "Viewport.hpp"

#include "Session.hpp"
#include "OpenGL.hpp"

constexpr F64 MS_15 = 1.0 / 15.0;
constexpr F64 MS_60 = 1.0 / 60.0;

Viewport::Viewport() :
	QOpenGLWidget(),

	frame_counter(0),
	frame_count(0),

	resolution(T_V2<U64>(3840U, 2160U)),
	aspect_ratio(to_F64(resolution.x) / to_F64(resolution.y)),

	window_time(0.0)
{
	QSurfaceFormat format;
	format.setSwapInterval(0);
	QSurfaceFormat::setDefaultFormat(format);
	setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

	setMouseTracking(true);
	SESSION->viewport = this;
	SIM_HOOK.viewport_resolution = F64_V2(to_F64(resolution.x), to_F64(resolution.y));
}

Viewport::~Viewport() {
}

void Viewport::f_tickUpdate() {
	switch (SIM_HOOK.playback_mode) {
		case Playback_Mode::REALTIME: {
			const F64 delta = min(SIM_HOOK.delta_time, MS_15);
			{
				glViewport(0, 0, resolution.x, resolution.y);
				glClearColor(0, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);

				const GLuint Shader = gl_data["BG Shader"];
				glUseProgram(Shader);

				glBindVertexArray(gl_data["Screen VAO"]);

				glUniform1f (glGetUniformLocation(Shader, "iTime"), to_F32(SIM_HOOK.exec_time));
				glUniform1ui(glGetUniformLocation(Shader, "iFrame"), to_U32(SIM_HOOK.current_frame));
				glUniform1f (glGetUniformLocation(Shader, "iTimedelta"), to_F32(delta));
				glUniform2f (glGetUniformLocation(Shader, "iResolution"), to_F32(resolution.x), to_F32(resolution.y));

				glUniform1f (glGetUniformLocation(Shader, "uZoom"), to_F32(SIM_HOOK.camera_zoom_2d));
				glUniform2fv(glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_pos_2d)));

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				glBindVertexArray(0);
				glUseProgram(0);
			}

			RENDER::Dim_3D::Sphere(F32_V3(1.0, 1.0, 0.0), 1.0);

			for (const auto& [k, f] : SIM_HOOK.onTick) {
				f(delta);
			}
			if (FILE.euler_tick) {
				FILE.euler_tick->exec(delta);
				SIM_HOOK.current_frame++;
			}
			for (const auto& func : SESSION->gl_3d_callbacks) {
				func();
			}
			SESSION->gl_3d_callbacks.clear();
			RENDER::Dim_3D::renderSphere();
			for (const auto& func : SESSION->gl_2d_callbacks) {
				func();
			}
			SESSION->gl_2d_callbacks.clear();
			break;
		}
		case Playback_Mode::PLAYING: {
			{
				glViewport(0, 0, resolution.x, resolution.y);
				glClearColor(0, 0, 0, 1);
				glClear(GL_COLOR_BUFFER_BIT);

				const GLuint Shader = gl_data["BG Shader"];
				glUseProgram(Shader);

				glBindVertexArray(gl_data["Screen VAO"]);

				glUniform1f (glGetUniformLocation(Shader, "iTime"), to_F32(SIM_HOOK.exec_time));
				glUniform1ui(glGetUniformLocation(Shader, "iFrame"), to_U32(SIM_HOOK.current_frame));
				glUniform1f (glGetUniformLocation(Shader, "iTimedelta"), to_F32(SIM_HOOK.playback_delta_time));
				glUniform2ui(glGetUniformLocation(Shader, "iResolution"), to_U32(resolution.x), to_U32(resolution.y));

				glUniform1f (glGetUniformLocation(Shader, "uZoom"), to_F32(SIM_HOOK.camera_zoom_2d));
				glUniform2fv(glGetUniformLocation(Shader, "uCenter"), 1, glm::value_ptr(to_F32(SIM_HOOK.camera_pos_2d)));

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				glBindVertexArray(0);
				glUseProgram(0);
			}

			RENDER::Dim_3D::Sphere(F32_V3(1.0, 1.0, 0.0), 0.5);

			for (const auto& [k, f] : SIM_HOOK.onTick) {
				f(SIM_HOOK.playback_delta_time);
			}
			if (FILE.euler_tick) {
				FILE.euler_tick->exec(SIM_HOOK.playback_delta_time);
				SIM_HOOK.current_frame++;
			}
			for (const auto& func : SESSION->gl_3d_callbacks) {
				func();
			}
			SESSION->gl_3d_callbacks.clear();
			RENDER::Dim_3D::renderSphere();
			for (const auto& func : SESSION->gl_2d_callbacks) {
				func();
			}
			SESSION->gl_2d_callbacks.clear();

			{
				const GLuint Shader = gl_data["Paused Shader"];
				glUseProgram(Shader);

				glBindVertexArray(gl_data["Screen VAO"]);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, gl_data["Screen Tex"]);
				glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, resolution.x, resolution.y);

				glUniform1i(glGetUniformLocation(Shader, "uFbt"), 0);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				glBindVertexArray(0);
				glUseProgram(0);
			}
			break;
		}
		case Playback_Mode::STOPPED: {
			glViewport(0, 0, resolution.x, resolution.y);
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			const GLuint Shader = gl_data["Paused Shader"];
			glUseProgram(Shader);

			glBindVertexArray(gl_data["Screen VAO"]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gl_data["Screen Tex"]);
			glUniform1i(glGetUniformLocation(Shader, "uFbt"), 0);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			glUseProgram(0);
			break;
		}
		case Playback_Mode::RESET: {
			glViewport(0, 0, resolution.x, resolution.y);
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			break;
		}
	}
}

void Viewport::f_compile() {
	RENDER::INIT::Screen();
	RENDER::Dim_2D::INIT::Line();
	RENDER::Dim_2D::INIT::Circle();
	RENDER::Dim_2D::INIT::Triangle();
	RENDER::Dim_2D::INIT::Rectangle();

	RENDER::Dim_3D::INIT::Sphere();
	{
		const auto confirm = OpenGL::f_compileFragShader("./Shaders/Screen.vert", "./Shaders/Paused.frag");
		if (confirm) {
			gl_data["Paused Shader"] = confirm.data;
		}
	}
	{
		const auto confirm = OpenGL::f_compileFragShader("./Shaders/Screen.vert", "./Shaders/Background.frag");
		if (confirm) {
			gl_data["BG Shader"] = confirm.data;
		}
	}
	OpenGL::createTex(&gl_data["Screen Tex"], resolution, GL_LINEAR);
}

void Viewport::f_pipeline() {
	GL = this;

//#ifdef _DEBUG
//	glEnable(GL_DEBUG_OUTPUT);
//	glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
//		LOGL(<< "[OpenGL Debug] (" << id << "): " << message);
//
//		if (severity == GL_DEBUG_SEVERITY_HIGH) {
//			LOGL(<< " --> SEVERITY: HIGH");
//		}
//	}, nullptr);
//#endif

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

	if (SIM_HOOK.playback_mode == Playback_Mode::REALTIME || SIM_HOOK.playback_mode == Playback_Mode::PLAYING) {
		QPainter painter(this);

		for (const auto& [k, f] : SIM_HOOK.onGuiRender) {
			f(&painter);
		}

		//TODO move to script
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

void Viewport::f_timings() {
	current_time = chrono::high_resolution_clock::now();
	SIM_HOOK.delta_time = chrono::duration<double>(current_time - last_time).count();
	last_time = current_time;
	window_time += SIM_HOOK.delta_time;
}

void Viewport::f_frameUpdate() {
	frame_counter++;
}

void Viewport::initializeGL() {
	initializeOpenGLFunctions();
	f_pipeline();

	for (auto& [k, f] : SIM_HOOK.onInit) {
		f();
	}
	if (FILE.init) {
		FILE.init->exec();
	}
	start_time = chrono::high_resolution_clock::now();
}

void Viewport::paintGL() {
	f_timings();
	f_tickUpdate();

	f_frameUpdate();
	f_guiUpdate();

	SIM_HOOK.mouse_wheel.x = 0.0;
	SIM_HOOK.mouse_wheel.y = 0.0;

	update();
}

void Viewport::resizeGL(int w, int h) {
	const F64 pixelRatio = devicePixelRatio();
	const int p_w = int(w * pixelRatio);
	const int p_h = int(h * pixelRatio);

	resolution = T_V2<U64>(to_U64(p_w), to_U64(p_h));
	aspect_ratio = to_F64(resolution.x) / to_F64(resolution.y);

	SIM_HOOK.viewport_resolution = F64_V2(to_F64(resolution.x), to_F64(resolution.y));

	glViewport(0, 0, resolution.x, resolution.y);

	OpenGL::resizeTex(&gl_data["Screen Tex"], resolution);
}

void Viewport::wheelEvent(QWheelEvent* event) {
	const QPoint scrollAmount = event->angleDelta();
	SIM_HOOK.mouse_wheel.x = scrollAmount.x();
	SIM_HOOK.mouse_wheel.y = scrollAmount.y();

	for (auto& [k, f] : SIM_HOOK.onWheel) {
		f(p_to_d(scrollAmount));
	}
}
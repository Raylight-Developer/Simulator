#include "Timeline.hpp"

#include "Viewport.hpp"
#include "Session.hpp"
#include "OpenGL.hpp"

//⏮⏭⏹⏯⏩⏪⏺⏏🔁🔀🔃🔄ℹ⏴⏵

Timeline::Timeline(QWidget* parent) :
	GUI::Linear_Contents(parent)
{
	auto start_stop = new GUI::Square_Button(this);
	start_stop->setText("⏯");

	auto reset_realtime = new GUI::Square_Button(this);
	reset_realtime->setText("🔄");

	auto mode = new GUI::Toggle(this);
	mode->setText("Mode: Playback");

	auto samples_label = new GUI::Label(this, "Samples (Frames) per second: ");
	samples_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

	auto samples = new GUI::Int_Input(1, MAX(int), this);
	samples->setText("60");

	addWidget(start_stop);
	addWidget(reset_realtime);
	addWidget(mode);
	addWidget(samples_label);
	addWidget(samples);
	setFixedHeight(24);

	connect(start_stop, &GUI::Square_Button::pressed, [this, start_stop, reset_realtime]() {
		if (SIM_HOOK.playback_mode == Playback_Mode::PLAYING) {
			SIM_HOOK.playback_mode = Playback_Mode::STOPPED;
			start_stop->setText("⏩");
			on_stopped = NOW;

			reset_realtime->show();
		}
		else if (SIM_HOOK.playback_mode == Playback_Mode::STOPPED) {
			SIM_HOOK.playback_mode = Playback_Mode::PLAYING;
			start_stop->setText("⏹");
			reset_realtime->hide();

			SIM_HOOK.playback_start += NOW - on_stopped;
		}
		else if (SIM_HOOK.playback_mode == Playback_Mode::RESET) {
			SIM_HOOK.playback_mode = Playback_Mode::PLAYING;
			start_stop->setText("⏹");
			reset_realtime->hide();

			SIM_HOOK.playback_start = NOW;
			SIM_HOOK.current_frame = 0;
		}
	});

	connect(reset_realtime, &GUI::Square_Button::pressed, [this, reset_realtime, start_stop]() {
		if (SIM_HOOK.playback_mode == Playback_Mode::REALTIME) {
			SIM_HOOK.playback_start = NOW;
			SIM_HOOK.current_frame = 0;
		}
		else {
			SIM_HOOK.playback_mode = Playback_Mode::RESET;
			SIM_HOOK.playback_start = NOW;
			SIM_HOOK.current_frame = 0;
			reset_realtime->hide();
			start_stop->setText("⏯");
		}

		for (auto& [k, f] : SIM_HOOK.onInit) {
			f();
		}
		if (FILE.init) {
			FILE.init->exec();
		}
		SIM_HOOK.exec_time = 0.0;
	});

	connect(mode, &GUI::Toggle::toggled, [this, start_stop, samples, samples_label, mode, reset_realtime](bool checked) {
		if (checked) {
			SIM_HOOK.playback_mode = Playback_Mode::REALTIME;
			SIM_HOOK.playback_start = NOW;
			SIM_HOOK.current_frame = 0;
			mode->setText("Mode: Realtime");
			start_stop->hide();
			samples_label->hide();
			samples->hide();
			reset_realtime->show();
		}
		else {
			mode->setText("Mode: Playback");
			SIM_HOOK.playback_mode = Playback_Mode::RESET;
			start_stop->setText("⏯");
			start_stop->show();
			samples_label->show();
			samples->show();
			reset_realtime->hide();

			{
				for (auto& [k, f] : SIM_HOOK.onInit) {
					f();
				}
				if (FILE.init) {
					FILE.init->exec();
				}
				SIM_HOOK.exec_time = 0.0;
			}
		}
	});

	connect(samples, &GUI::Int_Input::textChanged, [this](const QString& value) {
		SIM_HOOK.samples = value.toInt();
		SIM_HOOK.playback_delta_time = 1.0 / to_F64(SIM_HOOK.samples);
	});

	mode->toggle();
}
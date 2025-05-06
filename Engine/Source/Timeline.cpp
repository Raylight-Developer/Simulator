#include "Timeline.hpp"

#include "Session.hpp"

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

	connect(start_stop, &GUI::Square_Button::pressed, [this, start_stop]() {
		if (SESSION->playback_mode == Playback_Mode::PLAYING) {
			SESSION->playback_mode = Playback_Mode::O_STOPPED;
			start_stop->setText("🔄");
		}
		else if (SESSION->playback_mode == Playback_Mode::STOPPED) {
			SESSION->playback_mode = Playback_Mode::O_RESET;
			start_stop->setText("⏯");
		}
		else if (SESSION->playback_mode == Playback_Mode::RESET) {
			SESSION->playback_mode = Playback_Mode::PLAYING;
			start_stop->setText("⏹");

			SESSION->hook.playback_start = NOW;
			SESSION->hook.current_frame = 0;
		}
	});

	connect(reset_realtime, &GUI::Square_Button::pressed, [this]() {
		SESSION->hook.playback_start = NOW;
		SESSION->hook.current_frame = 0;

		for (auto& [k, f] : SESSION->hook.onReset) {
			f();
		}
		if (FILE.reset) {
			FILE.reset->exec();
		}
		if (FILE.euler_tick) {
			FILE.euler_tick->runtime = 0.0;
		}
	});

	connect(mode, &GUI::Toggle::toggled, [this, start_stop, samples, samples_label, mode, reset_realtime](bool checked) {
		if (checked) {
			SESSION->playback_mode = Playback_Mode::REALTIME;
			SESSION->hook.playback_start = NOW;
			SESSION->hook.current_frame = 0;
			mode->setText("Mode: Realtime");
			start_stop->hide();
			samples_label->hide();
			samples->hide();
			reset_realtime->show();
		}
		else {
			mode->setText("Mode: Playback");
			SESSION->playback_mode = Playback_Mode::O_RESET;
			start_stop->setText("⏯");
			start_stop->show();
			samples_label->show();
			samples->show();
			reset_realtime->hide();
		}
	});

	connect(samples, &GUI::Int_Input::textChanged, [this](const QString& value) {
		SESSION->samples = value.toInt();
		SESSION->viewport->playback_delta_time = 1.0 / SESSION->samples;
	});

	mode->toggle();
}
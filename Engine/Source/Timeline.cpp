#include "Timeline.hpp"

#include "Session.hpp"

//⏮⏭⏹⏯⏩⏪⏺⏏🔁🔀🔃🔄ℹ⏴⏵

Timeline::Timeline(QWidget* parent) :
	GUI::Linear_Contents(parent)
{
	auto start_stop = new GUI::Square_Button(this);
	start_stop->setText("⏯");

	auto live = new GUI::Toggle(this);
	live->setText("Mode: Playback");

	auto samples_label = new GUI::Label(this, "Samples (Frames) per second: ");
	samples_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

	auto samples = new GUI::Int_Input(1, MAX(int), this);
	samples->setText("60");

	addWidget(start_stop);
	addWidget(live);
	addWidget(samples_label);
	addWidget(samples);
	setFixedHeight(24);

	connect(start_stop, &GUI::Square_Button::pressed, [this, start_stop]() {
		if (SESSION->playback_mode == Playback_Mode::PLAYING) {
			SESSION->playback_mode = Playback_Mode::O_STOPPED;
			start_stop->setText("🔁");
		}
		else if (SESSION->playback_mode == Playback_Mode::STOPPED) {
			SESSION->playback_mode = Playback_Mode::O_RESET;
			start_stop->setText("⏯");
		}
		else if (SESSION->playback_mode == Playback_Mode::RESET) {
			SESSION->playback_mode = Playback_Mode::PLAYING;
			start_stop->setText("⏹");

			SESSION->current_frame = 0;
			SESSION->start = NOW;
		}
	});

	connect(live, &GUI::Toggle::toggled, [this, start_stop, samples, samples_label, live](bool checked) {
		if (checked) {
			SESSION->playback_mode = Playback_Mode::REALTIME;
			SESSION->start = NOW;
			SESSION->current_frame = 0;
			live->setText("Mode: Realtime");
			start_stop->hide();
			samples_label->hide();
			samples->hide();
		}
		else {
			live->setText("Mode: Playback");
			SESSION->playback_mode = Playback_Mode::O_RESET;
			start_stop->setText("⏯");
			start_stop->show();
			samples_label->show();
			samples->show();
		}
	});

	connect(samples, &GUI::Int_Input::textChanged, [this](const QString& value) {
		SESSION->samples = value.toInt();
	});

	live->toggle();
}
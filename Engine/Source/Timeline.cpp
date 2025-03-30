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
	setFixedHeight(20);

	connect(start_stop, &GUI::Square_Button::pressed, [this, start_stop]() {
		if (SESSION->active) {
			SESSION->active = false;
			start_stop->setText("🔁");
		}
		else {
			SESSION->start = NOW;
			SESSION->active = true;
			SESSION->current_frame = 0;
			start_stop->setText("⏹");
		}
	});

	connect(live, &GUI::Toggle::toggled, [this, start_stop, samples, samples_label, live](bool checked) {
		if (checked) {
			SESSION->realtime = true;
			SESSION->start = NOW;
			SESSION->current_frame = 0;
			live->setText("Mode: Realtime");
			start_stop->hide();
			samples_label->hide();
			samples->hide();
		}
		else {
			live->setText("Mode: Playback");
			SESSION->realtime = false;
			SESSION->active = false;
			start_stop->setText("⏯");
			start_stop->show();
			samples_label->show();
			samples->show();
		}
	});

	connect(samples, &GUI::Int_Input::textChanged, [this](const QString& value) {
		SESSION->samples = value.toInt();
	});
}
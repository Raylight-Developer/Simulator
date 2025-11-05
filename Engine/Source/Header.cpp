#include "Header.hpp"

#include "Session.hpp"

Header::Header(QWidget* parent) :
	GUI::Linear_Contents(parent, QBoxLayout::Direction::LeftToRight)
{
	setFixedHeight(24);

	auto load_file = new GUI::Button(this);
	load_file->setText("Load File");

	auto save_file = new GUI::Button(this);
	save_file->setText("Save File");

	addWidget(load_file);
	addWidget(save_file);

	connect(load_file, &GUI::Button::pressed, [this]() {
		QString file_name = QFileDialog::getOpenFileName(
			this,
			"Select a File",
			"./Resources/Showcase",
			"Sim Files (*.sim)"
		);
		if (!file_name.isEmpty()) {
			FILE.loadNewFile(file_name.toStdString());
		}
	});

	connect(save_file, &GUI::Button::pressed, []() {
		FILE.saveFile(FILE.file_path);
	});
}
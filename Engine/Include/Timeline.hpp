#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

struct Timeline : GUI::Linear_Contents {
	Timestamp on_stopped;

	Timeline(QWidget* parent);
};
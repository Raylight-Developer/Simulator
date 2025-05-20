#pragma once

#include "KL.hpp"

struct Timeline : GUI::Linear_Contents {
	Timestamp on_stopped;

	Timeline(QWidget* parent);
};
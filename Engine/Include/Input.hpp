#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

class Input : public QObject {
	QSet<int> keys_held;
protected:
	bool eventFilter(QObject *obj, QEvent *event) override;
};
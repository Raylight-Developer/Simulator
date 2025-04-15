#pragma once

#include "KL.hpp"

class Input : public QObject {
	QSet<int> keys_held;
protected:
	bool eventFilter(QObject *obj, QEvent *event) override;
};
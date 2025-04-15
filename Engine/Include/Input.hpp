#pragma once

#include "KL.hpp"

class Input : public QObject {
protected:
	bool eventFilter(QObject *obj, QEvent *event) override;
};
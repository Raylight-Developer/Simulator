#pragma once

#include "Include.hpp"
#include "QT.hpp"

#include "Scripting.hpp"

class Node_Editor : public GUI::Graphics_View {
	GUI::Graphics_Scene* scene;
public:
	Node_Editor(QWidget* parent = nullptr);

	void drawBackground(QPainter* painter, const QRectF& rect) override;
};
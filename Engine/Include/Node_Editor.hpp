#pragma once

#include "Include.hpp"
#include "QT.hpp"

#include "Scripting.hpp"

class Viewport : public GUI::Graphics_View {
public:
	Viewport(QWidget* parent = nullptr);

	void drawBackground(QPainter* painter, const QRectF& rect) override;
};

class Node_Editor : public GUI::Linear_Contents {
public:
	Viewport* viewport;
	GUI::Graphics_Scene* scene;

	Node_Editor(QWidget* parent = nullptr);
};
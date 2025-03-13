#pragma once

#include "Include.hpp"
#include "QT.hpp"

#include "Scripting.hpp"
#include "Nodes.hpp"

class Node_Editor : public GUI::Graphics_View {
	GUI::Graphics_Scene* scene;

	bool moving;
	bool selecting;

	QPointF move_pos;
	QPointF selection_start;
	QGraphicsRectItem* selection_rect;
	NODE::Connection* creating_connection;
public:
	vector<NODE::Node*> selection;

	Node_Editor(QWidget* parent = nullptr);
	~Node_Editor();

	void drawBackground(QPainter* painter, const QRectF& rect) override;

	void mouseReleaseEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override; // TODO Fix sticky mouse, double clicks and odd non-registering behaviors
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

	void dragMoveEvent(QDragMoveEvent* event) override;
	void dropEvent(QDropEvent* event) override;
};
#include "Node_Editor.hpp"

#include "Session.hpp"

Viewport::Viewport(QWidget* parent) :
	GUI::Graphics_View(parent)
{}

void Viewport::drawBackground(QPainter* painter, const QRectF& rect) {
	// Call the base class to draw the background
	QGraphicsView::drawBackground(painter, rect);

	// Set grid line color and style
	QPen gridPen(Qt::lightGray, 0.5);
	painter->setPen(gridPen);

	// Draw vertical grid lines
	qreal left = int(rect.left()) - int(rect.left()) % 50;
	qreal right = int(rect.right()) - int(rect.right()) % 50;
	for (qreal x = left; x <= right; x += 50) {
		painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
	}

	// Draw horizontal grid lines
	qreal top = int(rect.top()) - int(rect.top()) % 50;
	qreal bottom = int(rect.bottom()) - int(rect.bottom()) % 50;
	for (qreal y = top; y <= bottom; y += 50) {
		painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
	}
}

Node_Editor::Node_Editor(QWidget* parent) :
	GUI::Linear_Contents(parent)
{
	viewport = new Viewport(this);
	scene = new GUI::Graphics_Scene(viewport);
	viewport->setScene(scene);

	addWidget(viewport);
}
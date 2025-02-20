#include "Node_Editor.hpp"

#include "Session.hpp"

Node_Editor::Node_Editor(QWidget* parent) :
	GUI::Graphics_View(parent)
{
	scene = new GUI::Graphics_Scene(this);
	setScene(scene);
}

void Node_Editor::drawBackground(QPainter* painter, const QRectF& rect) {
	QGraphicsView::drawBackground(painter, rect);

	constexpr qreal smallGridSpacing = 10.0;
	constexpr qreal majorGridSpacing = smallGridSpacing * 10;

	qreal left = int(rect.left()) - int(rect.left()) % int(smallGridSpacing);
	qreal right = int(rect.right());
	qreal top = int(rect.top()) - int(rect.top()) % int(smallGridSpacing);
	qreal bottom = int(rect.bottom());

	if (transform().m11() > 0.6) {
		for (qreal x = left; x <= right; x += smallGridSpacing) {
			bool isMajorLine = (int(x) % int(majorGridSpacing) == 0);
			QPen gridPen(isMajorLine ? QColor(255, 255, 255) : QColor(150, 150, 150), isMajorLine ? 0.2 : 0.1);
			painter->setPen(gridPen);
			painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
		}

		for (qreal y = top; y <= bottom; y += smallGridSpacing) {
			bool isMajorLine = (int(y) % int(majorGridSpacing) == 0);
			QPen gridPen(isMajorLine ? QColor(255, 255, 255) : QColor(150, 150, 150), isMajorLine ? 0.2 : 0.1);
			painter->setPen(gridPen);
			painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
		}
	}
	else {
		for (qreal x = left; x <= right; x += majorGridSpacing) {
			QPen gridPen(QColor(150, 150, 150), 0.6);
			painter->setPen(gridPen);
			painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
		}

		for (qreal y = top; y <= bottom; y += majorGridSpacing) {
			QPen gridPen(QColor(150, 150, 150), 0.6);
			painter->setPen(gridPen);
			painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
		}
	}
}
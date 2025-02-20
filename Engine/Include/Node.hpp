#pragma once

#include "Include.hpp"

#include "Variable.hpp"

namespace NODE {
	struct Node;
	struct Port;

	struct Node : QGraphicsItem {
		QString label;
		QRectF rect;

		vector<Port*> children;

		Node(const QString& label = "NODE");
		~Node();

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		QRectF boundingRect() const override;;
	};

	struct Port : QGraphicsItem {
		Node* node;

		QRectF rect;
		QColor color;
		QString label;

		Port(Node* node);

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;;
		QRectF boundingRect() const override;;
	};

	struct Connection : QGraphicsItem {
		Port* port_l;
		Port* port_r;
		QPointF pos_l;
		QPointF pos_r;

		Connection(Port* port_l, Port* port_r);
		~Connection();

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		QRectF boundingRect() const override;

		void updateL(const QPointF& point);
		void updateR(const QPointF& point);
	};

	namespace PORT {
		struct Exec_I : Port {
			QString label;

			vector<Connection*> connections;

			Exec_I(Node* parent, const QString& label);
			~Exec_I();

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Exec_O : Port {
			QString label;

			Connection* connection;

			Exec_O(Node* parent, const QString& label);
			~Exec_O();

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Data_I : Port {
			QString label;
			QColor color;

			VARIABLE::Modifier modifier;
			VARIABLE::Type type;
			Variable variable;

			Connection* connection;

			Data_I(Node* parent, const QString& label, const VARIABLE::Type& type, const VARIABLE::Modifier& modifier);
			~Data_I();

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Data_O : Port {
			QString label;
			QColor color;

			VARIABLE::Modifier modifier;
			VARIABLE::Type type;

			vector<Connection*> connections;

			Data_O(Node* parent, const QString& label, const VARIABLE::Type& type, const VARIABLE::Modifier& modifier);
			~Data_O();

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

	}
}
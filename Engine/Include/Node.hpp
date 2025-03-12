#pragma once

#include "Include.hpp"

#include "Variable.hpp"

namespace NODE {
	struct Node;
	struct Port;
	struct Connection;
	namespace PORT {
		struct Data_I;
		struct Exec_I;
		struct Data_O;
		struct Exec_O;
	}

	struct Node : QGraphicsItem {
		QString label;
		QRectF rect;

		vector<Node*> children;
		vector<Port*> inputs;
		vector<Port*> outputs;

		Node(const QString& label = "NODE");
		~Node();

		virtual void exec(const Port* port) {}
		virtual Variable getData(const Port* port) const { return Variable(); };

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		QRectF boundingRect() const override;
	};

	struct Port : QGraphicsItem {
		Node* node;

		QRectF rect;
		QColor color;
		QString label;

		Port(Node* node);

		function<bool(Connection*)> conn_request;
		function<void(Connection*)> disconnection;
		bool onConnRequested(Connection* connection);
		void onDisconnected(Connection* connection);

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;;
		QRectF boundingRect() const override;
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

		PORT::Exec_I* getExecI() const;
		PORT::Exec_O* getExecO() const;
		PORT::Data_I* getDataI() const;
		PORT::Data_O* getDataO() const;
	};

	namespace PORT {
		struct Exec_I : Port {
			const QString label;

			vector<Connection*> connections;

			Exec_I(Node* parent, const QString& label);
			~Exec_I();

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Exec_O : Port {
			const QString label;

			Connection* connection;

			Exec_O(Node* parent, const QString& label);
			~Exec_O();

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Data_I : Port {
			const QString label;

			VARIABLE::Type type;
			Variable variable;
			QColor color;

			Connection* connection;

			Data_I(Node* parent, const QString& label);
			Data_I(Node* parent, const QString& label, const VARIABLE::Type& type);
			~Data_I();

			Variable getData() const;

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Data_O : Port {
			const QString label;

			VARIABLE::Type type;
			QColor color;

			vector<Connection*> connections;

			Data_O(Node* parent, const QString& label);
			Data_O(Node* parent, const QString& label, const VARIABLE::Type& type);
			~Data_O();

			Variable getData() const;

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

	}
}
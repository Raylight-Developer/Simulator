#pragma once

#include "KL.hpp"

#include "Variable.hpp"

struct Node;
namespace NODE {
	struct Port;
	struct Connection;
	namespace PORT {
		struct Data_I;
		struct Exec_I;
		struct Data_O;
		struct Exec_O;
	}
}

struct Node : QGraphicsItem {
	QColor header_color;
	QString label;
	QRectF rect;

	vector<Node*> children;
	vector<NODE::Port*> inputs;
	vector<NODE::Port*> outputs;

	Node(const QString& label = "NODE");
	~Node();

	virtual void exec(const NODE::Port* port) {}
	virtual Variable getData(const NODE::Port* port) const { return Variable(); };

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QRectF boundingRect() const override;
};

namespace NODE {
	struct Port : QGraphicsItem {
		Node* node;

		QRectF rect;

		Port(Node* node);

		function<bool(Port*, Connection*)> onConnRequested;
		function<void(Port*)> onDisconnection;
		virtual bool requestConnection(Connection* connection);
		void disconnect();

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;;
		QRectF boundingRect() const override;
	};

	struct Connection : QGraphicsItem {
		Port* port_l;
		Port* port_r;
		QPointF pos_l;
		QPointF pos_r;

		QColor color;
		vector<QGraphicsItem*> reroutes;

		Connection(Port* source_port);
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
			bool connected() const;

			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Exec_O : Port {
			const QString label;

			Connection* connection;

			Exec_O(Node* parent, const QString& label);
			~Exec_O();
			bool connected() const;

			void exec() const;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Data_I : Port {
			const QString label;

			VARIABLE::Type var_type;
			Variable variable;
			QColor color;

			Connection* connection;

			Data_I(Node* parent, const QString& label);
			Data_I(Node* parent, const QString& label, const VARIABLE::Type& var_type);
			~Data_I();
			bool connected() const;

			function<void(Port*, const VARIABLE::Type&)> onTypeChanged;
			void setType(const VARIABLE::Type& var_type);
			const Variable& getData() const;

			bool requestConnection(Connection* connection) override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Data_O : Port {
			const QString label;

			VARIABLE::Type var_type;
			QColor color;

			vector<Connection*> connections;

			Data_O(Node* parent, const QString& label);
			Data_O(Node* parent, const QString& label, const VARIABLE::Type& var_type);
			~Data_O();
			bool connected() const;

			function<void(Port*, const VARIABLE::Type&)> onTypeChanged;
			void setType(const VARIABLE::Type& var_type);
			Variable getData() const;

			bool requestConnection(Connection* connection) override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};
	}
}
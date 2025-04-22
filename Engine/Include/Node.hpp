#pragma once

#include "KL.hpp"

#include "Variable.hpp"

struct Node;
namespace NODE {
	struct Port;
	struct Connection;
	namespace PORT {
		struct Data_I;
		struct Data_O;
		struct Exec_O;
		struct Exec_I;
	}
}

enum Graphics_Item_Type {
	E_NODE   = QGraphicsItem::UserType + 1,
	E_CONN   = QGraphicsItem::UserType + 2,
	E_DATA_I = QGraphicsItem::UserType + 3,
	E_DATA_O = QGraphicsItem::UserType + 4,
	E_EXEC_O = QGraphicsItem::UserType + 5,
	E_EXEC_I = QGraphicsItem::UserType + 6
};
#define IS_PORT(type) type >= Graphics_Item_Type::E_DATA_I and type <= Graphics_Item_Type::E_EXEC_I

struct Node : Self<Node>, QGraphicsItem {
	QColor header_color;
	QString node_type;
	QString label;
	QRectF rect;

	CORE::Stack<NODE::Port*> inputs;
	CORE::Stack<NODE::Port*> outputs;

	Node();
	Node(const QString& node_type, const QString& label);
	~Node();

	virtual void exec(const NODE::Port* port) {}
	virtual Variable getData(const NODE::Port* port) const { return Variable(); };

	virtual void save(CORE::Lace& lace, const U64& index) const;
	static tuple<Node*, U64> load(const Token_Array& tokens);

	int type() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QRectF boundingRect() const override;
};

namespace NODE {
	struct Port : QGraphicsItem {
		Node* node;
		QRectF rect;

		function<bool(Port*, Connection*)> onConnRequested;
		function<void(Port*)> onDisconnection;

		Port(Node* node);

		virtual bool requestConnection(Connection* connection);
		virtual bool connected() const = 0;
		virtual void disconnect() = 0;

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;;
		QRectF boundingRect() const override;
	};

	struct Connection : QGraphicsItem {
		Port* port_l;
		Port* port_r;
		QPointF pos_l;
		QPointF pos_r;

		QColor color;
		CORE::Stack<QGraphicsItem*> reroutes;

		Connection(Port* source_port);
		Connection(Port* port_l, Port* port_r);

		int type() const override;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		QRectF boundingRect() const override;

		void updateL(const QPointF& point);
		void updateR(const QPointF& point);

		PORT::Data_I* getDataI() const;
		PORT::Data_O* getDataO() const;
		PORT::Exec_O* getExecO() const;
		PORT::Exec_I* getExecI() const;
	};

	namespace PORT {
		struct Data_I : Port {
			const QString label;

			VARIABLE::Type var_type;
			Variable variable;
			QColor color;

			Ptr_U<Connection> connection;

			Data_I(Node* parent, const QString& label);
			Data_I(Node* parent, const QString& label, const VARIABLE::Type& var_type);
			Data_I(Node* parent, const QString& label, const Variable& default_variable);
			~Data_I();

			bool canConnect(Data_O* port);
			void connect(Data_O* port);
			void disconnect() final override;
			bool connected() const final override;

			function<void(Port*, const VARIABLE::Type&)> onTypeChanged;
			void setType(const VARIABLE::Type& var_type);
			Variable getData() const;
			bool requestConnection(Connection* connection) override;

			int type() const override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Data_O : Port {
			const QString label;

			VARIABLE::Type var_type;
			QColor color;

			CORE::Stack<Connection*> connections;

			Data_O(Node* parent, const QString& label);
			Data_O(Node* parent, const QString& label, const VARIABLE::Type& var_type);
			~Data_O();

			void disconnect() final override;
			bool connected() const final override;

			function<void(Port*, const VARIABLE::Type&)> onTypeChanged;
			void setType(const VARIABLE::Type& var_type);
			Variable getData() const;
			bool requestConnection(Connection* connection) override;

			int type() const override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Exec_O : Port {
			const QString label;

			Ptr_U<Connection> connection;

			Exec_O(Node* parent, const QString& label);
			~Exec_O();

			bool canConnect(Exec_I* port);
			void connect(Exec_I* port);
			void disconnect() final override;
			bool connected() const final override;

			void exec() const;

			int type() const override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Exec_I : Port {
			const QString label;

			CORE::Stack<Connection*> connections;

			Exec_I(Node* parent, const QString& label);
			~Exec_I();

			void disconnect() final override;
			bool connected() const final override;

			int type() const override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};
	}
}

#define DATA_I(label, type) make_unique<PORT::Data_I>(this, label, type)
#define DATA_O(label, type) make_unique<PORT::Data_O>(this, label, type)
#define EXEC_O(label) make_unique<PORT::Exec_O>(this, label)
#define EXEC_I(label) make_unique<PORT::Exec_I>(this, label)

#define PORT_DATA_I Ptr_U<PORT::Data_I>
#define PORT_DATA_O Ptr_U<PORT::Data_O>
#define PORT_EXEC_O Ptr_U<PORT::Exec_O>
#define PORT_EXEC_I Ptr_U<PORT::Exec_I>

#define PROXY(widget) auto* proxy_##widget = new GUI::Graphics_Widget(widget, this)
#define GET_DATA(type) getData().get<type>()
#pragma once

#include "KL.hpp"

#include "Variable.hpp"

struct File;
namespace NODES {
	enum struct Node_Type;
}

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
	const NODES::Node_Type node_type;
	QColor header_color;
	QString label;
	QRectF rect;

	CORE::Stack<NODE::Port*> inputs;
	CORE::Stack<NODE::Port*> outputs;

	Node();
	Node(const NODES::Node_Type& node_type, const QString& label);
	~Node();

	// TODO linker error if virtual functions are defined in Node.cpp

	virtual void exec(const NODE::Port* port) {}
	virtual Ptr_S<Variable> getData(const NODE::Port* port) { return nullptr; };

	void save(CORE::Lace& lace, const U64& index) const;
	static void load(File* file, const Token_Array& tokens);
	virtual void saveDetail(CORE::Lace& lace) const {};
	virtual void loadDetail(const Token_Array& tokens) {};

	int type() const final override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QRectF boundingRect() const override;
};

namespace NODE {
	struct Port : QGraphicsItem {
		Node* node;
		QRectF rect;

		function<bool(Port*, Connection*)> onConnection;
		function<void(Port*)> onDisconnection;

		Port(Node* node);

		virtual bool connected() const = 0;
		virtual void disconnect() = 0;

		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		QRectF boundingRect() const override;
	};

	struct Connection : QGraphicsItem {
		Port* port_l;
		Port* port_r;
		QPointF pos_l;
		QPointF pos_r;

		QColor color;

		Connection(Port* source_port);
		Connection(Port* port_l, Port* port_r);

		int type() const final override;
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

			Ptr_S<Variable> variable;
			QColor color;

			Ptr_U<Connection> connection;

			Data_I(Node* parent, const QString& label);
			Data_I(Node* parent, const QString& label, const VAR_TYPE& var_type, const VAR_CONTAINER& var_container = VAR_CONTAINER::NONE);
			Data_I(Node* parent, const QString& label, const Variable& default_variable);
			~Data_I();

			void connect(Data_O* port);
			void disconnect() final override;
			bool connected() const final override;

			void setType(const VAR_TYPE& var_type, const VAR_CONTAINER& var_container);

			Ptr_S<Variable> getData();

			int type() const final override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Data_O : Port {
			const QString label;

			VAR_TYPE var_type;
			VAR_CONTAINER var_container;
			QColor color;

			CORE::Stack<Connection*> connections;

			Data_O(Node* parent, const QString& label);
			Data_O(Node* parent, const QString& label, const VAR_TYPE& var_type, const VAR_CONTAINER& var_container = VAR_CONTAINER::NONE);
			~Data_O();

			void disconnect() final override;
			bool connected() const final override;

			void setType(const VAR_TYPE& var_type, const VAR_CONTAINER& var_container);

			Ptr_S<Variable> getData();

			int type() const final override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Exec_O : Port {
			const QString label;

			Ptr_U<Connection> connection;

			Exec_O(Node* parent, const QString& label);
			~Exec_O();

			void connect(Exec_I* port);
			void disconnect() final override;
			bool connected() const final override;

			void exec() const;

			int type() const final override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};

		struct Exec_I : Port {
			const QString label;

			CORE::Stack<Connection*> connections;

			Exec_I(Node* parent, const QString& label);
			~Exec_I();

			void disconnect() final override;
			bool connected() const final override;

			int type() const final override;
			void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
		};
	}
}

#define DATA_I(label, type) make_unique<NODE::PORT::Data_I>(this, label, type)
#define DATA_O(label, type) make_unique<NODE::PORT::Data_O>(this, label, type)

#define DATA_I_C(label, type, container) make_unique<NODE::PORT::Data_I>(this, label, type, container)
#define DATA_O_C(label, type, container) make_unique<NODE::PORT::Data_O>(this, label, type, container)

#define EXEC_O(label) make_unique<NODE::PORT::Exec_O>(this, label)
#define EXEC_I(label) make_unique<NODE::PORT::Exec_I>(this, label)

#define PORT_DATA_I Ptr_U<NODE::PORT::Data_I>
#define PORT_DATA_O Ptr_U<NODE::PORT::Data_O>
#define PORT_EXEC_O Ptr_U<NODE::PORT::Exec_O>
#define PORT_EXEC_I Ptr_U<NODE::PORT::Exec_I>

#define PROXY(widget) auto* proxy_##widget = new GUI::Graphics_Widget(widget, this)
#define GET_DATA(type) getData()->get<type>()
#define GET_LIST(type) getData()->get<CORE::Stack< type >>()

namespace NODES {
	enum struct Node_Type {
		NONE                   = QGraphicsItem::UserType + 1,
		SCRIPT                 ,
		VARIABLE_CONSTANT      ,
		VARIABLE_GET           ,
		VARIABLE_SET           ,
		MATH_TRIGONOMETRIC     ,
		MATH_ARITHMETIC        ,
		BOOLEAN_COMPARE        ,
		BOOLEAN_SELECT         ,
		EXEC_SUBSAMPLE         ,
		EXEC_IF_ELSE           ,
		EXEC_IF                ,
		HOOK_INPUT_MOUSE_WHEEL ,
		HOOK_INPUT_MOUSE_POS   ,
		HOOK_INPUT_MOUSE       ,
		HOOK_INPUT_KEY         ,
		HOOK_DISPLAY           ,
		SINGLETON_EULER_TICK   ,
		SINGLETON_BACKGROUND   ,
		SINGLETON_2D_CAMERA    ,
		SINGLETON_3D_CAMERA    ,
		SINGLETON_RESET        ,
		RENDER_2D_RECTANGLE    ,
		RENDER_2D_TRIANGLE     ,
		RENDER_2D_CIRCLE       ,
		RENDER_2D_LINE         
	};
}
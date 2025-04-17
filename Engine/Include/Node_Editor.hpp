#pragma once

#include "KL.hpp"

#include "Scripting.hpp"
#include "Nodes.hpp"

struct Node_Editor : GUI::Graphics_View {
	GUI::Graphics_Scene* scene;

	bool moving;
	bool selecting;

	QPointF l_mouse_down;
	CORE::UMap<Node*, QPointF> node_move_start_pos;

	QPointF selection_start;
	QGraphicsRectItem* selection_rect;
	Ptr_U<NODE::Connection> creating_connection;

	vector<Node*> selection;

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

	void addNode(Ptr_S<Node> node, const F64_V2& pos);
	void moveNode(Ptr_S<Node> node, const F64_V2& new_pos);
	void deleteNode(Ptr_S<Node> node);

	void connectPorts(Port* port_l, Port* port_r);
	void disconnectPort(Port* port);

	void h_addNode(Ptr_S<Node> node, const F64_V2& pos);
	void h_moveNode(Ptr_S<Node> node, const F64_V2& from, const F64_V2& to);
	void h_deleteNode(Ptr_S<Node> node);

	void h_connectPorts(Port* port_l, Port* port_r);
	void h_disconnectPort(Port* port);

	struct Add_Node : Self<Add_Node>, CORE::CMD {
		Ptr_S<Node> node;
		F64_V2 pos;

		Add_Node(Ptr_S<Node> node, const F64_V2& pos);

		void execute() const final override;
		void undo() final override;
	};
	struct Move_Node : Self<Move_Node>, CORE::CMD {
		Ptr_S<Node> node;
		F64_V2 from, to;

		Move_Node(Ptr_S<Node> node, const F64_V2& from, const F64_V2& to);

		void execute() const final override;
		void undo() final override;
	};
	struct Delete_Node : Self<Delete_Node>, CORE::CMD {
		Ptr_S<Node> node;
		F64_V2 pos;

		Delete_Node(Ptr_S<Node> node);

		void execute() const final override;
		void undo() final override;
	};

	struct Connect : Self<Connect>, CORE::CMD {
		Port* port_l;
		Port* port_r;

		Connect(Port* port_l, Port* port_r);

		void execute() const final override;
		void undo() final override;
	};
	struct Disconnect : Self<Disconnect>, CORE::CMD {
		Port* port;
		CORE::Stack<Port*> connections;
		//TODO
		Disconnect(Port* port);

		void execute() const final override;
		void undo() final override;
	};
	struct Set_Variable : Self<Set_Variable>, CORE::CMD {
		//TODO
		void execute() const final override;
		void undo() final override;
	};
};

static Node_Editor* editor_ptr;
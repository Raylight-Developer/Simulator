#pragma once

#include "KL.hpp"

#include "Scripting.hpp"
#include "Nodes.hpp"

class Node_Editor : public GUI::Graphics_View {
	GUI::Graphics_Scene* scene;

	bool moving;
	bool selecting;

	QPointF l_mouse_down;
	CORE::UMap<Node*, QPointF> node_move_start_pos;

	QPointF selection_start;
	QGraphicsRectItem* selection_rect;
	NODE::Connection* creating_connection;
public:
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

	void h_addNode(Ptr_S<Node> node, const F64_V2& pos);
	void h_moveNode(Ptr_S<Node> node, const F64_V2& from, const F64_V2& to);
	void h_deleteNode(Ptr_S<Node> node);

	struct Add_Node : Self<Add_Node>, CORE::CMD {
		Node_Editor* editor;
		Ptr_S<Node> node;
		F64_V2 pos;

		Add_Node(Ptr_S<Node> node, Node_Editor* editor, const F64_V2& pos);

		void execute() const final override;
		void undo() final override;
	};
	struct Move_Node : Self<Move_Node>, CORE::CMD {
		Node_Editor* editor;
		Ptr_S<Node> node;
		F64_V2 from, to;

		Move_Node(Ptr_S<Node> node, Node_Editor* editor, const F64_V2& from, const F64_V2& to);

		void execute() const final override;
		void undo() final override;
	};
	struct Delete_Node : Self<Delete_Node>, CORE::CMD {
		Node_Editor* editor;
		Ptr_S<Node> node;
		F64_V2 pos;

		Delete_Node(Ptr_S<Node> node, Node_Editor* editor);

		void execute() const final override;
		void undo() final override;
	};

	struct Connect_Port : Self<Connect_Port>, CORE::CMD {
	};
	struct Disconnect_Port : Self<Disconnect_Port>, CORE::CMD {
	};

	struct Set_Variable : Self<Set_Variable>, CORE::CMD {
	};
};
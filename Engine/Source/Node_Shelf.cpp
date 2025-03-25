#include "Node_Shelf.hpp"

Node_Shelf::Node_Shelf(QWidget* parent) :
	GUI::Linear_Contents(parent, QBoxLayout::Direction::TopToBottom)
{
	tree = new NODE_SHELF::Tree(this);
	addWidget(tree);
}

NODE_SHELF::Tree::Tree(Node_Shelf* parent) :
	GUI::Tree(parent)
{
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDropMode::DragOnly);

	auto tree_math      = new GUI::Tree_Item(this, "Math");
	auto tree_inputs    = new GUI::Tree_Item(this, "Inputs");
	auto tree_cast      = new GUI::Tree_Item(this, "Casting");
	auto tree_exec      = new GUI::Tree_Item(this, "Exec");
	auto tree_render    = new GUI::Tree_Item(this, "Rendering");

	auto tree_make      = new GUI::Tree_Item(tree_cast, "Make", 1);
	auto tree_break     = new GUI::Tree_Item(tree_cast, "Break", 1);

	auto tree_render_2d = new GUI::Tree_Item(tree_render, "2D Rendering", 1);
	auto tree_render_3d = new GUI::Tree_Item(tree_render, "3D Rendering", 1);

	auto arithmetic     = new GUI::Tree_Item(tree_math, "Arithmetic"  , 1, { { 1000, "ARITHMETIC"   } });
	auto trigonometry   = new GUI::Tree_Item(tree_math, "Trigonometry", 1, { { 1000, "TRIGONOMETRY" } });

	auto input_int      = new GUI::Tree_Item(tree_inputs, "Integer", 2, { { 1000, "INPUT INTEGER" } });
	auto input_double   = new GUI::Tree_Item(tree_inputs, "Double" , 2, { { 1000, "INPUT DOUBLE"  } });
	auto input_bool     = new GUI::Tree_Item(tree_inputs, "Bool"   , 2, { { 1000, "INPUT BOOL"    } });
	auto input_string   = new GUI::Tree_Item(tree_inputs, "String" , 2, { { 1000, "INPUT STRING"  } });
	auto input_vec2     = new GUI::Tree_Item(tree_inputs, "Vec 2"  , 2, { { 1000, "INPUT VEC2"    } });
	auto input_vec3     = new GUI::Tree_Item(tree_inputs, "Vec 3"  , 2, { { 1000, "INPUT VEC3"    } });
	auto input_vec4     = new GUI::Tree_Item(tree_inputs, "Vec 4"  , 2, { { 1000, "INPUT VEC4"    } });

	auto make_vec2      = new GUI::Tree_Item(tree_make, "Vec 2", 2, { { 1000, "MAKE VEC2" } });
	auto make_vec3      = new GUI::Tree_Item(tree_make, "Vec 3", 2, { { 1000, "MAKE VEC3" } });
	auto make_vec4      = new GUI::Tree_Item(tree_make, "Vec 4", 2, { { 1000, "MAKE VEC4" } });
	auto make_quat      = new GUI::Tree_Item(tree_make, "Quat" , 2, { { 1000, "MAKE QUAT" } });
	auto make_mat2      = new GUI::Tree_Item(tree_make, "Mat 2", 2, { { 1000, "MAKE MAT2" } });
	auto make_mat3      = new GUI::Tree_Item(tree_make, "Mat 3", 2, { { 1000, "MAKE MAT3" } });
	auto make_mat4      = new GUI::Tree_Item(tree_make, "Mat 4", 2, { { 1000, "MAKE MAT4" } });

	//auto euler_tick     = new GUI::Tree_Item(tree_exec, "Euler Tick", 2, { { 1000, "EULER TICK" } });

	auto render_2d_line      = new GUI::Tree_Item(tree_render_2d, "Line"     , 2, { { 1000, "RENDER 2D LINE"      } });
	auto render_2d_triangle  = new GUI::Tree_Item(tree_render_2d, "Triangle" , 2, { { 1000, "RENDER 2D TRIANGLE"  } });
	auto render_2d_rectangle = new GUI::Tree_Item(tree_render_2d, "Rectangle", 2, { { 1000, "RENDER 2D RECTANGLE" } });
	auto render_2d_circle    = new GUI::Tree_Item(tree_render_2d, "Circle"   , 2, { { 1000, "RENDER 2D CIRCLE"    } });

	expandAll();
}

void NODE_SHELF::Tree::startDrag(Qt::DropActions actions) {
	if (QTreeWidgetItem* temp = currentItem()) {

		QMimeData* mimeData = new QMimeData;
		mimeData->setText("NODE");

		QByteArray type;
		QDataStream dataStreamType(&type, QIODevice::WriteOnly);
		dataStreamType << temp->data(0, 1000).toString();
		mimeData->setData("Type", type);

		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->exec(Qt::MoveAction);
	}
}
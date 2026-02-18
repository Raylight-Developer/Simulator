#include "Node_Shelf.hpp"

#include "Session.hpp"

Node_Shelf::Node_Shelf(QWidget* parent) :
	GUI::Linear_Contents(parent, QBoxLayout::Direction::TopToBottom)
{
	auto add_script = new GUI::Button(this);
	add_script->setText("Load C++ Script");
	addWidget(add_script);

	tree = new NODE_SHELF::Tree(this);
	addWidget(tree);

	connect(add_script, &GUI::Button::pressed, [this]() {
		const QString script_id = QInputDialog::getText(nullptr, "Add Script", "Enter Script ID:");
		if (!script_id.isEmpty()) {
			const QString script_path = QFileDialog::getOpenFileName(nullptr, "Open Script DLL File", "", "Dll Files (*.dll)");
			if (!script_path.isEmpty()) {
				new GUI::Tree_Item(tree->user_scripts, script_id, 1, { { 1000, "SCRIPT" }, { 1001, script_path } });
			}
		}
	});
}

NODE_SHELF::Tree::Tree(Node_Shelf* parent) :
	GUI::Tree(parent)
{
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDropMode::DragOnly);

	user_scripts = new GUI::Tree_Item(this, "Scripts");

	auto tree_included = new GUI::Tree_Item(user_scripts, "Included", 1);
	{
		new GUI::Tree_Item(tree_included, "Camera Controller", 2, { {1000, "SCRIPT"}, { 1001, "./Script-Camera-Controller.dll" } });
		new GUI::Tree_Item(tree_included, "GUI Fps"          , 2, { {1000, "SCRIPT"}, { 1001, "./Script-GUI-Fps.dll"           } });
	}

	auto tree_showcase = new GUI::Tree_Item(user_scripts, "Showcase", 1);
	{
		new GUI::Tree_Item(tree_showcase, "Controllable Object", 2, { {1000, "SCRIPT"}, { 1001, "./Script-Controllable-Object-Showcase.dll" } });
		new GUI::Tree_Item(tree_showcase, "Particles"          , 2, { {1000, "SCRIPT"}, { 1001, "./Script-Particle-Showcase.dll"            } });
		new GUI::Tree_Item(tree_showcase, "Newton"             , 2, { {1000, "SCRIPT"}, { 1001, "./Script-Newtons-Cradle.dll"               } });
		new GUI::Tree_Item(tree_showcase, "Boids"              , 2, { {1000, "SCRIPT"}, { 1001, "./Script-Boid-Showcase.dll"                } });
		new GUI::Tree_Item(tree_showcase, "SVG"                , 2, { {1000, "SCRIPT"}, { 1001, "./Script-SVG-Art-Showcase.dll"             } });
	}

	auto tree_variables = new GUI::Tree_Item(this, "Variables");
	{
		new GUI::Tree_Item(tree_variables, "Constant", 1, { { 1000, "VARIABLE CONSTANT" } });
		new GUI::Tree_Item(tree_variables, "Set"     , 1, { { 1000, "VARIABLE SET"      } });
		new GUI::Tree_Item(tree_variables, "Get"     , 1, { { 1000, "VARIABLE GET"      } });
	}

	auto tree_cast = new GUI::Tree_Item(this, "Casting");
	{
		auto tree_convert = new GUI::Tree_Item(tree_cast, "Convert", 1);
		{
			new GUI::Tree_Item(tree_convert, "Int -> Double", 2, { { 1000, "CAST CONVERT I64 TO F64" } });
		}
		auto tree_break = new GUI::Tree_Item(tree_cast, "Break", 1);
		{
			new GUI::Tree_Item(tree_break, "Vec2", 2, { { 1000, "CAST BREAK VEC2"  } });
		}
		auto tree_make = new GUI::Tree_Item(tree_cast, "Make", 1);
		{
			new GUI::Tree_Item(tree_make, "Color", 2, { { 1000, "CAST MAKE COLOR" } });
			new GUI::Tree_Item(tree_make, "Vec2" , 2, { { 1000, "CAST MAKE VEC2"  } });
			new GUI::Tree_Item(tree_make, "Vec3" , 2, { { 1000, "CAST MAKE VEC3"  } });
			new GUI::Tree_Item(tree_make, "Vec4" , 2, { { 1000, "CAST MAKE VEC4"  } });
			new GUI::Tree_Item(tree_make, "Quat" , 2, { { 1000, "CAST MAKE QUAT"  } });
			new GUI::Tree_Item(tree_make, "Mat2" , 2, { { 1000, "CAST MAKE MAT2"  } });
			new GUI::Tree_Item(tree_make, "Mat3" , 2, { { 1000, "CAST MAKE MAT3"  } });
			new GUI::Tree_Item(tree_make, "Mat4" , 2, { { 1000, "CAST MAKE MAT4"  } });
		}
	}

	auto tree_math = new GUI::Tree_Item(this, "Math");
	{
		new GUI::Tree_Item(tree_math, "Arithmetic"  , 1, { { 1000, "MATH ARITHMETIC"   } });
		new GUI::Tree_Item(tree_math, "Trigonometry", 1, { { 1000, "MATH TRIGONOMETRY" } });
	}

	auto tree_boolean = new GUI::Tree_Item(this, "Boolean");
	{
		new GUI::Tree_Item(tree_boolean, "Comparison", 1, { { 1000, "BOOLEAN COMPARISON" } });
		new GUI::Tree_Item(tree_boolean, "Select"    , 1, { { 1000, "BOOLEAN SELECT"     } });
	}

	auto tree_container = new GUI::Tree_Item(this, "Container");
	{
		auto tree_list = new GUI::Tree_Item(tree_container, "List", 1);
		{
			new GUI::Tree_Item(tree_list, "Access", 2, { { 1000, "CONTAINER LIST ACCESS" } });
			new GUI::Tree_Item(tree_list, "Create", 2, { { 1000, "CONTAINER LIST CREATE" } });
			new GUI::Tree_Item(tree_list, "Insert", 2, { { 1000, "CONTAINER LIST INSERT" } });
			new GUI::Tree_Item(tree_list, "Modify", 2, { { 1000, "CONTAINER LIST MODIFY" } });
			new GUI::Tree_Item(tree_list, "Remove", 2, { { 1000, "CONTAINER LIST REMOVE" } });
			new GUI::Tree_Item(tree_list, "Clear" , 2, { { 1000, "CONTAINER LIST CLEAR"  } });
			new GUI::Tree_Item(tree_list, "Push"  , 2, { { 1000, "CONTAINER LIST PUSH"   } });
			new GUI::Tree_Item(tree_list, "Size"  , 2, { { 1000, "CONTAINER LIST SIZE"   } });
		}
	}

	auto tree_exec = new GUI::Tree_Item(this, "Exec");
	{
		auto tree_loop = new GUI::Tree_Item(tree_exec, "Loop", 1);
		{
			new GUI::Tree_Item(tree_loop, "Subsample" , 2, { { 1000, "EXEC LOOP SUBSAMPLE" } });
			new GUI::Tree_Item(tree_loop, "While"     , 2, { { 1000, "EXEC LOOP WHILE"     } });
			new GUI::Tree_Item(tree_loop, "For"       , 2, { { 1000, "EXEC LOOP FOR"       } });
		}
		new GUI::Tree_Item(tree_exec, "If Else"    , 1, { { 1000, "EXEC IF ELSE"    } });
		new GUI::Tree_Item(tree_exec, "If"         , 1, { { 1000, "EXEC IF"         } });
	}

	auto tree_singleton = new GUI::Tree_Item(this, "Singletons");
	{
		new GUI::Tree_Item(tree_singleton, "Render Background", 1, { { 1000, "SINGLETON BACKGROUND" } });
		new GUI::Tree_Item(tree_singleton, "Euler Tick"       , 1, { { 1000, "SINGLETON EULER TICK" } });
		new GUI::Tree_Item(tree_singleton, "Camera 2D"        , 1, { { 1000, "SINGLETON 2D CAMERA"  } });
		new GUI::Tree_Item(tree_singleton, "Camera 3D"        , 1, { { 1000, "SINGLETON 3D CAMERA"  } });
		new GUI::Tree_Item(tree_singleton, "Init Scene"       , 1, { { 1000, "SINGLETON INIT"       } });
	}

	auto tree_hooks = new GUI::Tree_Item(this, "Hooks");
	{
		auto tree_inputs = new GUI::Tree_Item(tree_hooks, "Inputs", 1);
		{
			new GUI::Tree_Item(tree_inputs, "Key"        , 2, { { 1000, "HOOK INPUT KEY"         } });
			new GUI::Tree_Item(tree_inputs, "Mouse"      , 2, { { 1000, "HOOK INPUT MOUSE"       } });
			new GUI::Tree_Item(tree_inputs, "Mouse Pos"  , 2, { { 1000, "HOOK INPUT MOUSE POS"   } });
			new GUI::Tree_Item(tree_inputs, "Mouse Wheel", 2, { { 1000, "HOOK INPUT MOUSE WHEEL" } });
		}
		new GUI::Tree_Item(tree_hooks, "Display", 1, { { 1000, "HOOK DISPLAY" } });
	}

	auto tree_render = new GUI::Tree_Item(this, "Rendering");
	{
		auto tree_2d = new GUI::Tree_Item(tree_render, "2D Rendering", 1);
		{
			new GUI::Tree_Item(tree_2d, "Line"     , 2, { { 1000, "RENDER 2D LINE"      } });
			new GUI::Tree_Item(tree_2d, "Triangle" , 2, { { 1000, "RENDER 2D TRIANGLE"  } });
			new GUI::Tree_Item(tree_2d, "Rectangle", 2, { { 1000, "RENDER 2D RECTANGLE" } });
			new GUI::Tree_Item(tree_2d, "Circle"   , 2, { { 1000, "RENDER 2D CIRCLE"    } });
		}
		auto tree_3d = new GUI::Tree_Item(tree_render, "3D Rendering", 1);
		{
			new GUI::Tree_Item(tree_3d, "Sphere" , 2, { { 1000, "RENDER 3D SPHERE" } });
		}
	}

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

		if (temp->data(0, 1000).toString() == "SCRIPT") {
			QByteArray script_path;
			QDataStream dataStreamPath(&script_path, QIODevice::WriteOnly);
			dataStreamPath << temp->data(0, 1001).toString();
			mimeData->setData("Path", script_path);
		}

		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->exec(Qt::MoveAction);
	}
}
#include "Node_Shelf.hpp"

#include "Session.hpp"

#ifdef _DEBUG
const QString type = "Debug";
#else
const QString type = "Release";
#endif

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
				auto item = new GUI::Tree_Item(tree->user_scripts, script_id, 1, { { 1000, "SCRIPT" }, { 1001, script_path } });
			}
		}
	});

	auto tree_included = new GUI::Tree_Item(tree->user_scripts, "Included", 1);
	{
		auto camera = new GUI::Tree_Item(tree_included, "Camera Controller", 2, { {1000, "SCRIPT"}, { 1001, "D:/Coding/Simulator/x64/" + type + "/Script-Camera-Controller.dll" } });
	}

	auto tree_showcase = new GUI::Tree_Item(tree->user_scripts, "Showcase", 1);
	{
		auto controllable = new GUI::Tree_Item(tree_showcase, "Controllable Object", 2, { {1000, "SCRIPT"}, { 1001, "D:/Coding/Simulator/x64/" + type + "/Script-Controllable-Object-Showcase.dll" } });
		auto particles    = new GUI::Tree_Item(tree_showcase, "Particles"          , 2, { {1000, "SCRIPT"}, { 1001, "D:/Coding/Simulator/x64/" + type + "/Script-Particle-Showcase.dll"            } });
	}
}

NODE_SHELF::Tree::Tree(Node_Shelf* parent) :
	GUI::Tree(parent)
{
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::DragDropMode::DragOnly);

	user_scripts = new GUI::Tree_Item(this, "Scripts");

	auto tree_variables = new GUI::Tree_Item(this, "Variables");
	{
		auto constant = new GUI::Tree_Item(tree_variables, "Constant", 1, { { 1000, "VARIABLE CONSTANT" } });
		auto set      = new GUI::Tree_Item(tree_variables, "Set"     , 1, { { 1000, "VARIABLE SET"      } });
		auto get      = new GUI::Tree_Item(tree_variables, "Get"     , 1, { { 1000, "VARIABLE GET"      } });
	}

	auto tree_cast = new GUI::Tree_Item(this, "Casting");
	{
		auto tree_convert = new GUI::Tree_Item(tree_cast, "Convert", 1);
		{
			auto i64_to_f64 = new GUI::Tree_Item(tree_convert, "Int -> Double", 2, { { 1000, "CAST CONVERT I64 TO F64" } });
		}
		auto tree_make = new GUI::Tree_Item(tree_cast, "Make", 1);
		{
			auto vec2  = new GUI::Tree_Item(tree_make, "Vec 2", 2, { { 1000, "CAST MAKE VEC2"  } });
			auto vec3  = new GUI::Tree_Item(tree_make, "Vec 3", 2, { { 1000, "CAST MAKE VEC3"  } });
			auto vec4  = new GUI::Tree_Item(tree_make, "Vec 4", 2, { { 1000, "CAST MAKE VEC4"  } });
			auto color = new GUI::Tree_Item(tree_make, "Color", 2, { { 1000, "CAST MAKE COLOR" } });
			auto quat  = new GUI::Tree_Item(tree_make, "Quat" , 2, { { 1000, "CAST MAKE QUAT"  } });
			auto mat2  = new GUI::Tree_Item(tree_make, "Mat 2", 2, { { 1000, "CAST MAKE MAT2"  } });
			auto mat3  = new GUI::Tree_Item(tree_make, "Mat 3", 2, { { 1000, "CAST MAKE MAT3"  } });
			auto mat4  = new GUI::Tree_Item(tree_make, "Mat 4", 2, { { 1000, "CAST MAKE MAT4"  } });
		}
		auto tree_break = new GUI::Tree_Item(tree_cast, "Break", 1);
		{

		}
	}

	auto tree_math = new GUI::Tree_Item(this, "Math");
	{
		auto arithmetic   = new GUI::Tree_Item(tree_math, "Arithmetic"  , 1, { { 1000, "MATH ARITHMETIC"   } });
		auto trigonometry = new GUI::Tree_Item(tree_math, "Trigonometry", 1, { { 1000, "MATH TRIGONOMETRY" } });
	}

	auto tree_boolean = new GUI::Tree_Item(this, "Boolean");
	{
		auto comparison = new GUI::Tree_Item(tree_boolean, "Comparison", 1, { { 1000, "BOOLEAN COMPARISON" } });
		auto select     = new GUI::Tree_Item(tree_boolean, "Select"    , 1, { { 1000, "BOOLEAN SELECT"     } });
	}

	auto tree_container = new GUI::Tree_Item(this, "Container");
	{
		auto tree_list = new GUI::Tree_Item(tree_container, "List", 1);
		{
			auto access = new GUI::Tree_Item(tree_list, "Access", 2, { { 1000, "CONTAINER LIST ACCESS" } });
			auto create = new GUI::Tree_Item(tree_list, "Create", 2, { { 1000, "CONTAINER LIST CREATE" } });
			auto insert = new GUI::Tree_Item(tree_list, "Insert", 2, { { 1000, "CONTAINER LIST INSERT" } });
			auto modify = new GUI::Tree_Item(tree_list, "Modify", 2, { { 1000, "CONTAINER LIST MODIFY" } });
			auto remove = new GUI::Tree_Item(tree_list, "Remove", 2, { { 1000, "CONTAINER LIST REMOVE" } });
			auto clear  = new GUI::Tree_Item(tree_list, "Clear" , 2, { { 1000, "CONTAINER LIST CLEAR"  } });
			auto push   = new GUI::Tree_Item(tree_list, "Push"  , 2, { { 1000, "CONTAINER LIST PUSH"   } });
			auto size   = new GUI::Tree_Item(tree_list, "Size"  , 2, { { 1000, "CONTAINER LIST SIZE"   } });
		}
	}

	auto tree_exec = new GUI::Tree_Item(this, "Exec");
	{
		auto tree_loop = new GUI::Tree_Item(tree_exec, "Loop", 1);
		{
			auto subsample = new GUI::Tree_Item(tree_loop, "Subsample" , 2, { { 1000, "EXEC LOOP SUBSAMPLE" } });
			auto _while    = new GUI::Tree_Item(tree_loop, "While"     , 2, { { 1000, "EXEC LOOP WHILE"     } });
			auto _for      = new GUI::Tree_Item(tree_loop, "For"       , 2, { { 1000, "EXEC LOOP FOR"       } });
		}
		auto _if_else    = new GUI::Tree_Item(tree_exec, "If Else"    , 1, { { 1000, "EXEC IF ELSE"    } });
		auto _if         = new GUI::Tree_Item(tree_exec, "If"         , 1, { { 1000, "EXEC IF"         } });
	}

	auto tree_singleton = new GUI::Tree_Item(this, "Singletons");
	{
		auto background = new GUI::Tree_Item(tree_singleton, "Render Background", 1, { { 1000, "SINGLETON BACKGROUND" } });
		auto euler_tick = new GUI::Tree_Item(tree_singleton, "Euler Tick"       , 1, { { 1000, "SINGLETON EULER TICK" } });
		auto camera_2d  = new GUI::Tree_Item(tree_singleton, "Camera 2D"        , 1, { { 1000, "SINGLETON 2D CAMERA"  } });
		auto camera_3d  = new GUI::Tree_Item(tree_singleton, "Camera 3D"        , 1, { { 1000, "SINGLETON 3D CAMERA"  } });
		auto init       = new GUI::Tree_Item(tree_singleton, "Init Scene"       , 1, { { 1000, "SINGLETON INIT"       } });
	}

	auto tree_hooks = new GUI::Tree_Item(this, "Hooks");
	{
		auto tree_inputs = new GUI::Tree_Item(tree_hooks, "Inputs", 1);
		{
			auto key         = new GUI::Tree_Item(tree_inputs, "Key"        , 2, { { 1000, "HOOK INPUT KEY"         } });
			auto mouse       = new GUI::Tree_Item(tree_inputs, "Mouse"      , 2, { { 1000, "HOOK INPUT MOUSE"       } });
			auto mouse_pos   = new GUI::Tree_Item(tree_inputs, "Mouse Pos"  , 2, { { 1000, "HOOK INPUT MOUSE POS"   } });
			auto mouse_wheel = new GUI::Tree_Item(tree_inputs, "Mouse Wheel", 2, { { 1000, "HOOK INPUT MOUSE WHEEL" } });
		}
		auto display = new GUI::Tree_Item(tree_hooks, "Display", 1, { { 1000, "HOOK DISPLAY" } });
	}

	auto tree_render = new GUI::Tree_Item(this, "Rendering");
	{
		auto tree_2d = new GUI::Tree_Item(tree_render, "2D Rendering", 1);
		{
			auto line      = new GUI::Tree_Item(tree_2d, "Line"     , 2, { { 1000, "RENDER 2D LINE"      } });
			auto triangle  = new GUI::Tree_Item(tree_2d, "Triangle" , 2, { { 1000, "RENDER 2D TRIANGLE"  } });
			auto rectangle = new GUI::Tree_Item(tree_2d, "Rectangle", 2, { { 1000, "RENDER 2D RECTANGLE" } });
			auto circle    = new GUI::Tree_Item(tree_2d, "Circle"   , 2, { { 1000, "RENDER 2D CIRCLE"    } });
		}
		auto tree_3d = new GUI::Tree_Item(tree_render, "3D Rendering", 1);
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
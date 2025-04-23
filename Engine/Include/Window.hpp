#pragma once

#include "KL.hpp"

#include "Variable_Editor.hpp"
#include "History_View.hpp"
#include "Node_Editor.hpp"
#include "Node_Shelf.hpp"
#include "Viewport.hpp"
#include "Timeline.hpp"

struct Session;

struct Window : GUI::Window {
	Session* session;

	Node_Shelf*      shelf          ;
	Timeline*        timeline       ;
	Node_Editor*     node_editor    ;
	History_View*    history_view   ;
	Variable_Editor* variable_editor;

	Viewport*        viewport       ;

	Window();
	~Window();
};
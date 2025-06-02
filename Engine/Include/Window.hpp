#pragma once

#include "KL.hpp"
#include "KL_GUI.hpp"

#include "Variable_Editor.hpp"
#include "History_View.hpp"
#include "Node_Editor.hpp"
#include "Node_Shelf.hpp"
#include "Viewport.hpp"
#include "Timeline.hpp"
#include "Header.hpp"

struct Session;

struct Window : GUI::Window {
	Session* session;

	Header*          header         ;
	Timeline*        timeline       ;
	Node_Shelf*      node_shelf     ;
	Node_Editor*     node_editor    ;
	History_View*    history_view   ;
	Variable_Editor* variable_editor;

	Viewport*        viewport       ;

	Window();
	~Window();
};
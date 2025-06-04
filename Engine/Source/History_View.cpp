#include "History_View.hpp"

#include "Session.hpp"

History_View::History_View(QWidget* parent) :
	GUI::Linear_Contents(parent)
{
	undo = new GUI::Tree(this);
	redo = new GUI::Tree(this);

	auto splitter = new GUI::Splitter(this);
	splitter->addWidget(undo);
	splitter->addWidget(redo);

	addWidget(splitter);

	SESSION->history.group_undo_stack.onItemAddedCallback(this, [this](const U32& item) {
		auto hitory = SESSION->history;
		undo->clear();
		U64 counter = 0;
		for (U64 i = 0; i < SESSION->history.group_undo_stack.size(); i++) {
			const U32 group_count = SESSION->history.group_undo_stack.inverse(i);
			if (group_count > 1) {
				auto group = new GUI::Tree_Item(undo, "[" + QString::number(group_count) + "]");
				for (U64 j = 0; j < group_count; j++) {
					new GUI::Tree_Item(group, qstr(SESSION->history.undo_stack.inv_ref(counter)->info), 1);
					counter++;
				}
			}
			else {
				new GUI::Tree_Item(undo, qstr(SESSION->history.undo_stack.inv_ref(counter)->info));
				counter++;
			}
		}
	});
	SESSION->history.group_undo_stack.onItemRemovedCallback(this, [this](const U32& item) {
		undo->clear();
		U64 counter = 0;
		for (U64 i = 0; i < SESSION->history.group_undo_stack.size(); i++) {
			const U32 group_count = SESSION->history.group_undo_stack.inverse(i);
			if (group_count > 1) {
				auto group = new GUI::Tree_Item(undo, "[" + QString::number(group_count) + "]");
				for (U64 j = 0; j < group_count; j++) {
					new GUI::Tree_Item(group, qstr(SESSION->history.undo_stack.inv_ref(counter)->info), 1);
					counter++;
				}
			}
			else {
				new GUI::Tree_Item(undo, qstr(SESSION->history.undo_stack.inv_ref(counter)->info));
				counter++;
			}
		}
	});
	SESSION->history.group_undo_stack.onItemsClearedCallback(this, [this]() {
		undo->clear();
	});

	SESSION->history.group_redo_stack.onItemAddedCallback(this, [this](const U32& item) {
		redo->clear();
		U64 counter = 0;
		for (U64 i = 0; i < SESSION->history.group_redo_stack.size(); i++) {
			const U32 group_count = SESSION->history.group_redo_stack.inverse(i);
			if (group_count > 1) {
				auto group = new GUI::Tree_Item(redo, "[" + QString::number(group_count) + "]");
				for (U64 j = 0; j < group_count; j++) {
					auto val = new GUI::Tree_Item(group, qstr(SESSION->history.redo_stack.inv_ref(counter)->info), 1);
					val->setFlags(val->flags() & ~ Qt::ItemFlag::ItemIsSelectable);
					counter++;
				}
			}
			else {
				auto val = new GUI::Tree_Item(redo, qstr(SESSION->history.redo_stack.inv_ref(counter)->info));
				val->setFlags(val->flags() & ~ Qt::ItemFlag::ItemIsSelectable);
				counter++;
			}
		}
	});
	SESSION->history.group_redo_stack.onItemRemovedCallback(this, [this](const U32& item) {
		redo->clear();
		U64 counter = 0;
		for (U64 i = 0; i < SESSION->history.group_redo_stack.size(); i++) {
			const U32 group_count = SESSION->history.group_redo_stack.inverse(i);
			if (group_count > 1) {
				auto group = new GUI::Tree_Item(redo, "[" + QString::number(group_count) + "]");
				for (U64 j = 0; j < group_count; j++) {
					auto val = new GUI::Tree_Item(group, qstr(SESSION->history.redo_stack.inv_ref(counter)->info), 1);
					val->setFlags(val->flags() & ~ Qt::ItemFlag::ItemIsSelectable);
					counter++;
				}
			}
			else {
				auto val = new GUI::Tree_Item(redo, qstr(SESSION->history.redo_stack.inv_ref(counter)->info));
				val->setFlags(val->flags() & ~ Qt::ItemFlag::ItemIsSelectable);
				counter++;
			}
		}
	});
	SESSION->history.group_redo_stack.onItemsClearedCallback(this, [this]() {
		redo->clear();
	});
}

History_View::~History_View() {
	SESSION->history.group_undo_stack.removeOnItemAddedCallback(this);
	SESSION->history.group_undo_stack.removeOnItemRemovedCallback(this);
	SESSION->history.group_undo_stack.removeOnItemsClearedCallback(this);
	SESSION->history.group_redo_stack.removeOnItemAddedCallback(this);
	SESSION->history.group_redo_stack.removeOnItemRemovedCallback(this);
	SESSION->history.group_redo_stack.removeOnItemsClearedCallback(this);
}
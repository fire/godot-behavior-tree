#include "visual_brain_tree_behavior_tree_editor_plugin.h"

#include "core/io/resource_loader.h"
#include "core/os/input.h"
#include "core/os/keyboard.h"
#include "core/project_settings.h"
#include "editor/editor_properties.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/panel.h"
#include "scene/main/viewport.h"

///////////////////////////////////

void VisualBrainTreeBehaviorTreeEditor::edit(const Ref<VisualBrainTreeBehaviorTree> &p_visual_brain_tree_behavior_tree) {

	if (visual_brain_tree_behavior_tree == p_visual_brain_tree_behavior_tree) {
		return;
	} else {
		//hide();
		component_editor->hide();
	}

	//if (visual_anl_noise.is_valid()) {
	//	visual_anl_noise->disconnect("component_changed", this, "_on_component_changed");
	//}

	if (p_visual_brain_tree_behavior_tree.is_valid()) {
		visual_brain_tree_behavior_tree = p_visual_brain_tree_behavior_tree;

		//if (!visual_anl_noise->is_connected("component_changed", this, "_on_component_changed")) {
		//	visual_anl_noise->connect("component_changed", this, "_on_component_changed");
		//}
		//edit_component();
		//_update_path();

	} else {
		visual_brain_tree_behavior_tree.unref();
	}

	//if (visual_anl_noise.is_null()) {
	//	hide();
	//}
}

void VisualBrainTreeBehaviorTreeEditor::save_external_data() {

	if (visual_brain_tree_behavior_tree.is_null())
		return;

	ResourceSaver::save(visual_brain_tree_behavior_tree->get_path(), visual_brain_tree_behavior_tree);
}

void VisualBrainTreeBehaviorTreeEditor::add_plugin(VisualBrainTreeBehaviorTreeNodeComponentEditor *p_editor) {

	ERR_FAIL_COND(p_editor->get_parent());
	editor_base->add_child(p_editor);
	component_editor = p_editor;
	p_editor->set_h_size_flags(SIZE_EXPAND_FILL);
	p_editor->set_v_size_flags(SIZE_EXPAND_FILL);
	p_editor->hide();
}

void VisualBrainTreeBehaviorTreeEditor::remove_plugin(VisualBrainTreeBehaviorTreeNodeComponentEditor *p_editor) {

	ERR_FAIL_COND(p_editor->get_parent() != editor_base);
	editor_base->remove_child(p_editor);
	component_editor = NULL;
}

void VisualBrainTreeBehaviorTreeEditor::_update_path() {

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> node = visual_brain_tree_behavior_tree->get_component();
	if (node.is_null()) {
		return;
	}

	while (path_hb->get_child_count()) {
		memdelete(path_hb->get_child(0));
	}

	Ref<ButtonGroup> group;
	group.instance();

	Button *b = memnew(Button);
	b->set_text(node->get_component_name());
	b->set_toggle_mode(true);
	b->set_button_group(group);
	b->set_pressed(true);
	b->set_focus_mode(FOCUS_NONE);
	b->connect("pressed", this, "_path_button_pressed", varray(-1));
	path_hb->add_child(b);

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> comp;

	for (int i = 0; i < button_path.size(); i++) {

		node = node->get_node(button_path[i]);

		b = memnew(Button);
		b->set_text(node->get_component_name());
		b->set_toggle_mode(true);
		b->set_button_group(group);
		path_hb->add_child(b);
		b->set_pressed(true);
		b->set_focus_mode(FOCUS_NONE);
		b->connect("pressed", this, "_path_button_pressed", varray(i));
	}
}

Ref<VisualBrainTreeBehaviorTreeNodeComponent> VisualBrainTreeBehaviorTreeEditor::_get_child_by_path(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_node, Vector<int> &p_path) {

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> node = p_node;

	for (int i = 0; i < p_path.size(); i++) {

		Ref<VisualBrainTreeBehaviorTreeNodeComponent> child = node->get_node(p_path[i]);
		ERR_BREAK(child.is_null());
		node = child;
	}
	return node;
}

void VisualBrainTreeBehaviorTreeEditor::edit_path(const Vector<int> &p_path) {

	button_path.clear();

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> node = visual_brain_tree_behavior_tree->get_component();

	if (node.is_valid()) {
		current_component = node->get_instance_id();

		for (int i = 0; i < p_path.size(); i++) {

			Ref<VisualBrainTreeBehaviorTreeNodeComponent> child = node->get_node(p_path[i]);
			ERR_BREAK(child.is_null());
			node = child;
			button_path.push_back(p_path[i]);
		}
		edit_component(node);
	} else {
		current_component = 0;
	}

	edited_path = button_path;

	_update_path();
}

void VisualBrainTreeBehaviorTreeEditor::_path_button_pressed(int p_path) {

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> node = visual_brain_tree_behavior_tree->get_component();

	if (node.is_null())
		return;

	edited_path.clear();

	if (p_path >= 0) {
		for (int i = 0; i <= p_path; i++) {
			Ref<VisualBrainTreeBehaviorTreeNodeComponent> child = node->get_node(button_path[i]);
			ERR_BREAK(child.is_null());
			node = child;
			edited_path.push_back(button_path[i]);
		}
	}

	edit_component(node);
}

void VisualBrainTreeBehaviorTreeEditor::edit_component(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_component) {

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> component;

	if(p_component.is_null()) {
		component = visual_brain_tree_behavior_tree->get_component();
	} else {
		component = p_component;
	}

	if(component.is_valid()) {

		if (component_editor->can_edit(component)) {
			component_editor->edit(component);
			component_editor->show();
		} else {
			component_editor->edit(Ref<VisualBrainTreeBehaviorTreeNodeComponent>());
			component_editor->hide();
		}
	}
}

void VisualBrainTreeBehaviorTreeEditor::_on_component_changed() {

	edit_component();
}

void VisualBrainTreeBehaviorTreeEditor::enter_editor(int p_which) {

	Vector<int> path = edited_path;
	path.push_back(p_which);
	edit_path(path);
}

Vector<int> VisualBrainTreeBehaviorTreeEditor::get_edited_path() const {

	return button_path;
}

bool VisualBrainTreeBehaviorTreeEditor::can_edit(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_node) const {

	if (component_editor->can_edit(p_node)) {
		return true;
	}
	return false;
}

void VisualBrainTreeBehaviorTreeEditor::_notification(int p_what) {

	if (p_what == NOTIFICATION_PROCESS) {
		ObjectID component = 0;
		if (visual_brain_tree_behavior_tree.is_valid() && visual_brain_tree_behavior_tree->get_component().is_valid()) {
			component = visual_brain_tree_behavior_tree->get_component()->get_instance_id();
		}

		if (component != current_component) {
			edit_path(Vector<int>());
		}
	}
}

void VisualBrainTreeBehaviorTreeEditor::_bind_methods() {

	ClassDB::bind_method("_path_button_pressed", &VisualBrainTreeBehaviorTreeEditor::_path_button_pressed);
	ClassDB::bind_method("_on_component_changed", &VisualBrainTreeBehaviorTreeEditor::_on_component_changed);
}

VisualBrainTreeBehaviorTreeEditor *VisualBrainTreeBehaviorTreeEditor::singleton = NULL;

VisualBrainTreeBehaviorTreeEditor::VisualBrainTreeBehaviorTreeEditor() {

	path_edit = memnew(ScrollContainer);
	add_child(path_edit);
	path_edit->set_enable_h_scroll(true);
	path_edit->set_enable_v_scroll(false);
	path_hb = memnew(HBoxContainer);
	path_edit->add_child(path_hb);

	current_component = 0;
	singleton = this;
	editor_base = memnew(PanelContainer);
	editor_base->set_v_size_flags(SIZE_EXPAND_FILL);
	add_child(editor_base);

	add_plugin(memnew(VisualBrainTreeBehaviorTreeNodeComponentEditor));
}

///////////////////////////////////
// Plugin
///////////////////////////////////

void VisualBrainTreeBehaviorTreeEditorPlugin::edit(Object *p_object) {

	visual_brain_tree_behavior_tree_editor->edit(Object::cast_to<VisualBrainTreeBehaviorTree>(p_object));
}

bool VisualBrainTreeBehaviorTreeEditorPlugin::handles(Object *p_object) const {

	return p_object->is_class("VisualAnlNoise");
}

void VisualBrainTreeBehaviorTreeEditorPlugin::make_visible(bool p_visible) {

	if (p_visible) {
		button->show();
		editor->make_bottom_panel_item_visible(visual_brain_tree_behavior_tree_editor);

		visual_brain_tree_behavior_tree_editor->set_process(true);
		visual_brain_tree_behavior_tree_editor->set_process_input(true);
	} else {

		if (visual_brain_tree_behavior_tree_editor->is_visible_in_tree())
			editor->hide_bottom_panel();
		button->hide();

		visual_brain_tree_behavior_tree_editor->set_process(false);
		visual_brain_tree_behavior_tree_editor->set_process_input(false);
	}
}

void VisualBrainTreeBehaviorTreeEditorPlugin::save_external_data() {

	visual_brain_tree_behavior_tree_editor->save_external_data();
}

VisualBrainTreeBehaviorTreeEditorPlugin::VisualBrainTreeBehaviorTreeEditorPlugin(EditorNode *p_node) {

	editor = p_node;
	visual_brain_tree_behavior_tree_editor = memnew(VisualBrainTreeBehaviorTreeEditor);
	visual_brain_tree_behavior_tree_editor->set_custom_minimum_size(Size2(0, 300));

	button = editor->add_bottom_panel_item(TTR("VisualAnlNoise"), visual_brain_tree_behavior_tree_editor);
	button->hide();
}

VisualBrainTreeBehaviorTreeEditorPlugin::~VisualBrainTreeBehaviorTreeEditorPlugin() {
}

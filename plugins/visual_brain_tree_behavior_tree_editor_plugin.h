#ifndef VISUAL_BRAIN_TREE_BEHAVIOR_TREE_EDITOR_PLUGIN_H
#define VISUAL_BRAIN_TREE_BEHAVIOR_TREE_EDITOR_PLUGIN_H

#include "../visual_brain_tree_behavior_tree.h"
#include "visual_brain_tree_behavior_tree_component_editor_plugin.h"

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/gui/button.h"
#include "scene/gui/graph_edit.h"
#include "scene/gui/popup.h"
#include "scene/gui/tree.h"

class VisualBrainTreeBehaviorTreeEditor : public VBoxContainer {

	GDCLASS(VisualBrainTreeBehaviorTreeEditor, VBoxContainer);

	static VisualBrainTreeBehaviorTreeEditor *singleton;

	Ref<VisualBrainTreeBehaviorTree> visual_brain_tree_behavior_tree;

	ScrollContainer *path_edit;
	HBoxContainer *path_hb;
	PanelContainer *editor_base;

	Vector<int> button_path;
	Vector<int> edited_path;
	VisualBrainTreeBehaviorTreeNodeComponentEditor *component_editor;

	ObjectID current_component;

	void _update_path();
	void _path_button_pressed(int path);

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	static VisualBrainTreeBehaviorTreeEditor *get_singleton() { return singleton; }

	void add_plugin(VisualBrainTreeBehaviorTreeNodeComponentEditor *p_editor);
	void remove_plugin(VisualBrainTreeBehaviorTreeNodeComponentEditor *p_editor);

	bool can_edit(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_node) const;

	void edit_component(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_component = NULL);
	void _on_component_changed();

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> _get_child_by_path(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &node, Vector<int> &p_path);

	void edit_path(const Vector<int> &p_path);
	Vector<int> get_edited_path() const;

	void enter_editor(int p_which);

	void edit(const Ref<VisualBrainTreeBehaviorTree> &p_visual_anl_noise);

	void save_external_data();

	VisualBrainTreeBehaviorTreeEditor();
};

class VisualBrainTreeBehaviorTreeEditorPlugin : public EditorPlugin {

	GDCLASS(VisualBrainTreeBehaviorTreeEditorPlugin, EditorPlugin);

	VisualBrainTreeBehaviorTreeEditor *visual_brain_tree_behavior_tree_editor;
	EditorNode *editor;
	Button *button;

public:
	virtual String get_name() const { return "VisualBrainTreeBehaviourTree"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);

	virtual void save_external_data();

	VisualBrainTreeBehaviorTreeEditorPlugin(EditorNode *p_node);
	~VisualBrainTreeBehaviorTreeEditorPlugin();
};

#endif

#ifndef VISUAL_ANL_NOISE_NODE_COMPONENT_EDITOR_PLUGIN_H
#define VISUAL_ANL_NOISE_NODE_COMPONENT_EDITOR_PLUGIN_H

#include "../visual_brain_tree_behavior_tree.h"

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/gui/button.h"
#include "scene/gui/graph_edit.h"
#include "scene/gui/popup.h"
#include "scene/gui/tree.h"

class VisualBrainTreeBehaviourTreeNodePlugin : public Reference {

	GDCLASS(VisualBrainTreeBehaviourTreeNodePlugin, Reference)

protected:
	static void _bind_methods();

public:
	virtual Control *create_editor(const Ref<VisualBrainTreeBehaviorTreeNode> &p_node);
	VisualBrainTreeBehaviourTreeNodePlugin(EditorNode *p_node) {}
	~VisualBrainTreeBehaviourTreeNodePlugin() {}
};

class VisualBrainTreeBehaviorTreeNodePluginDefault : public VisualBrainTreeBehaviourTreeNodePlugin {

	GDCLASS(VisualBrainTreeBehaviorTreeNodePluginDefault, VisualBrainTreeBehaviourTreeNodePlugin)

public:
	virtual Control *create_editor(const Ref<VisualBrainTreeBehaviorTreeNode> &p_node);
};

class VisualBrainTreeBehaviorTreeEditorPlugin;
class VisualBrainTreeBehaviorTreeNodeComponentEditor : public VBoxContainer {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeComponentEditor, VBoxContainer);

	static VisualBrainTreeBehaviorTreeNodeComponentEditor *singleton;

	Vector<Ref<VisualBrainTreeBehaviourTreeNodePlugin> > plugins;

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> component;
    GraphEdit *graph;
	MenuButton *add_node;

	PanelContainer *error_panel;
	Label *error_label;

    UndoRedo *undo_redo;

	CustomPropertyEditor *property_editor;
	int editing_node;
	int editing_port;

	void _update_graph();

	struct AddOption {
		String name;
		String category;
		String type;
		Ref<Script> script;
		AddOption(const String &p_name = String(), const String &p_category = String(), const String &p_type = String()) {
			name = p_name;
			type = p_type;
			category = p_category;
		}
	};

	Vector<AddOption> add_options;

	void _draw_color_over_button(Object *obj, Color p_color);

	void _add_node(int p_idx);
	void _update_options_menu();

	void _node_dragged(const Vector2 &p_from, const Vector2 &p_to, int p_node);

	bool updating;

	void _connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index);
	void _disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index);

	void _scroll_changed(const Vector2 &p_scroll);
	void _node_selected(Object *p_node);

	void _delete_request(int);

	void _removed_from_graph();

	void _node_changed(int p_id);

	void _edit_port_default_input(Object *p_button, int p_node, int p_port);
	void _port_edited();

	void _connection_to_empty(const String &p_from, int p_from_slot, const Vector2 &p_release_position);

	void _component_renamed(const String &p_text, int p_which);
	void _component_renamed_focus_out(Node *le, int p_which);

	void _line_edit_changed(const String &p_text, Object *line_edit, int p_node_id);
	void _line_edit_focus_out(Object *line_edit, int p_node_id);

	void _duplicate_nodes();

	void _preview_select_port(int p_node, int p_port);
	void _input(const Ref<InputEvent> p_event);

	EditorFileDialog *open_file;
	Ref<VisualBrainTreeBehaviorTreeNodeComponent> file_loaded;

	void _file_opened(const String &p_file);

	enum {
		MENU_LOAD_FILE = 1000,
		MENU_PASTE = 1001,
		MENU_LOAD_FILE_CONFIRM = 1002
	};

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	static VisualBrainTreeBehaviorTreeNodeComponentEditor *get_singleton() { return singleton; }

	void add_custom_type(const String &p_name, const String &p_category, const Ref<Script> &p_script);
	void remove_custom_type(const Ref<Script> &p_script);

	void add_plugin(const Ref<VisualBrainTreeBehaviourTreeNodePlugin> &p_plugin);
	void remove_plugin(const Ref<VisualBrainTreeBehaviourTreeNodePlugin> &p_plugin);

	virtual Size2 get_minimum_size() const;

	bool can_edit(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_component);
	void edit(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_component);

	VisualBrainTreeBehaviorTreeNodeComponentEditor(EditorNode *p_editor, VisualBrainTreeBehaviorTreeEditorPlugin *p_plugin);
};

#endif

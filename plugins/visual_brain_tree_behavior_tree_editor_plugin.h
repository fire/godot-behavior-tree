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

class VisualBrainTreeBehaviorTreeEditorPlugin : public EditorPlugin {

	GDCLASS(VisualBrainTreeBehaviorTreeEditorPlugin, EditorPlugin);

	VisualBrainTreeBehaviorTreeNodeComponentEditor *visual_brain_tree_behavior_tree_editor;
	EditorNode *editor;

public:
	virtual String get_name() const { return "VisualBrainTreeBehaviourTree"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);

	VisualBrainTreeBehaviorTreeEditorPlugin(EditorNode *p_node);
	~VisualBrainTreeBehaviorTreeEditorPlugin();
};

#endif

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
// Plugin
///////////////////////////////////

void VisualBrainTreeBehaviorTreeEditorPlugin::edit(Object *p_object) {

	visual_brain_tree_behavior_tree_editor->edit(Object::cast_to<VisualBrainTreeBehaviorTreeNodeComponent>(p_object));
}

bool VisualBrainTreeBehaviorTreeEditorPlugin::handles(Object *p_object) const {

	return p_object->is_class("VisualBrainTreeBehaviorTree");
}

void VisualBrainTreeBehaviorTreeEditorPlugin::make_visible(bool p_visible) {

	if (p_visible) {
		editor->make_bottom_panel_item_visible(visual_brain_tree_behavior_tree_editor);

		visual_brain_tree_behavior_tree_editor->set_process(true);
		visual_brain_tree_behavior_tree_editor->set_process_input(true);
	} else {

		if (visual_brain_tree_behavior_tree_editor->is_visible_in_tree()) {
			editor->hide_bottom_panel();
		}

		visual_brain_tree_behavior_tree_editor->set_process(false);
		visual_brain_tree_behavior_tree_editor->set_process_input(false);
	}
}

VisualBrainTreeBehaviorTreeEditorPlugin::VisualBrainTreeBehaviorTreeEditorPlugin(EditorNode *p_node) {

	editor = p_node;
	visual_brain_tree_behavior_tree_editor = memnew(VisualBrainTreeBehaviorTreeNodeComponentEditor(editor, this));
	editor->add_bottom_panel_item(TTR("Behavior tree"), visual_brain_tree_behavior_tree_editor);
	visual_brain_tree_behavior_tree_editor->hide();
}

VisualBrainTreeBehaviorTreeEditorPlugin::~VisualBrainTreeBehaviorTreeEditorPlugin() {
}

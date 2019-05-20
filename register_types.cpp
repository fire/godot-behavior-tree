#include "register_types.h"

#include "brain_tree_behavior_tree.h"
#include "plugins/visual_brain_tree_behavior_tree_editor_plugin.h"
#include "visual_brain_tree_behavior_tree.h"
#include "visual_brain_tree_behavior_tree_nodes.h"

void register_brain_tree_types() {

	ClassDB::register_class<BrainTreeBehaviorTree>();
	ClassDB::register_class<VisualBrainTreeBehaviorTree>();
	ClassDB::register_virtual_class<VisualBrainTreeBehaviorTreeNode>();
	ClassDB::register_class<VisualBrainTreeBehaviorTreeNodeComponent>();
	ClassDB::register_class<VisualBrainTreeBehaviorTreeNodeSelector>();
	ClassDB::register_class<VisualBrainTreeBehaviorTreeNodeSequence>();
	ClassDB::register_class<VisualBrainTreeBehaviorTreeNodeTask>();
	EditorPlugins::add_by_type<VisualBrainTreeBehaviorTreeEditorPlugin>();
}

void unregister_brain_tree_types() {

	// nothing to do here
}

#include "register_types.h"

#include "brain_tree_behavior_tree.h"
#include "plugins/visual_brain_tree_behavior_tree_editor_plugin.h"
#include "visual_brain_tree_behavior_tree.h"
#include "visual_brain_tree_behavior_tree_nodes.h"

#ifdef TOOLS_ENABLED
static void _editor_init() {
	EditorPlugins::add_by_type<VisualBrainTreeBehaviorTreeEditorPlugin>();
}
#endif

void register_brain_tree_types() {

	ClassDB::register_class<BrainTreeBehaviorTree>();
	ClassDB::register_class<VisualBrainTreeBehaviorTree>();

	//// Component
	ClassDB::register_class<VisualBrainTreeBehaviorTreeNodeComponent>();

	//// Nodes
	ClassDB::register_class<VisualBrainTreeBehaviorTreeNodeSelector>();
	ClassDB::register_class<VisualBrainTreeBehaviorTreeNodeSequence>();
	ClassDB::register_class<VisualBrainTreeBehaviorTreeNodeTask>();

#ifdef TOOLS_ENABLED
	EditorNode::add_init_callback(_editor_init);
#endif
}

void unregister_brain_tree_types() {

	// nothing to do here
}

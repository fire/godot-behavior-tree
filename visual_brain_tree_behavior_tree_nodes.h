#ifndef VISUAL_ANL_NOISE_NODES_H
#define VISUAL_ANL_NOISE_NODES_H

#include "visual_brain_tree_behavior_tree.h"

class VisualBrainTreeBehaviorTreeNodeSelector : public VisualBrainTreeBehaviorTreeNode {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeSelector, VisualBrainTreeBehaviorTreeNode)
public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual Vector<StringName> get_editable_properties() const;

	VisualBrainTreeBehaviorTreeNodeSelector();

protected:
	static void _bind_methods();
};

class VisualBrainTreeBehaviorTreeNodeSequence : public VisualBrainTreeBehaviorTreeNode {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeSequence, VisualBrainTreeBehaviorTreeNode)
public:
	virtual String get_caption() const { return "Sequence"; }

	virtual void set_input_port_value(int p_port, const Variant &p_value) {}
	virtual Variant get_input_port_value(int p_port) const {
		return Variant();
	};
	virtual int get_input_port_count() const { return 1; }
	virtual PortType get_input_port_type(int p_port) const { return PORT_TYPE_INDEX; }
	virtual String get_input_port_name(int p_port) const { return String(); }

	virtual int get_output_port_count() const { return 1; }
	virtual PortType get_output_port_type(int p_port) const { return PORT_TYPE_INDEX; }
	virtual String get_output_port_name(int p_port) const { return String(); }

	virtual Vector<StringName> get_editable_properties() const { return Vector<StringName>(); }

	VisualBrainTreeBehaviorTreeNodeSequence() {}

protected:
	static void _bind_methods() {}
};

class VisualBrainTreeBehaviorTreeNodeAction : public VisualBrainTreeBehaviorTreeNode {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeAction, VisualBrainTreeBehaviorTreeNode)

	StringName method;

public:
	virtual String get_caption() const { return "Action"; }

	virtual void set_input_port_value(int p_port, const Variant &p_value) {}
	virtual Variant get_input_port_value(int p_port) const {
		return Variant();
	};
	virtual int get_input_port_count() const { return 1; }
	virtual PortType get_input_port_type(int p_port) const { return PORT_TYPE_INDEX; }
	virtual String get_input_port_name(int p_port) const { return String(); }

	virtual int get_output_port_count() const { return 0; }
	virtual PortType get_output_port_type(int p_port) const { return PORT_TYPE_INDEX; }
	virtual String get_output_port_name(int p_port) const { return String(); }

	void set_action_method(const String p_method) {

		method = p_method;
		emit_changed();
	}

	String get_action_method() const {

		return method;
	}

	virtual Vector<StringName> get_editable_properties() const {

		Vector<StringName> props;
		props.push_back("action_method");

		return props;
	}

	VisualBrainTreeBehaviorTreeNodeAction() { }

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("set_action_method", "method"), &VisualBrainTreeBehaviorTreeNodeAction::set_action_method);
		ClassDB::bind_method(D_METHOD("get_action_method"), &VisualBrainTreeBehaviorTreeNodeAction::get_action_method);

		ADD_PROPERTY(PropertyInfo(Variant::STRING, "action_method"), "set_action_method", "get_action_method");
	}
};

//class VisualAnlNoiseNodeScalar : public VisualAnlNoiseNode {
//	GDCLASS(VisualAnlNoiseNodeScalar, VisualAnlNoiseNode)
//
//public:
//	enum ScalarType {
//		SCALAR_CONSTANT,
//		SCALAR_PI,
//		SCALAR_E,
//		SCALAR_ONE,
//		SCALAR_ZERO,
//		SCALAR_POINT5,
//		SCALAR_SQRT2,
//	};
//
//	void set_type(ScalarType p_type);
//	ScalarType get_type() const;
//
//	void set_constant(real_t p_value);
//	real_t get_constant() const;
//
//public:
//	virtual String get_caption() const;
//
//	virtual void set_input_port_value(int p_port, const Variant &p_value);
//	virtual Variant get_input_port_value(int p_port) const;
//	virtual int get_input_port_count() const;
//	virtual PortType get_input_port_type(int p_port) const;
//	virtual String get_input_port_name(int p_port) const;
//
//	virtual int get_output_port_count() const;
//	virtual PortType get_output_port_type(int p_port) const;
//	virtual String get_output_port_name(int p_port) const;
//
//	virtual Vector<StringName> get_editable_properties() const;
//
//	virtual void evaluate(Ref<VisualAnlNoise> noise);
//
//    VisualAnlNoiseNodeScalar();
//
//protected:
//    static void _bind_methods();
//
//private:
//	ScalarType type;
//    real_t constant;
//};
//
//VARIANT_ENUM_CAST(VisualAnlNoiseNodeScalar::ScalarType);
//
//
//class VisualAnlNoiseNodeScalarOp : public VisualAnlNoiseNode {
//	GDCLASS(VisualAnlNoiseNodeScalarOp, VisualAnlNoiseNode)
//
//public:
//	enum Operator {
//		OP_ADD,
//		OP_SUB,
//		OP_MUL,
//		OP_DIV,
//		OP_POW,
//		OP_MAX,
//		OP_MIN,
//	};
//
//	void set_operator(Operator p_op);
//	Operator get_operator() const;
//
//public:
//	virtual String get_caption() const;
//
//	virtual void set_input_port_value(int p_port, const Variant &p_value);
//	virtual Variant get_input_port_value(int p_port) const;
//	virtual int get_input_port_count() const;
//	virtual PortType get_input_port_type(int p_port) const;
//	virtual String get_input_port_name(int p_port) const;
//
//	virtual int get_output_port_count() const;
//	virtual PortType get_output_port_type(int p_port) const;
//	virtual String get_output_port_name(int p_port) const;
//
//	virtual Vector<StringName> get_editable_properties() const;
//
//	virtual void evaluate(Ref<VisualAnlNoise> noise);
//
//    VisualAnlNoiseNodeScalarOp();
//
//protected:
//    static void _bind_methods();
//
//private:
//	Operator op;
//	Index a, b;
//};
//
//VARIANT_ENUM_CAST(VisualAnlNoiseNodeScalarOp::Operator);
//
//
//class VisualAnlNoiseNodeSimplexBasis : public VisualAnlNoiseNode {
//	GDCLASS(VisualAnlNoiseNodeSimplexBasis, VisualAnlNoiseNode)
//
//public:
//	void set_seed(Index p_idx);
//	Index get_seed() const;
//
//public:
//	virtual String get_caption() const;
//
//	virtual void set_input_port_value(int p_port, const Variant &p_value);
//	virtual Variant get_input_port_value(int p_port) const;
//	virtual int get_input_port_count() const;
//	virtual PortType get_input_port_type(int p_port) const;
//	virtual String get_input_port_name(int p_port) const;
//
//	virtual int get_output_port_count() const;
//	virtual PortType get_output_port_type(int p_port) const;
//	virtual String get_output_port_name(int p_port) const;
//
//	virtual Vector<StringName> get_editable_properties() const;
//
//	virtual void evaluate(Ref<VisualAnlNoise> noise);
//
//    VisualAnlNoiseNodeSimplexBasis();
//
//protected:
//    static void _bind_methods();
//
//private:
//	Index seed;
//};
//
//
//class VisualAnlNoiseNodeExpression : public VisualAnlNoiseNode {
//	GDCLASS(VisualAnlNoiseNodeExpression, VisualAnlNoiseNode)
//
//public:
//	void set_expression(const String &p_expression);
//	String get_expression() const;
//
//public:
//	virtual String get_caption() const;
//
//	virtual void set_input_port_value(int p_port, const Variant &p_value);
//	virtual Variant get_input_port_value(int p_port) const;
//	virtual int get_input_port_count() const;
//	virtual PortType get_input_port_type(int p_port) const;
//	virtual String get_input_port_name(int p_port) const;
//
//	virtual int get_output_port_count() const;
//	virtual PortType get_output_port_type(int p_port) const;
//	virtual String get_output_port_name(int p_port) const;
//
//	virtual Vector<StringName> get_editable_properties() const;
//
//	virtual void evaluate(Ref<VisualAnlNoise> noise);
//
//    VisualAnlNoiseNodeExpression();
//
//protected:
//    static void _bind_methods();
//
//private:
//	String expression;
//};

#endif

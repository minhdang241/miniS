#include "bplus_tree_node.h"

BPlusTreeNode::BPlusTreeNode(size_t const max_size, NodeType const type, BPlusTreeNode* parent = nullptr)
: max_size_{max_size}
, type_{type}
, parent_{parent} {
	keys_.reserve(max_size);
}

auto BPlusTreeNode::get_max_size() const -> size_t {
	return max_size_;
}

auto BPlusTreeNode::get_size() const -> size_t {
	return keys_.size();
}

auto BPlusTreeNode::get_type() const -> NodeType {
	return type_;
}

auto BPlusTreeNode::set_max_size(int const max_size) -> void {
	max_size_ = max_size;
}

auto BPlusTreeNode::is_leaf() const -> bool {
	return type_ == NodeType::LEAF_NODE;
}

auto BPlusTreeNode::is_full() const -> bool {
	return keys_.size() == max_size_;
}

auto BPlusTreeNode::set_type(NodeType const type) -> void {
	type_ = type;
}

auto BPlusTreeNode::get_parent() const -> BPlusTreeNode* {
	return parent_;
}

auto BPlusTreeNode::set_parent(BPlusTreeNode* parent) -> void {
	parent_ = parent;
}

auto BPlusTreeNode::get_keys() -> std::vector<int>& {
	return keys_;
}

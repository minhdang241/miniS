#include "bplus_tree_leaf_node.h"

BPlusTreeLeafNode::BPlusTreeLeafNode(size_t const max_size, BPlusTreeNode* parent)
: BPlusTreeNode(max_size, NodeType::LEAF_NODE, parent) {
	this->rids_.reserve(max_size);
}

auto BPlusTreeLeafNode::insert(int const key, std::pair<int, int> const& value) -> void {
	auto const it = std::ranges::upper_bound(this->keys_, key);
	this->keys_.insert(it, key);
	auto const index = std::distance(this->keys_.begin(), it);
	this->rids_.insert(this->rids_.begin() + index, value);
}

auto BPlusTreeLeafNode::find(int const key) -> std::pair<int, int> {
	auto const it = std::ranges::upper_bound(this->keys_, key);
	auto const index = std::distance(this->keys_.begin(), it);
	return rids_[index];
}

auto BPlusTreeLeafNode::get_values() -> std::vector<std::pair<int, int>>& {
	return this->rids_;
}

auto BPlusTreeLeafNode::get_next_node() const -> BPlusTreeLeafNode* {
	return this->next_node_;
}

auto BPlusTreeLeafNode::set_next_node(BPlusTreeLeafNode* node) -> void {
	this->next_node_ = node;
}

#include "bplus_tree_internal_node.h"

BPlusTreeInternalNode::BPlusTreeInternalNode(size_t const max_size, BPlusTreeNode* parent)
: BPlusTreeNode(max_size, NodeType::INTERNAL_NODE, parent) {
	this->keys_.push_back(-1); // The first key is invalid
	this->children_.reserve(max_size);
}

auto BPlusTreeInternalNode::insert(const int key, std::unique_ptr<BPlusTreeNode> child_ptr) -> void {
	auto const it = std::ranges::upper_bound(this->keys_, key);
	auto const index = std::distance(this->keys_.begin(), it);
	this->keys_.insert(it, key);
	this->children_.insert(children_.begin() + index, std::move(child_ptr));
}

auto BPlusTreeInternalNode::find(int const key) -> BPlusTreeNode* {
	auto const it = std::ranges::upper_bound(this->keys_, key);
	auto const index = std::distance(this->keys_.begin(), it);
	return children_.at(index - 1).get();
}

auto BPlusTreeInternalNode::get_values() -> std::vector<std::unique_ptr<BPlusTreeNode>>& {
	return children_;
}

auto BPlusTreeInternalNode::is_full() const -> bool {
	return keys_.size() - 1 >= max_size_;
}

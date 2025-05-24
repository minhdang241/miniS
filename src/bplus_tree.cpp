#include "bplus_tree.h"

#include <cassert>
#include <iostream>

#include "bplus_tree_leaf_node.h"

BPlusTree::BPlusTree(int const leaf_max_size, int const internal_max_size)
: leaf_max_size_{leaf_max_size}
, internal_max_size_{internal_max_size} {
	root_ = std::make_unique<BPlusTreeLeafNode>(leaf_max_size_, nullptr);
}

auto BPlusTree::update_parent(int const key,
                              BPlusTreeNode const* old_node,
                              std::unique_ptr<BPlusTreeNode>&& new_node) -> void {
	if (old_node == root_.get()) {
		// if the current node is the root, we need to create a new root
		auto new_root = std::make_unique<BPlusTreeInternalNode>(internal_max_size_, nullptr);
		new_root->get_keys().push_back(key);

		// update the parent of the old root and new node
		root_->set_parent(new_root.get());
		new_node->set_parent(new_root.get());

		new_root->get_values().push_back(std::move(root_));
		new_root->get_values().push_back(std::move(new_node));

		root_ = std::move(new_root);
	}
	else {
		auto const parent = dynamic_cast<BPlusTreeInternalNode*>(old_node->get_parent());
		parent->insert(key, std::move(new_node));
		if (parent->is_full()) {
			split_internal_node(parent);
		}
	}
}

auto BPlusTree::split_internal_node(BPlusTreeInternalNode* current_node) -> void {
	auto parent = dynamic_cast<BPlusTreeInternalNode*>(current_node->get_parent());
	auto new_node = std::make_unique<BPlusTreeInternalNode>(internal_max_size_, parent);
	auto const mid_index = static_cast<long>(current_node->get_size() / 2); // cast to avoid warning
	auto& current_keys = current_node->get_keys();
	auto& current_values = current_node->get_values();

	// copy value to new_node
	std::copy(current_keys.begin() + mid_index + 1,
	          current_keys.end(),
	          std::back_inserter(new_node->get_keys()));
	std::move(current_values.begin() + mid_index,
	          current_values.end(),
	          std::back_inserter(new_node->get_values()));

	auto const key = current_keys.at(mid_index);

	// remove copied values from the current node
	current_keys.resize(mid_index);
	current_values.resize(mid_index);

	// update the parent node the children nodes
	auto& new_values = new_node->get_values();
	for (auto& new_value : new_values) {
		new_value->set_parent(new_node.get());
	}

	update_parent(key, current_node, std::move(new_node));
}

auto BPlusTree::split_leaf_node(BPlusTreeLeafNode* current_node) -> void {
	auto parent = dynamic_cast<BPlusTreeInternalNode*>(current_node->get_parent());

	auto new_node = std::make_unique<BPlusTreeLeafNode>(this->leaf_max_size_, parent);

	auto const mid_index = static_cast<long>(current_node->get_size() / 2); // cast to avoid warning

	auto& current_keys = current_node->get_keys();
	auto& current_values = current_node->get_values();

	// copy value to new_leaf
	std::copy(current_keys.begin() + mid_index,
	          current_keys.end(),
	          std::back_inserter(new_node->get_keys()));
	std::copy(current_values.begin() + mid_index,
	          current_values.end(),
	          std::back_inserter(new_node->get_values()));

	// remove copied values from the current node
	current_keys.resize(mid_index);
	current_values.resize(mid_index);

	// update the next node
	new_node->set_next_node(current_node->get_next_node());
	current_node->set_next_node(new_node.get());

	// update parent node by inserting new key for the new node
	auto const key = new_node->get_keys().front();
	update_parent(key, current_node, std::move(new_node));
}

auto BPlusTree::insert(int const key, std::pair<int, int> const& rid) -> bool {
	auto current_node = root_.get();
	while (current_node and !current_node->is_leaf()) {
		auto const internal = dynamic_cast<BPlusTreeInternalNode*>(current_node)->find(key);
		current_node = internal;
	}
	auto const leaf = dynamic_cast<BPlusTreeLeafNode*>(current_node);
	if (!leaf)
		return false;
	leaf->insert(key, rid);
	if (leaf->is_full()) {
		split_leaf_node(leaf);
	}
	return true;
}

auto BPlusTree::find(int const key) const -> std::pair<int, int> {
	auto current_node = root_.get();
	while (current_node and !current_node->is_leaf()) {
		auto const internal = dynamic_cast<BPlusTreeInternalNode*>(current_node)->find(key);
		current_node = internal;
	}
	auto const leaf = dynamic_cast<BPlusTreeLeafNode*>(current_node);
	assert(leaf != nullptr);
	return leaf->find(key);
}

auto BPlusTree::print() const -> void {
	std::vector<BPlusTreeNode*> q;
	q.push_back(root_.get());
	int level = 0;

	while (!q.empty()) {
		auto const level_size = q.size();
		std::cout << "Level " << level << ": ";
		for (int i = 0; i < level_size; ++i) {
			auto const node = q.front();
			q.erase(q.begin());

			std::cout << "[";
			for (auto const& key : node->get_keys()) {
				std::cout << key << " ";
			}
			std::cout << "] ";

			if (!node->is_leaf()) {
				for (auto const internal = dynamic_cast<BPlusTreeInternalNode*>(node);
				     auto const& child_ptr : internal->get_values())
				{
					if (child_ptr) {
						q.push_back(child_ptr.get());
					}
				}
			}
		}
		std::cout << "\n";
		level++;
	}
}

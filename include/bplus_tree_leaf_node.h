#ifndef B_PLUS_TREE_LEAF_NODE_H
#define B_PLUS_TREE_LEAF_NODE_H
#include "bplus_tree_node.h"
#include <vector>

class BPlusTreeLeafNode : public BPlusTreeNode {
public:
    BPlusTreeLeafNode(size_t max_size, BPlusTreeNode* parent);

    auto find(int key) -> std::pair<int, int>;

    auto insert(int key, std::pair<int, int> const&) -> void;

    [[nodiscard]] auto get_values() -> std::vector<std::pair<int, int> >&;

    [[nodiscard]] auto get_next_node() const -> BPlusTreeLeafNode*;

    auto set_next_node(BPlusTreeLeafNode* node) -> void;

private:
    BPlusTreeLeafNode* next_node_ = nullptr;
    std::vector<std::pair<int, int> > rids_; // record ids
};

#endif

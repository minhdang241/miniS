#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H
#include <memory>

#include "bplus_tree_internal_node.h"
#include "bplus_tree_node.h"
#include "bplus_tree_leaf_node.h"

class BPlusTree {
public:
    BPlusTree(int leaf_max_size, int internal_max_size);

    auto insert(int key, const std::pair<int, int>& rid) -> bool;

    [[nodiscard]] auto find(int key) const -> std::pair<int, int>; // return a pair of page_id and row_id

    auto split_leaf_node(BPlusTreeLeafNode*) -> void;

    auto split_internal_node(BPlusTreeInternalNode*) -> void;

    auto update_parent(int key, const BPlusTreeNode*, std::unique_ptr<BPlusTreeNode>&&) -> void;


    auto print() const -> void;

private:
    std::unique_ptr<BPlusTreeNode> root_;
    int leaf_max_size_;
    int internal_max_size_;;
};

#endif

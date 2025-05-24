#ifndef B_PLUS_TREE_INTERNAL_NODE_H
#define B_PLUS_TREE_INTERNAL_NODE_H
#include "bplus_tree_node.h"
#include <vector>


class BPlusTreeInternalNode : public BPlusTreeNode {
public:
    BPlusTreeInternalNode(size_t max_size, BPlusTreeNode* parent);

    auto insert(int key, std::unique_ptr<BPlusTreeNode> child_ptr) -> void;

    [[nodiscard]] auto is_full() const -> bool override;

    [[nodiscard]] auto find(int key) -> BPlusTreeNode*;

    [[nodiscard]] auto get_values() -> std::vector<std::unique_ptr<BPlusTreeNode> >&;

private:
    std::vector<std::unique_ptr<BPlusTreeNode> > children_;
};

#endif

#ifndef B_PLUS_TREE_NODE_H
#define B_PLUS_TREE_NODE_H
#include <vector>

enum class NodeType { INVALID_NODE = 0, LEAF_NODE, INTERNAL_NODE };

class BPlusTreeNode {
public:
    BPlusTreeNode() = default;

    BPlusTreeNode(size_t, NodeType, BPlusTreeNode*);

    [[nodiscard]] auto is_leaf() const -> bool;

    [[nodiscard]] virtual auto is_full() const -> bool;

    [[nodiscard]] auto get_max_size() const -> size_t;

    [[nodiscard]] auto get_type() const -> NodeType;

    [[nodiscard]] auto get_size() const -> size_t;

    [[nodiscard]] auto get_parent() const -> BPlusTreeNode*;

    [[nodiscard]] auto get_keys() -> std::vector<int>&;

    auto set_max_size(int max_size) -> void;

    auto set_parent(BPlusTreeNode*) -> void;

    auto set_type(NodeType type) -> void;


    virtual ~BPlusTreeNode() = default;

protected:
    size_t max_size_;
    std::vector<int> keys_;
    NodeType type_;
    BPlusTreeNode* parent_;
};
#endif

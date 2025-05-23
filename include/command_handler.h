#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include "parser.h"
#include "bplus_tree.h"

class CommandHandler {
public:
    static auto execute_stmt(Stmt const& stmt, Table& table, BPlusTree& index) -> void;
};
#endif

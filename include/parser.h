#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>

#include "table.h"
#include "tokenizer.h"

class Stmt {
public:
    Stmt(std::string const&& type, Record row);

    explicit Stmt(std::string const&& type);

    [[nodiscard]] auto getCommand() const -> std::string;

    [[nodiscard]] auto getRow() const -> Record;

private:
    std::string type_;
    Record row_{};
};

class Parser {
public:
    static auto parse(std::vector<Token> const& tokens) -> Stmt;
};
#endif

#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>

#include "tokenizer.h"

class Stmt {
public:
    Stmt(const std::string& command, const std::vector<std::string>& args);

    auto getCommand() const -> std::string;

    auto getArgs() const -> std::vector<std::string>;

private:
    std::string command_;
    std::vector<std::string> args_;
};

class Parser {
public:
    static auto parse(std::vector<Token> const& tokens) -> Stmt;
};
#endif

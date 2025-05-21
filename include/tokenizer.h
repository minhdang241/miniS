#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>

class Token {
public:
    Token(std::string const& spelling, std::string const& kind);

    auto getKind() const -> std::string;

    auto getSpelling() const -> std::string;

private:
    std::string spelling_;
    std::string kind_;
};

class Tokenizer {
public:
    static auto tokenize(std::string const& input) -> std::vector<Token>;
};
#endif

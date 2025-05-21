#include "tokenizer.h"

#include <cctype>
#include <format>
#include <ranges>
#include <sstream>
#include <unordered_set>

Token::Token(std::string const& spelling, std::string const& kind)
: spelling_{spelling}
, kind_{kind} {};

auto Token::getKind() const -> std::string {
	return kind_;
}

auto Token::getSpelling() const -> std::string {
	return spelling_;
}

auto Tokenizer::tokenize(std::string const& input) -> std::vector<Token> {
	auto validVerbs = std::unordered_set<std::string>{"INSERT", "SELECT"};
	// TODO: improve by using C++20 feature
	auto iss = std::istringstream(input);
	auto words = std::vector<std::string>{};
	for (auto word = std::string(); iss >> word;) {
		words.push_back(word);
	}
	auto tokens = std::vector<Token>{};
	auto it = words.begin();
	auto verb = *it;
	std::transform(verb.begin(), verb.end(), verb.begin(), [](auto c) { return std::toupper(c); });
	if (!validVerbs.contains(verb)) {
		throw std::logic_error(std::format("Unrecognized keyword at start of {}", verb));
	}
	tokens.emplace_back(verb, "VERB");
	++it;
	while (it != words.end()) {
		tokens.emplace_back(*it, "ARG");
		++it;
	}
	return tokens;
}

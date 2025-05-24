#include "parser.h"

#include <format>

Stmt::Stmt(std::string const&& type, Record row)
: type_{type}
, row_{row} {};

Stmt::Stmt(std::string const&& type)
: type_{type} {}

auto Stmt::getRow() const -> Record {
	return row_;
}

auto Stmt::getCommand() const -> std::string {
	return type_;
}

auto Parser::parse(std::vector<Token> const& tokens) -> Stmt {
	auto const& first_token = tokens.front();
	if (first_token.getKind() != "VERB") {
		throw std::logic_error("First token must be VERB");
	}
	auto args = std::vector<std::string>(tokens.size() - 1);
	auto stmt = Stmt{std::move(first_token.getSpelling())};
	if (first_token.getSpelling() == "INSERT") {
		if (tokens.size() != 4) {
			throw std::logic_error("The size of insert statement must be 4");
		}
		try {
			auto id = stoi(tokens[1].getSpelling());
			auto const name_str = tokens[2].getSpelling();
			auto name = std::array<char, 32>();
			std::ranges::copy(name_str, name.begin());
			auto const email_str = tokens[3].getSpelling();
			auto email = std::array<char, 255>();
			std::ranges::copy(email_str, email.begin());
			auto const row = Record(id, name, email);
			stmt = Stmt{std::move(first_token.getSpelling()), row};
		} catch (std::exception const& e) {
			throw std::logic_error(
			   std::format("Error when converting the arguments to row {}", e.what()));
		}
	}
	else if (first_token.getSpelling() == "SELECT") {
		if (tokens.size() == 2) {
			auto const id = stoi(tokens[1].getSpelling());
			stmt = Stmt(std::move(first_token.getSpelling()), Record(id, {}, {}));
		}
	}
	return stmt;
}

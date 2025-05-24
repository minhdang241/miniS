#include "catch2/catch.hpp"
#include "parser.h"
#include "tokenizer.h"

TEST_CASE("parse insert stmt") {
	auto tokens = std::vector{
	   Token("INSERT", "VERB"),
	   Token("1", "ARGS"),
	   Token("minhdg241", "ARGS"),
	   Token("minhdg241@gmail.com", "ARGS"),
	};
	auto stmt = Parser::parse(tokens);
	CHECK(stmt.getCommand() == "INSERT");
}

TEST_CASE("parse select stmt") {
	auto tokens = std::vector{
	   Token("SELECT", "VERB"),
	   Token("*", "ARGS"),
	   Token("from", "ARGS"),
	   Token("users", "ARGS"),
	};
	auto stmt = Parser::parse(tokens);
	CHECK(stmt.getCommand() == "SELECT");
}

TEST_CASE("parse invalid tokens") {
	auto tokens = std::vector{
	   Token("INVALID_COMMAND", "INVALID"),
	   Token("*", "ARGS"),
	   Token("from", "ARGS"),
	   Token("users", "ARGS"),
	};
	CHECK_THROWS_AS(Parser::parse(tokens), std::logic_error);
}

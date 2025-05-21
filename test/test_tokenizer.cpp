#include <iostream>

#include "catch2/catch.hpp"
#include "tokenizer.h"

TEST_CASE("tokenize insert stmt") {
	auto const input = std::string("select * from students");
	auto const tokens = Tokenizer::tokenize(input);
	CHECK(tokens.front().getKind() == "VERB");
	CHECK(tokens.front().getSpelling() == "SELECT");
	CHECK(tokens.size() == 4);
}

TEST_CASE("tokenize select stmt") {
	auto const input = std::string("insert INTO users (email) VALUES person58@example.com");
	auto const tokens = Tokenizer::tokenize(input);
	CHECK(tokens.front().getKind() == "VERB");
	CHECK(tokens.front().getSpelling() == "INSERT");
	CHECK(tokens.size() == 6);
}

TEST_CASE("tokenize invalid stmt") {
	auto const input = std::string("invalid INTO");
	CHECK_THROWS_AS(Tokenizer::tokenize(input), std::logic_error);
}

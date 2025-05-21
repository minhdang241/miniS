#include "parser.h"

Stmt::Stmt(const std::string& command, const std::vector<std::string>& args)
: command_{command}
, args_{args} {};

auto Stmt::getArgs() const -> std::vector<std::string> {
	return args_;
}

auto Stmt::getCommand() const -> std::string {
	return command_;
}

auto Parser::parse(std::vector<Token> const& tokens) -> Stmt {
	if (tokens.front().getKind() != "VERB") {
		throw std::logic_error("First token must be VERB");
	}
	auto args = std::vector<std::string>(tokens.size() - 1);
	std::transform(tokens.begin() + 1, tokens.end(), args.begin(), [](Token const& t) -> std::string {
		return t.getSpelling();
	});
	return {tokens.front().getSpelling(), args};
}

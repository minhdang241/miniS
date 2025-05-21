#include <format>
#include <iostream>
#include <string>

#include "command_handler.h"
#include "parser.h"
#include "tokenizer.h"

int main() {
	auto command = std::string();
	while (true) {
		std::cout << "simple> ";
		if (std::getline(std::cin, command)) {
			if (command[0] == '.') {
				std::transform(command.begin(), command.end(), command.begin(), ::tolower);
				if (command == ".exit") {
					exit(EXIT_SUCCESS);
				}
				std::cout << std::format("Unrecognize command {}", command) << std::endl;
			}
			else {
				try {
					auto tokens = Tokenizer::tokenize(command);
					auto stmt = Parser::parse(tokens);
					CommandHandler::execute_stmt(stmt);
				} catch (std::logic_error& e) {
					std::cout << "Parsing error: " << e.what() << std::endl;
				}
			}
		};
	}
}

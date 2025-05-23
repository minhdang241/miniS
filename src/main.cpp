#include <format>
#include <iostream>
#include <string>

#include "bplus_tree.h"
#include "command_handler.h"
#include "disk_manager.h"
#include "parser.h"
#include "tokenizer.h"

int main() {
	auto command = std::string();
	auto filename = std::filesystem::path("minis.db");
	auto const disk_manager = std::make_shared<DiskManager>(filename);
	auto table = Table();
	auto index = BPlusTree(3, 3);
	disk_manager->load_data(table, index);
	while (true) {
		std::cout << "simple> ";
		if (std::getline(std::cin, command)) {
			if (command[0] == '.') {
				std::ranges::transform(command, command.begin(), ::tolower);
				if (command == ".exit") {
					disk_manager->save_data(table);
					exit(EXIT_SUCCESS);
				}
				std::cout << std::format("Unrecognize command {}", command) << std::endl;
			}
			else {
				try {
					auto tokens = Tokenizer::tokenize(command);
					auto stmt = Parser::parse(tokens);
					CommandHandler::execute_stmt(stmt, table, index);
				} catch (std::logic_error& e) {
					std::cout << "Parsing error: " << e.what() << std::endl;
				}
			}
		};
	}
}

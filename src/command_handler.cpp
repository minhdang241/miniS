#include "command_handler.h"
#include <iostream>

auto CommandHandler::execute_stmt(Stmt const& stmt) -> void {
	if (stmt.getCommand() == "INSERT") {
		std::cout << "This is where we would do an insert\n";
	}
	else if (stmt.getCommand() == "SELECT") {
		std::cout << "This is where we would do a select\n";
	}
	else {
		std::cout << "invalid\n";
	}
}

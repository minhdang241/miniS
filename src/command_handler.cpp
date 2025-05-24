#include "command_handler.h"
#include <iostream>

auto CommandHandler::execute_stmt(Stmt const& stmt, Table& table) -> void {
	if (stmt.getCommand() == "INSERT") {
		auto const row = stmt.getRow();
		table.insert(row);
	}
	else if (stmt.getCommand() == "SELECT") {
		for (auto const rows = table.get_rows(); auto const& row : rows) {
			std::cout << row.id << " " << row.name.data() << " " << row.email.data() << "\n";
		}
	}
	else {
		std::cout << "invalid\n";
	}
}

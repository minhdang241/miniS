#include "command_handler.h"
#include <iostream>

auto CommandHandler::execute_stmt(Stmt const& stmt, Table& table, BPlusTree& index) -> void {
	if (stmt.getCommand() == "INSERT") {
		auto const row = stmt.getRow();
		table.insert(row);
		index.insert(row.id, {table.get_pages().size() - 1, row.id});
	}
	else if (stmt.getCommand() == "SELECT") {
		if (auto const row = stmt.getRow(); row.id == -1) {
			for (auto const rows = table.get_rows(); auto const& row : rows) {
				std::cout << row.id << " " << row.name.data() << " " << row.email.data() << "\n";
			}
		}
		else {
			auto const [page_id, row_id] = index.find(row.id);
			auto const page = table.get_pages().at(page_id);
			auto const result = page.get_rows().at(row_id - 1);
			std::cout << result.id << " " << result.name.data() << " " << result.email.data() << "\n";
		}
	}
	else {
		std::cout << "invalid\n";
	}
}

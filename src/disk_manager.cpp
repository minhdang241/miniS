
#include "disk_manager.h"
#include <stdexcept>

DiskManager::DiskManager(std::filesystem::path const& db_file)
: file_name_{db_file} {
	db_io_.open(file_name_, std::ios::binary | std::ios::in | std::ios::out);
	if (!db_io_.is_open()) {
		throw std::runtime_error("Cannot open database file");
	}
	// Initialize the database file
	std::filesystem::resize_file(file_name_, (capacity_ + 1) * mini_sqlite::PAGE_SIZE);
}

auto DiskManager::increase_disk_space(size_t const current_page_counts) -> void {
	if (current_page_counts < capacity_) {
		return;
	}
	capacity_ *= 2;
	std::filesystem::resize_file(file_name_, capacity_ * mini_sqlite::PAGE_SIZE);
}

auto DiskManager::write_page(int const page_id, Table& table) -> void {
	auto const& pages = table.get_pages();
	if (page_id >= pages.size()) {
		throw std::runtime_error("Page not found");
	}

	increase_disk_space(pages.size());

	auto const offset = page_id * mini_sqlite::PAGE_SIZE;
	db_io_.seekp(offset);
	auto const& page = pages[page_id];
	auto const data = page_id == 0 ? page.serialize_p0() : page.serialize();
	db_io_.write(data.data(), mini_sqlite::PAGE_SIZE);
	if (db_io_.bad()) {
		throw std::runtime_error("Error writing to database file");
	}
	db_io_.flush();
}

auto DiskManager::read_page(int const page_id, Table const& table) -> Page {
	if (page_id >= table.get_num_pages()) {
		throw std::runtime_error("Page not found");
	}
	auto const offset = page_id * mini_sqlite::PAGE_SIZE;
	db_io_.seekg(offset);
	auto data = std::array<char, mini_sqlite::PAGE_SIZE>();
	db_io_.read(data.data(), mini_sqlite::PAGE_SIZE);
	if (db_io_.bad()) {
		throw std::runtime_error("Error reading from database file");
	}

	if (auto const read_count = db_io_.gcount(); read_count < mini_sqlite::PAGE_SIZE) {
		db_io_.clear();
		memset(data.data() + read_count, 0, mini_sqlite::PAGE_SIZE - read_count);
	}
	auto page = page_id == 0 ? Page::deserialize_p0(data) : Page::deserialize(data);
	return page;
}

auto DiskManager::load_data(Table& table) -> void {
	auto& pages = table.get_pages();
	pages[0] = read_page(0, table);
	auto const& page0 = pages.front();
	table.update_num_pages(page0.get_num_pages());
	for (auto i = 1; i < table.get_num_pages(); ++i) {
		pages.push_back(read_page(i, table));
	}
}

auto DiskManager::save_data(Table& table) -> void {
	for (auto i = 0; i < table.get_num_pages(); ++i) {
		write_page(i, table);
	}
}

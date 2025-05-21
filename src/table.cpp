//
// Created by DANG BA MINH on 21/5/25.
//

#include "table.h"

Row::Row(int id, std::array<char, 32> const& name, std::array<char, 255> const& email): id{id}, name{name},
    email{email} {
}

auto Page::add_row(Row const& row) -> void {
    rows_.push_back(row);
}

auto Page::get_num_rows() const -> size_t {
    return rows_.size();
}

auto Page::get_page_size() const -> int {
    return page_size_;
}

auto Page::get_max_rows() const -> size_t {
    return max_num_rows_;
}

auto Page::get_rows() const -> std::vector<Row> {
    return rows_;
}


auto Table::allocate_page() -> void {
    pages.emplace_back();
}

auto Table::insert(Row const& row) -> void {
    if (pages.empty()) {
        pages.emplace_back();
    }
    if (
        auto const& last_page = pages.back();
        last_page.get_num_rows() >= last_page.get_max_rows()
    ) {
        allocate_page();
    }
    pages.back().add_row(row);
}

auto Table::get_rows() const -> std::vector<Row> {
    auto result = std::vector<Row>();
    for (auto const& page: pages) {
        auto rows = page.get_rows();
        result.insert(result.end(), rows.begin(), rows.end());
    }
    return result;
}






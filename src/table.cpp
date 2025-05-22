//
// Created by DANG BA MINH on 21/5/25.
//

#include "table.h"

Record::Record(int id, std::array<char, 32> const& name, std::array<char, 255> const& email): id{id}, name{name},
    email{email} {
}

auto Record::serialize() const -> std::array<char, mini_sqlite::ROW_SIZE> {
    auto data = std::array<char, mini_sqlite::ROW_SIZE>();
    std::memcpy(data.data(), &id, sizeof(id));
    std::memcpy(data.data() + sizeof(id), name.data(), 32);
    std::memcpy(data.data() + sizeof(id) + 32, email.data(), 255);
    return data;
}

Page::Page(std::vector<Record> const& rows): rows_{rows} {
}

Page::Page(int const num_pages): num_pages_{num_pages} {
}


auto Page::serialize() const -> std::array<char, mini_sqlite::PAGE_SIZE> {
    auto data = std::array<char, mini_sqlite::PAGE_SIZE>();
    auto offset = 0;
    auto const num_rows = static_cast<int>(rows_.size());
    memcpy(data.data() + offset, &num_rows, sizeof(int));
    offset += sizeof(int);
    for (auto const& row: rows_) {
        memcpy(data.data() + offset, row.serialize().data(), mini_sqlite::ROW_SIZE);
        offset += mini_sqlite::ROW_SIZE;
    }
    return data;
}

auto Page::serialize_p0() const -> std::array<char, mini_sqlite::PAGE_SIZE> {
    auto data = std::array<char, mini_sqlite::PAGE_SIZE>();
    memcpy(data.data(), &num_pages_, sizeof(int));
    return data;
}

auto Page::deserialize(const std::array<char, mini_sqlite::PAGE_SIZE>& data) -> Page {
    int num_rows;
    memcpy(&num_rows, data.data(), sizeof(int));
    auto offset = sizeof(int);
    int id;
    auto name = std::array<char, 32>();
    auto email = std::array<char, 255>();
    auto rows = std::vector<Record>();
    for (auto i = 0; i < num_rows; i++) {
        memcpy(&id, data.data() + offset, sizeof(int));
        offset += sizeof(int);
        memcpy(&name, data.data() + offset, 32);
        offset += 32;
        memcpy(&email, data.data() + offset, 255);
        offset += 255;
        rows.emplace_back(id, name, email);
    }
    return Page(rows);
};

auto Page::deserialize_p0(const std::array<char, mini_sqlite::PAGE_SIZE>& data) -> Page {
    int num_pages;
    memcpy(&num_pages, data.data(), sizeof(int));
    return Page(num_pages);
}

auto Page::add_row(Record const& row) -> void {
    rows_.push_back(row);
}

auto Page::get_num_rows() const -> size_t {
    return rows_.size();
}

auto Page::get_max_rows() const -> size_t {
    return max_num_rows_;
}

auto Page::get_rows() const -> std::vector<Record> {
    return rows_;
}

auto Page::get_num_pages() const -> int {
    return num_pages_;
}


auto Table::get_pages() -> std::vector<Page>& {
    return pages_;
}


auto Table::allocate_page() -> void {
    auto& pages = get_pages();
    pages.emplace_back();
    update_num_pages(static_cast<int>(pages.size()));
}

auto Table::insert(Record const& row) -> void {
    auto& pages = get_pages();
    if (pages.size() == 1) {
        allocate_page();
    }
    if (
        auto const& last_page = pages.back();
        last_page.get_num_rows() >= last_page.get_max_rows()
    ) {
        allocate_page();
    }
    pages.back().add_row(row);
    // TODO: do it in a more efficient way than copying.
}

auto Table::get_rows() -> std::vector<Record> {
    auto result = std::vector<Record>();
    auto pages = get_pages();
    auto it = pages.begin();
    ++it;
    for (; it != pages.end(); ++it) {
        const auto& page = *it;
        auto rows = page.get_rows();
        result.insert(result.end(), rows.begin(), rows.end());
    }
    return result;
}

auto Table::update_pages(int const page_id, Page const& page) -> void {
    if (page_id >= num_pages_) {
        throw std::runtime_error("Invalid page id");
    }
    pages_[page_id] = page;
}

auto Table::get_num_pages() const -> int {
    return num_pages_;
}

auto Table::update_num_pages(int const num_pages) -> void {
    num_pages_ = num_pages;
    // Update Page 0
    pages_.front().num_pages_ = num_pages;
    if (pages_.size() < num_pages_) {
        pages_.resize(num_pages_);
    }
}

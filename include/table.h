#ifndef TABLE_H
#define	TABLE_H
#include <vector>

/**
id          integer(8bytes)
username	varchar(32bytes)
email	    varchar(255bytes)
*/
class Row {
public:
    inline static int size = 8 + 32 + 255;

    Row(int id_, std::array<char, 32> const& name, std::array<char, 255> const& email);

    Row() = default;

    int id;
    std::array<char, 32> name;
    std::array<char, 255> email;
};

class Page {
public:
    [[nodiscard]] auto get_page_size() const -> int;

    [[nodiscard]] auto get_max_rows() const -> size_t;

    [[nodiscard]] auto get_num_rows() const -> size_t;

    [[nodiscard]] auto get_rows() const -> std::vector<Row>;

    auto add_row(Row const&) -> void;

private:
    int page_size_ = 4096;
    int max_num_rows_ = page_size_ / Row::size;
    std::vector<Row> rows_;
};

class Table {
public:
    std::vector<Page> pages;

    [[nodiscard]] auto get_rows() const -> std::vector<Row>;

    auto insert(Row const&) -> void;

private:
    auto allocate_page() -> void;
};
#endif

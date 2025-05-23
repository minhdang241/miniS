#ifndef TABLE_H
#define	TABLE_H
#include <vector>
#include <config.h>

/**
id          integer(8bytes)
username	varchar(32bytes)
email	    varchar(255bytes)
*/
class Record {
public:
    inline static int size = mini_sqlite::ROW_SIZE;

    Record(int id_, std::array<char, 32> const& name, std::array<char, 255> const& email);

    Record() = default;

    [[nodiscard]] auto serialize() const -> std::array<char, mini_sqlite::ROW_SIZE>;

    int id = -1;
    std::array<char, 32> name{};
    std::array<char, 255> email{};
};

class Page {
public:
    explicit Page(std::vector<Record> const&);

    explicit Page(int);

    Page() = default;

    auto add_row(Record const&) -> void;

    [[nodiscard]] auto get_num_pages() const -> int;

    [[nodiscard]] auto get_max_rows() const -> size_t;

    [[nodiscard]] auto get_num_rows() const -> size_t;

    [[nodiscard]] auto get_rows() const -> std::vector<Record>;

    [[nodiscard]] auto serialize() const -> std::array<char, mini_sqlite::PAGE_SIZE>;

    [[nodiscard]] auto serialize_p0() const -> std::array<char, mini_sqlite::PAGE_SIZE>;

    [[nodiscard]] static auto deserialize(const std::array<char, mini_sqlite::PAGE_SIZE>&) -> Page;

    [[nodiscard]] static auto deserialize_p0(const std::array<char, mini_sqlite::PAGE_SIZE>&) -> Page;

    friend class Table;

private:
    // When calculate the max rows, we have to subtract the memory space used to
    // store the page header (an integer keeping track of the number of rows)
    size_t max_num_rows_ = (mini_sqlite::PAGE_SIZE - sizeof(int)) / Record::size;
    int num_pages_ = 0;
    std::vector<Record> rows_;
};

class Table {
public:
    [[nodiscard]] auto get_pages() -> std::vector<Page>&;

    [[nodiscard]] auto get_rows() -> std::vector<Record>;

    [[nodiscard]] auto get_num_pages() const -> int;

    auto insert(Record const&) -> void;

    auto update_pages(int page_id, Page const& page) -> void;

    auto update_num_pages(int num_pages) -> void;

private:
    std::vector<Page> pages_ = std::vector(1, Page(1));
    int num_pages_ = 1;

    auto allocate_page() -> void;
};
#endif

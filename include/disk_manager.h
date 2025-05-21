#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H
#include <filesystem>
#include <fstream>

#include "table.h"

class DiskManager {
public:
    explicit DiskManager(std::filesystem::path const& db_file);

    /**
     * @brief : write a page to the database file
     * @param page_id
     * @param table
     */
    auto write_page(int page_id, Table& table) -> void;;

    /**
     * @brief : read a page from the database file
     * @param page_id
     * @param table
     */
    auto read_page(int page_id, const Table& table) -> Page;

    /**
     * @brief : increase database file size
     * @param : current_page_counts
     */
    auto increase_disk_space(size_t current_page_counts) -> void;

    auto load_data(Table& table) -> void;

    auto save_data(Table& table) -> void;

    DiskManager(DiskManager const&) = delete;

    DiskManager& operator=(DiskManager const&) = delete;

    DiskManager(DiskManager const&&) = delete;

    DiskManager& operator=(DiskManager const&&) = delete;

    ~DiskManager() {
        if (db_io_.is_open()) {
            db_io_.close();
        }
    };

private:
    std::fstream db_io_;
    std::filesystem::path file_name_;
    int capacity_ = mini_sqlite::DEFAULT_DB_FILE_CAPACITY;
};
#endif


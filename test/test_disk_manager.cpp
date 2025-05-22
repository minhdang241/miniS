#include <filesystem>
#include <fstream>
#include <disk_manager.h>

#include "catch2/catch.hpp"
TEST_CASE("Save data") {
    auto const filename = "minis.db";
    if (std::filesystem::exists(filename)) {
        std::filesystem::remove(filename);
    } {
        // Create a new file
        std::ofstream outFile(filename, std::ios::binary);
        outFile.close();
    }
    auto table = Table();
    constexpr auto name = std::array<char, 32>{'m', 'i', 'n', 'h', '\0'};
    constexpr auto email = std::array<char, 255>{'m', 'd', '@', 'g', 'm', 'a', 'i', 'l', '\0'};
    auto const row1 = Row(1, name, email);
    auto const row2 = Row(row1);
    auto const row3 = Row(row1);
    table.insert(row1);
    table.insert(row2);
    table.insert(row3);
    auto disk_manager = DiskManager(filename);
    disk_manager.save_data(table);
    auto page0 = disk_manager.read_page(0, table);
    CHECK(page0.get_num_pages() == 2);
    auto page1 = disk_manager.read_page(1, table);
    CHECK(page1.get_num_rows() == 3);
    // Clean up the file
    std::ofstream clear_file(filename, std::ios::trunc);
    clear_file.close();
}

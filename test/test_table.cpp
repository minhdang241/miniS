#include "catch2/catch.hpp"
#include "table.h"

TEST_CASE("insert single row") {
    auto table = Table();
    constexpr auto name = std::array<char, 32>{'m', 'i', 'n', 'h', '\0'};
    constexpr auto email = std::array<char, 255>{'m', 'd', '@', 'g', 'm', 'a', 'i', 'l', '\0'};
    auto const row = Row(1, name, email);
    table.insert(row);
    auto const rows = table.get_rows();
    CHECK(rows.size() == 1);
}

TEST_CASE("insert multiple row") {
    auto table = Table();
    constexpr auto name = std::array<char, 32>{'m', 'i', 'n', 'h', '\0'};
    constexpr auto email = std::array<char, 255>{'m', 'd', '@', 'g', 'm', 'a', 'i', 'l', '\0'};
    auto const row1 = Row(1, name, email);
    auto const row2 = Row(row1);
    auto const row3 = Row(row1);
    table.insert(row1);
    table.insert(row2);
    table.insert(row3);
    auto const rows = table.get_rows();
    CHECK(rows.size() == 3);
}

TEST_CASE("insert multiple row 2") {
    auto table = Table();
    constexpr auto name = std::array<char, 32>{'m', 'i', 'n', 'h', '\0'};
    constexpr auto email = std::array<char, 255>{'m', 'd', '@', 'g', 'm', 'a', 'i', 'l', '\0'};
    for (auto i = 0; i < 1400; ++i) {
        auto const row = Row(1, name, email);
        table.insert(row);
    }
    auto const rows = table.get_rows();
    CHECK(rows.size() == 1400);
}

TEST_CASE("select empty table") {
    auto table = Table();
    auto const rows = table.get_rows();
    CHECK(rows.empty());
}

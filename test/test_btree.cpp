#include <catch2/catch.hpp>

#include "bplus_tree.h"

TEST_CASE("insert without split") {
	auto btree = BPlusTree(3, 3);
	auto success = btree.insert(1, {1, 1});
	success = btree.insert(2, {1, 2});
	CHECK(success);
}

TEST_CASE("insert with split") {
	auto btree = BPlusTree(3, 3);
	auto success = btree.insert(1, {1, 1});
	success = btree.insert(2, {1, 2});
	success = btree.insert(3, {1, 3});
	success = btree.insert(4, {1, 4});
	success = btree.insert(5, {1, 5});
	success = btree.insert(6, {1, 6});
	success = btree.insert(7, {1, 7});
	success = btree.insert(8, {1, 8});
	// btree.print();
	CHECK(success);
}

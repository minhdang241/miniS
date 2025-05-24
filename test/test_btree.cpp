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
	success = btree.insert(9, {1, 9});
	success = btree.insert(10, {1, 10});
	btree.print();
	CHECK(success);
}

TEST_CASE("larger fanout") {
	auto btree = BPlusTree(6, 6);
	auto success = btree.insert(1, {1, 1});
	success = btree.insert(2, {1, 2});
	success = btree.insert(3, {1, 3});
	success = btree.insert(4, {1, 4});
	success = btree.insert(5, {1, 5});
	success = btree.insert(6, {1, 6});
	success = btree.insert(7, {1, 7});
	success = btree.insert(8, {1, 8});
	success = btree.insert(9, {1, 9});
	success = btree.insert(10, {1, 10});
	btree.print();
	CHECK(success);
}

TEST_CASE("find") {
	auto btree = BPlusTree(6, 6);
	auto success = btree.insert(1, {1, 1});
	success = btree.insert(2, {1, 2});
	success = btree.insert(3, {1, 3});
	success = btree.insert(4, {1, 4});
	success = btree.insert(5, {1, 5});
	success = btree.insert(6, {1, 6});
	success = btree.insert(7, {1, 7});
	success = btree.insert(8, {1, 8});
	success = btree.insert(9, {1, 9});
	success = btree.insert(10, {1, 10});

	auto pair = btree.find(9);
	CHECK(pair.first == 1);
	CHECK(pair.second == 9);

	pair = btree.find(1);
	CHECK(pair.first == 1);
	CHECK(pair.second == 1);

	pair = btree.find(5);
	CHECK(pair.first == 1);
	CHECK(pair.second == 5);
}

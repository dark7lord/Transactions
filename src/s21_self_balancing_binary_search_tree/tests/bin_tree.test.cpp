#include <gtest/gtest.h>
#include "../s21_self_balancing_binary_search_tree.h"

// class node
// Тут можно разрешить методы get_root,get_left и get_right
// и дополнить декораторами вывода
// namespace s21 {
// 	class BinTree : public SelfBalancingBinarySearchTree {

// 	}

// }
// namespace Decorator {
// 	template<typename Function>
// 	static auto make(Function&& func) {
// 		return[func = std::forward<Function>(func)](auto&&... args)
// 		{
// 			std::cout << "Do something" << std::endl;
// 			return std::invoke(func, std::forward<decltype(args)>(args)...);
// 		};
// 	}
// }


TEST(SelfBalancingBinarySearchTree, set) {
	// s21::SelfBalancingBinarySearchTree tree;
	// tree.set("Alice", (s21::Value) { "Alice", "Wonder", "1996", "Paris", "0" }, -1);

	// test nullptr
	// test TimiLimit t
	// test same key
	// а что если задать время 0, то это запись которая уже мертва без шанса пожить какое-то время?
	ASSERT_EQ(4 - 2, 2);
}

TEST(SelfBalancingBinarySearchTree, get) {
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value value = { "Bruce", "Wayne", "1996", "Gotham", "100000" };
	tree.set("Bruce", value);

	ASSERT_EQ(*tree.get("Bruce"), value);
	ASSERT_EQ(tree.get("Random key"), nullptr);
	// ASSERT_EQ(tree.get(nullptr), nullptr);
}

TEST(SelfBalancingBinarySearchTree, exists) {
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value value = { "Alice", "Wonder", "1996", "Paris", "0" };
	tree.set("Alice", value);

	ASSERT_EQ(tree.exists("Random Key"), false);
	ASSERT_EQ(tree.exists("Alice"), true);
}

TEST(SelfBalancingBinarySearchTree, del) {
	// TODO: нужно проверить что значения верные у корня взамен value
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value value = { "April", "O'Neil", "1990", "New York", "4500" };

	ASSERT_EQ(tree.del("April"), false);
	tree.set("April", value);
	ASSERT_EQ(tree.exists("April"), true);
	tree.del("April");
	ASSERT_EQ(tree.exists("April"), false);
}

TEST(SelfBalancingBinarySearchTree, update) {
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value value = { "Casey", "Jones", "1990", "New York", "400" };

	tree.set("Casey", value);
	s21::Value new_value = { "Karai", "Oruki", "1994", "Okinawa", "15400" };
	tree.update("Casey", new_value);
	s21::Value updated = *(tree.get("Casey"));
	ASSERT_EQ(updated, new_value);

	s21::Value new_value_with_skips = { "Oroki", "Saki", "-", "-", "-" };
	s21::Value expected_value = { "Oroki", "Saki", "1994", "Okinawa", "15400" };
	tree.update("Casey", new_value_with_skips);
	ASSERT_EQ( *(tree.get("Casey")), expected_value);
}

TEST(SelfBalancingBinarySearchTree, find) {
	s21::SelfBalancingBinarySearchTree tree;

	// Ninjas values
	s21::Value don = { "Donatello", "Tech Genius", "1997", "New York", "100" };
	s21::Value mike = { "Michael", "Part Dude", "1998", "New York", "70" };
	s21::Value leo = { "Leonardo", "Ninja Leader", "1996", "New York", "240" };
	s21::Value raf = { "Leonardo", "Rebel", "1997", "New York", "100" };
	s21::Value shredder = { "Oroku", "Saki", "1897", "Okinawa", "100000" };

	tree.set("Don", don);
	tree.set("Mike", mike);
	tree.set("Leo", leo);
	tree.set("Raf", don);
	tree.set("Shredder", shredder);


	s21::Value allKey = { "-", "-", "-", "-", "-" };
	auto arrKeys = tree.find(allKey);
	std::vector<s21::Key> arrKeysExpected = { "Don", "Leo", "Mike", "Raf", "Shredder" };
	ASSERT_EQ( arrKeys, arrKeysExpected);

	s21::Value keyByCity = { "-", "-", "-", "New York", "-" };
	auto keysByCity = tree.find(keyByCity);
	std::vector<s21::Key> arrKeysByCityExpected = { "Don", "Leo", "Mike", "Raf" };
	ASSERT_EQ( keysByCity, arrKeysByCityExpected);

	s21::Value key_ByCity_and_ByCoins = { "-", "-", "-", "New York", "100" };
	auto keys_ByCity_ByCoins = tree.find(key_ByCity_and_ByCoins);
	std::vector<s21::Key> keys_ByCity_ByCoins_expected = { "Don", "Raf" };
	ASSERT_EQ( keys_ByCity_ByCoins, keys_ByCity_ByCoins_expected);
}

TEST(SelfBalancingBinarySearchTree, keys) {
	s21::SelfBalancingBinarySearchTree tree;

	// Ninjas values
	s21::Value don = { "Donatello", "Tech Genius", "1997", "New York", "100" };
	s21::Value mike = { "Michael", "Part Dude", "1998", "New York", "70" };
	s21::Value leo = { "Leonardo", "Ninja Leader", "1996", "New York", "240" };
	s21::Value raf = { "Leonardo", "Rebel", "1997", "New York", "100" };

	tree.set("Don", don);
	tree.set("Mike", mike);
	tree.set("Leo", leo);
	tree.set("Raf", don);

	auto result = tree.keys();
	std::vector<s21::Key> vector_expected = { "Don", "Leo", "Mike", "Raf" };
	ASSERT_EQ( result, vector_expected);
}

TEST(SelfBalancingBinarySearchTree, rename) {
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value don = { "Donatello", "Tech Genius", "1997", "New York", "100" };

	tree.set("Don", don);
	tree.rename("Don", "Donatello");
	ASSERT_EQ(tree.get("Don"), nullptr);

	auto result = *(tree.get( "Donatello"));
	ASSERT_EQ(result, don);
}

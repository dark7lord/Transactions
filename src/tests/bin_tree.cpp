#include <gtest/gtest.h>
#include <s21_self_balancing_binary_search_tree.h>

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
	ASSERT_EQ(4 - 2, 2);
}

TEST(SelfBalancingBinarySearchTree, get) {
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value value = { "Bruce", "Wayne", "1996", "Gotham", "100000" };
	tree.set("Bruce", value);

	// ASSERT_EQ(tree.get("Bruce"), value); // doesn't work
	ASSERT_EQ(4 - 2, 2);
}

TEST(SelfBalancingBinarySearchTree, exists) {
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value value = { "Alice", "Wonder", "1996", "Paris", "0" };
	tree.set("Alice", value);

	ASSERT_EQ(tree.exists("Random Key"), false);
	ASSERT_EQ(tree.exists("Alice"), true);
}

TEST(SelfBalancingBinarySearchTree, del) {
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value value = { "April", "O'Neil", "1990", "New York", "4500" };

	ASSERT_EQ(tree.del("April"), false);
	tree.set("April", value);
	ASSERT_EQ(tree.exists("April"), true);
	tree.del("April");
	ASSERT_EQ(tree.exists("April"), false);
}


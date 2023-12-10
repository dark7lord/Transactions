#include <gtest/gtest.h>
#include "../s21_self_balancing_binary_search_tree.h"
#include <iostream>
#include <fstream>
#include <string>

TEST(SelfBalancingBinarySearchTree, set) {
	s21::SelfBalancingBinarySearchTree tree;
	tree.set("Alice", (s21::Value) { "Alice", "Wonder", "1996", "Paris", "0" }, -1);
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


TEST(SelfBalancingBinarySearchTree, save) {
	s21::SelfBalancingBinarySearchTree tree;

	s21::Value value1 = { "Naruto", "Uzumaki", "1999", "Konoha", "15" };
	s21::Value value2 = { "Haruno", "Sakura", "1998", "Konoha", "60" };
	s21::Value value3 = { "Nara", "Shikamaru", "1997", "Konoha", "80" };

	tree.set("Naruto", value1);
	tree.set("Sakura", value2);
	tree.set("Shikamaru", value3);

	// Save the tree to a file
	const std::string filename = "test_files/file_for_export.1";

	try {
		tree.save(filename);
		std::cout << "File saved successfully." << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		FAIL();  // Mark the test as failed
	}

	// Verify that the file was created
	std::ifstream input_file(filename);
	ASSERT_TRUE(input_file.good());

	// Add more assertions as needed...
}

TEST(SelfBalancingBinarySearchTree, showall) {
	s21::SelfBalancingBinarySearchTree tree;

	s21::Value value1 = { "Naruto", "Uzumaki", "1999", "Konoha", "15" };
	s21::Value value2 = { "Haruno", "Sakura", "1998", "Konoha", "60" };
	s21::Value value3 = { "Nara", "Shikamaru", "1997", "Konoha", "80" };

	tree.set("Naruto", value1);
	tree.set("Sakura", value2);
	tree.set("Shikamaru", value3);

	std::vector<s21::Value> all_values = tree.showall();
	ASSERT_EQ(all_values.size(), 3);
}

TEST(SelfBalancingBinarySearchTree, ttl) {
	s21::SelfBalancingBinarySearchTree tree;
	s21::Value value = { "Minato", "Hokage", "2001", "Konoha", "500" };

	tree.set("immortal", value);
	tree.set("has time", value, 5);
	tree.set("dead", value, 1);

	std::cout << "...Waiting sleeping... 2s" << std::endl;
	sleep(2);

	ASSERT_EQ(tree.ttl("immortal"), -1);
	ASSERT_EQ(tree.ttl("has time"), 3);
	ASSERT_EQ(tree.ttl("dead"), 0);
}

// TEST(SelfBalancingBinarySearchTree, upload) {
//     s21::SelfBalancingBinarySearchTree tree;

//     // Attempt to upload from a non-existent file
//     const std::string filename = "test_files/file_for_import.dat";

//     try {
//         tree.upload(filename);
//         std::cout << "File uploaded successfully." << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Exception caught: " << e.what() << std::endl;
//         FAIL();  // Mark the test as failed
//     }

//     // Add more assertions as needed...
// }

class FileManager {
public:
    void createFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << content;
            file.close();
        } else {
            std::cerr << "Failed to create file: " << filename << std::endl;
        }
    }

    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string content;

        if (file.is_open()) {
            std::getline(file, content);
            file.close();
        } else {
            std::cerr << "Failed to open file: " << filename << std::endl;
        }

        return content;
    }
};

TEST(FileManagerTest, CreateAndReadFile) {
    FileManager fileManager;

    // Временное имя файла для теста
    const std::string filename = "test_file.txt";

    // Содержимое, которое мы хотим записать в файл
    const std::string content = "Hello, World!";

    // Создаем файл
    fileManager.createFile(filename, content);

    // Читаем содержимое файла
    std::string readContent = fileManager.readFile(filename);

    // Проверяем, что содержимое файла совпадает с ожидаемым
    EXPECT_EQ(content, readContent);
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
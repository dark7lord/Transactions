#include <gtest/gtest.h>

#include "../s21_hash_table.h"

TEST(HashTableSet, SetValue) {
  s21::HashTable table;
  s21::Value val = {"Ivanov", "Ivan", "2000", "Rostov", "55"};
  table.set("record1", val);
  ASSERT_TRUE(table.exists("record1"));
  std::vector<s21::Key> all_keys = table.keys();
  EXPECT_EQ(all_keys.size(), 1);
  EXPECT_EQ(*(table.get("record1")), val);
}

TEST(HashTableSet, ThrowOnReset) {
  s21::HashTable table;
  table.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  EXPECT_THROW(table.set("record1", {"I", "I", "2000", "Rostov", "55"}),
               s21::IKeyValueStorage::KeyExistsException);
}

TEST(HashTableGet, ReturnsNullOnFail) {
  s21::HashTable table;
  EXPECT_EQ(table.get("hello, world"), nullptr);
}

TEST(HashTableGet, ReturnsValOnSuccess) {
  s21::HashTable table;
  s21::Value val = {"Hel", "lo", "0", "world", "1"};
  table.set("hello, world", val);
  ASSERT_NE(table.get("hello, world"), nullptr);
  EXPECT_EQ(*(table.get("hello, world")), val);
}

TEST(HashTableExists, ReturnsTrueOnSuccess) {
  s21::HashTable table;
  s21::Value val = {"Hel", "lo", "0", "world", "1"};
  table.set("hello, world", val);
  table.set("helloo, world", val);
  table.set("helllo, world", val);
  table.set("heello, world", val);
  table.set("hello, woorld", val);
  table.set("ello, world", val);
  EXPECT_TRUE(table.exists("hello, world"));
}

TEST(HashTableExists, ReturnsFalseOnFail) {
  s21::HashTable table;
  s21::Value val = {"Hel", "lo", "0", "world", "1"};
  table.set("hello, world", val);
  table.set("helloo, world", val);
  table.set("helllo, world", val);
  table.set("heello, world", val);
  table.set("hello, woorld", val);
  table.set("ello, world", val);
  EXPECT_FALSE(table.exists("hello, lord"));
}

TEST(HashTableDel, ReturnsTrueOnSuccess) {
  s21::HashTable table;
  s21::Value val = {"Hel", "lo", "0", "world", "1"};
  table.set("hello, world", val);
  table.set("helloo, world", val);
  table.set("helllo, world", val);
  table.set("heello, world", val);
  table.set("hello, woorld", val);
  table.set("ello, world", val);
  EXPECT_TRUE(table.del("hello, world"));
  std::vector<s21::Key> all_keys = table.keys();
  EXPECT_EQ(all_keys.size(), 5);
  EXPECT_FALSE(table.exists("hello, world"));
  EXPECT_TRUE(table.exists("helloo, world"));
  EXPECT_TRUE(table.del("helloo, world"));
  all_keys = table.keys();
  EXPECT_EQ(all_keys.size(), 4);
  EXPECT_FALSE(table.exists("helloo, world"));
}

TEST(HashTableDel, ReturnsFalseOnFail) {
  s21::HashTable table;
  s21::Value val = {"Hel", "lo", "0", "world", "1"};
  table.set("hello, world", val);
  table.set("helloo, world", val);
  table.set("helllo, world", val);
  table.set("heello, world", val);
  table.set("hello, woorld", val);
  table.set("ello, world", val);
  EXPECT_FALSE(table.del("hello, lord"));
  EXPECT_FALSE(table.del("hello,, lord"));
}

TEST(HashTableUpdate, UpdatePart) {
  s21::HashTable table;
  s21::Value val = {"Hel", "lo", "0", "world", "1"};
  table.set("hello, world", val);
  table.update("hello, world", {"-", "-", "-", "-", "2"});
  ASSERT_TRUE(table.exists("hello, world"));
  EXPECT_EQ(*(table.get("hello, world")),
            s21::Value({"Hel", "lo", "0", "world", "2"}));
}

TEST(HashTableUpdate, UpdateFull) {
  s21::HashTable table;
  s21::Value val = {"Hel", "lo", "0", "world", "1"};
  table.set("hello, world", val);
  s21::Value val2 = {"Hell", "loo", "3", "woorld", "4"};
  table.update("hello, world", val2);
  ASSERT_TRUE(table.exists("hello, world"));
  EXPECT_EQ(*(table.get("hello, world")), val2);
}

TEST(HashTableUpdate, ThrowOnNotExists) {
  s21::HashTable table;
  EXPECT_THROW(table.update("hello, world", {"Hel", "lo", "0", "world", "1"}),
               s21::IKeyValueStorage::KeyNotExistsException);
}

TEST(HashTableKeys, ReturnsRightSize) {
  s21::HashTable table;
  s21::Value val = {"I", "A", "2000", "S", "1"};
  table.set("1", val);
  table.set("2", val);
  table.set("3", val);
  table.set("100", val);
  table.set("0", val);
  table.set("16", val);
  table.set("32", val);
  EXPECT_EQ(table.keys().size(), 7);
  EXPECT_TRUE(table.del("100"));
  EXPECT_EQ(table.keys().size(), 6);
  EXPECT_FALSE(table.del("100"));
  EXPECT_EQ(table.keys().size(), 6);
  ASSERT_NO_THROW(table.rename("1", "4"));
  EXPECT_EQ(table.keys().size(), 6);
  ASSERT_NO_THROW(table.set("32638", val));
  EXPECT_EQ(table.keys().size(), 7);
}

TEST(HashTableShowall, ReturnsRightSize) {
  s21::HashTable table;
  s21::Value val = {"I", "A", "2000", "S", "1"};
  table.set("1", val);
  table.set("2", val);
  table.set("3", val);
  table.set("100", val);
  table.set("0", val);
  table.set("16", val);
  table.set("32", val);
  EXPECT_EQ(table.showall().size(), 7);
  EXPECT_TRUE(table.del("100"));
  EXPECT_EQ(table.showall().size(), 6);
  EXPECT_FALSE(table.del("100"));
  EXPECT_EQ(table.showall().size(), 6);
  ASSERT_NO_THROW(table.rename("1", "4"));
  EXPECT_EQ(table.showall().size(), 6);
  ASSERT_NO_THROW(table.set("32638", val));
  EXPECT_EQ(table.showall().size(), 7);
}

TEST(HashTableRename, ThrowOnNotExists) {
  s21::HashTable table;
  EXPECT_THROW(table.rename("1", "2"),
               s21::IKeyValueStorage::KeyNotExistsException);
}

TEST(HashTableRename, NoRenameOnItself) {
  s21::HashTable table;
  s21::Value val = {"I", "A", "2000", "S", "1"};
  table.set("1", val);
  EXPECT_NO_THROW(table.rename("1", "1"));
  ASSERT_TRUE(table.exists("1"));
  EXPECT_EQ(table.keys(), std::vector<s21::Key>{"1"});
}

TEST(HashTableRename, CreateNewNode) {
  s21::HashTable table;
  s21::Value val = {"I", "A", "2000", "S", "1"};
  table.set("1", val);
  EXPECT_NO_THROW(table.rename("1", "2"));
  ASSERT_TRUE(table.exists("2"));
  EXPECT_EQ(table.keys(), std::vector<s21::Key>{"2"});
}

TEST(HashTableRename, NoReplaceNode) {
  s21::HashTable table;
  s21::Value val = {"I", "A", "2000", "S", "1"};
  table.set("1", val);
  table.set("2", val);
  EXPECT_THROW(table.rename("1", "2"), s21::IKeyValueStorage::KeyExistsException);
}

TEST(HashTableFind, FindPartMatches) {
  s21::HashTable table;
  s21::Value val = {"I", "A", "2000", "S", "1"};
  table.set("1", val, 1);
  table.set("2", val, 1);
  table.update("2", {"-", "-", "-", "-", "2"});
  EXPECT_EQ(table.find({"-", "-", "-", "S", "-"}).size(), 2);
  EXPECT_EQ(table.find({"-", "-", "-", "-", "2"}).size(), 1);
}

TEST(HashTableFind, FindFullMatches) {
  s21::HashTable table;
  s21::Value val = {"I", "A", "2000", "S", "1"};
  table.set("1", val, 1);
  table.set("2", val, 1);
  table.update("2", {"-", "-", "-", "-", "2"});
  EXPECT_EQ(table.find({"I", "A", "2000", "S", "1"}).size(), 1);
  EXPECT_EQ(table.find({"I", "A", "2000", "S", "2"}).size(), 1);
}

TEST(HashTableExport, BadPermission) {
	s21::HashTable table;
	std::system("chmod 000 tests/test_files/file_for_test.dat");
	EXPECT_THROW(table.save("tests/test_files/file_for_test.dat"), s21::IKeyValueStorage::CantOpenFile);
	std::system("chmod 777 tests/test_files/file_for_test.dat");
}

TEST(HashTableUpload, NoFile) {
	s21::HashTable table;
	EXPECT_THROW(table.upload("tests/test_files/file_for_test1.dat"), s21::IKeyValueStorage::CantOpenFile);
}

TEST(HashTableUpload, BadPermission) {
	s21::HashTable table;
	std::system("chmod 000 tests/test_files/file_for_test.dat");
	EXPECT_THROW(table.upload("tests/test_files/file_for_test.dat"), s21::IKeyValueStorage::CantOpenFile);
	std::system("chmod 777 tests/test_files/file_for_test.dat");
}

TEST(HashTableUpload, GoodFiles) {
  s21::HashTable table;
  ASSERT_NO_THROW(table.upload("tests/test_files/file_for_test2.dat"));
  EXPECT_EQ(table.keys().size(), 1);
}

TEST(HashTableUpload, BadFiles) {
  s21::HashTable table;
  EXPECT_THROW(table.upload("tests/test_files/bad_file_for_test1.dat"),
               s21::IKeyValueStorage::SyntaxError);
  EXPECT_THROW(table.upload("tests/test_files/bad_file_for_test2.dat"),
               s21::IKeyValueStorage::SyntaxError);
}

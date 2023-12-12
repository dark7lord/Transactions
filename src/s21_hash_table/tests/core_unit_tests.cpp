#include <gtest/gtest.h>

#include "../s21_hash_table.h"

TEST(HashTableDefaultConstructor, CreateRightObject) {
  s21::HashTable table1;
  std::vector<s21::Key> all_keys = table1.keys();
  EXPECT_EQ(all_keys.size(), 0);
}

TEST(HashTableCopyConstructor, DoesRightCopy) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  s21::HashTable table2(table1);
  EXPECT_EQ(*table1.get("record1"), *table2.get("record1"));
  EXPECT_EQ(*table1.get("record2"), *table2.get("record2"));
}

TEST(HashTableCopyConstructor, ReallocateMemory) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  s21::HashTable table2(table1);
  EXPECT_NE(table1.get("record1"), table2.get("record1"));
  EXPECT_NE(table1.get("record2"), table2.get("record2"));
}

TEST(HashTableMoveConstructor, DoesRightMove) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  s21::Value record1 = *table1.get("record1");
  s21::Value record2 = *table1.get("record2");
  s21::HashTable table2(std::move(table1));
  EXPECT_EQ(record1, *table2.get("record1"));
  EXPECT_EQ(record2, *table2.get("record2"));
}

TEST(HashTableMoveConstructor, DoesNotReallocateMemory) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  const s21::Value* record1 = table1.get("record1");
  const s21::Value* record2 = table1.get("record2");
  s21::HashTable table2(std::move(table1));
  EXPECT_EQ(record1, table2.get("record1"));
  EXPECT_EQ(record2, table2.get("record2"));
}

TEST(HashTableCopyAssignment, DoesRightCopy) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  s21::HashTable table2;
  table2.set("record3", {"Iva", "Ivan", "2000", "Rostov", "5"});
  table2 = table1;
  EXPECT_EQ(*table1.get("record1"), *table2.get("record1"));
  EXPECT_EQ(*table1.get("record2"), *table2.get("record2"));
  EXPECT_FALSE(table2.exists("record3"));
}

TEST(HashTableCopyAssignment, ReallocateMemory) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  s21::HashTable table2;
  table2 = table1;
  EXPECT_NE(table1.get("record1"), table2.get("record1"));
  EXPECT_NE(table1.get("record2"), table2.get("record2"));
}

TEST(HashTableCopyAssignment, DoesNotChangeObjectItself) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  table1 = table1;
  EXPECT_EQ(table1.get("record1"), table1.get("record1"));
  EXPECT_EQ(table1.get("record2"), table1.get("record2"));
}

TEST(HashTableMoveAssignment, DoesRightMove) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  s21::Value record1 = *table1.get("record1");
  s21::Value record2 = *table1.get("record2");
  s21::HashTable table2;
  table2.set("record3", {"Iva", "Ivan", "2000", "Rostov", "5"});
  table2 = (std::move(table1));
  EXPECT_EQ(record1, *table2.get("record1"));
  EXPECT_EQ(record2, *table2.get("record2"));
  EXPECT_FALSE(table2.exists("record3"));
}

TEST(HashTableMoveAssignment, DoesNotReallocateMemory) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  const s21::Value* record1 = table1.get("record1");
  const s21::Value* record2 = table1.get("record2");
  s21::HashTable table2;
  table2 = (std::move(table1));
  EXPECT_EQ(record1, table2.get("record1"));
  EXPECT_EQ(record2, table2.get("record2"));
}

TEST(HashTableMoveAssignment, DoesNotChangeObjectItself) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  table1 = (std::move(table1));
  EXPECT_EQ(table1.get("record1"), table1.get("record1"));
  EXPECT_EQ(table1.get("record2"), table1.get("record2"));
}

TEST(HashTableIncreaseTable, DoesNotBrokeTable) {
  s21::HashTable table1;
  table1.set("record1", {"Ivanov", "Ivan", "2000", "Rostov", "55"});
  table1.set("record2", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  table1.set("record3", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  table1.set("record4", {"Ivanova", "Sveta", "2011", "Ufa", "1"});
  EXPECT_TRUE(table1.exists("record1"));
  EXPECT_TRUE(table1.exists("record1"));
  EXPECT_TRUE(table1.exists("record1"));
  EXPECT_TRUE(table1.exists("record1"));
  std::vector<s21::Key> all_keys = table1.keys();
  EXPECT_EQ(all_keys.size(), 4);
}

#include <gtest/gtest.h>
#include "../Lab2/HashTable.h"

class HashTableTest : public testing::Test
{
public:
	HashTable TableTest()
	{
		HashTable tmp;
		return tmp;
	}

};

TEST_F(HashTableTest, constructor)
{
	ASSERT_NO_THROW(HashTable table);
}

TEST_F(HashTableTest, copyConstructor)
{
	HashTable table1;
	ASSERT_NO_THROW(HashTable table2(table1));
}

TEST_F(HashTableTest, destructor)
{
	HashTable table;
	ASSERT_NO_THROW(table.~HashTable());
}

TEST_F(HashTableTest, empty)
{
	HashTable table;
	ASSERT_TRUE(table.empty());
	ASSERT_NO_THROW(table.insert("ABC", { 2, 3 }));
	ASSERT_FALSE(table.empty());
}

TEST_F(HashTableTest, insert)
{
	HashTable table;
	std::string key = "ABC";
	std::string keyOne = "QWE";
	int i;

	for (i = 0; i < 5; ++i)
	{
		ASSERT_TRUE(table.insert(key + std::to_string(i), { 11, 40 }));
		ASSERT_FALSE(table.insert(key + std::to_string(i), { 11, 40 }));
	}
	ASSERT_TRUE(table.insert(keyOne, { 20,11 }));
}

TEST_F(HashTableTest, contains)
{
	HashTable table;
	std::string key = "ABC";
	std::string key2 = "BFF";
	std::string key3 = "BFFF";
	std::string key4 = "BRR";
	std::string name1 = "Ivan";
	std::string name2 = "Vova";
	std::string name3 = "Petya";
	std::string name4 = "Vasya";
	std::string name5 = "Leha";

	int i;

	for (i = 0; i < 5; ++i)
	{
		ASSERT_TRUE(table.insert(key + std::to_string(i), { 2, 4 }));
		ASSERT_TRUE(table.contains(key + std::to_string(i)));
		ASSERT_FALSE(table.contains(key + std::to_string(i + 1)));

	}

	ASSERT_FALSE(table.contains(key2));
	ASSERT_FALSE(table.contains(key3));
	ASSERT_FALSE(table.contains(key4));
	ASSERT_FALSE(table.contains(name1));
	ASSERT_FALSE(table.contains(name2));
	ASSERT_FALSE(table.contains(name3));
	ASSERT_FALSE(table.contains(name4));
	ASSERT_FALSE(table.contains(name5));
}

TEST_F(HashTableTest, erase)
{
	HashTable table;
	std::string key = "ABC";
	int i;
	size_t size;

	for (i = 0; i < 5; ++i)
	{
		ASSERT_TRUE(table.insert(key + std::to_string(i), { 2, 4 }));
		ASSERT_TRUE(table.erase(key + std::to_string(i)));
	}
	ASSERT_TRUE(table.empty());
	ASSERT_FALSE(table.erase(key + std::to_string(7)));
}

TEST_F(HashTableTest, clear)
{
	HashTable table;
	std::string key = "TEST";
	table.insert(key, { 10, 20 });
	table.clear();
	ASSERT_TRUE(table.empty());
}

TEST_F(HashTableTest, at)
{
	HashTable table;
	Value v;
	v.age = 4;
	v.weight = 5;
	std::string key = "ABC";
	std::string key1 = "RED";
	unsigned int i;

	ASSERT_TRUE(table.insert(key, v));
	
	EXPECT_EQ(table.at(key).age, v.age);
	EXPECT_EQ(table.at(key).weight, v.weight);
}

TEST_F(HashTableTest, indexOperator)
{
	HashTable table;
	Value v = {4, 5};
	Value v1 = { 0, 0 };

	std::string key = "ABC";
	std::string key1 = "TYT";

	ASSERT_TRUE(table.insert(key, v));

	EXPECT_EQ(table[key].age, v.age);
	EXPECT_EQ(table[key].weight, v.weight);
	EXPECT_EQ(table[key1].age, v1.age);
	EXPECT_EQ(table[key1].weight, v1.weight);
}

TEST_F(HashTableTest, swap)
{
	HashTable table1, table2;
	std::string key = "ABC";
	int size1 = 5;
	int size2 = 25;
	int i;

	for (i = 0; i < size1; ++i)
	{
		table1.insert(key + std::to_string(i), { 11, 40 });
	}

	for (i = 0; i < size2; ++i)
	{
		table2.insert(key + std::to_string(i), { 11, 40 });
	}

	ASSERT_NO_THROW(table1.swap(table2));

}

TEST_F(HashTableTest, equalOperator)
{
	HashTable table1, table2, table3, table4;
	std::string key = "ABC";
	std::string key1 = "ABB";
	std::string key2 = "ADD";
	std::string keyOne = "QWE";
	int i = 5;

	table1.insert(key, { 31, 75 });
	table2.insert(key, { 31, 75 });
	table3.insert(key, { 31, 5 });
	
	ASSERT_TRUE(table1 == table2);
	ASSERT_FALSE(table1 == table3);

	table1.insert(key2, { 30, 77 });
	table3.insert(key1, { 30, 77 });

	ASSERT_FALSE(table1 == table3);

	table1.insert(keyOne, { 3, 4 });
	table1.insert(keyOne, { 3, 8 });
	table2.insert(keyOne, { 3, 5 });

	ASSERT_FALSE(table1 == table2);

}

TEST_F(HashTableTest, notEqualOperator)
{
	HashTable table1, table2, table3, table4;
	std::string key = "ABC";
	int i = 5;

	table1.insert(key, { 31, 75 });
	table2.insert(key, { 31, 75 });
	table3.insert(key, { 11, 5 });

	ASSERT_FALSE(table1 != table2);
	ASSERT_TRUE(table1 != table3);

}

TEST_F(HashTableTest, assignmentOperator)
{
	HashTable table1, table2;
	std::string key = "ABC";
	int size = 5;
	int i;

	for (i = 0; i < size; ++i)
	{
		table1.insert(key + std::to_string(i), { 11, 40 });
		ASSERT_NO_THROW(table2 = table1);
		ASSERT_TRUE(table1.at(key + std::to_string(i)).age == table2.at(key + std::to_string(i)).age);
		ASSERT_TRUE(table1.at(key + std::to_string(i)).weight == table2.at(key + std::to_string(i)).weight);
	}

	ASSERT_TRUE(table1 == table2);
}
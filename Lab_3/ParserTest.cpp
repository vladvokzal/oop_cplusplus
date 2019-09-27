#include <string>
#include <gtest/gtest.h>
#include "../GameLife/Parser.h"
#include "../GameLife/Field.h"
#include "../GameLife/Deserializer.h"
#include "../GameLife/Serializer.h"

class ParserTest : public testing::Test
{
public:
	Parser TestParser()
	{
		Parser parser;
		return parser;
	}
};

class DeserializerTest : public testing::Test
{
public:
	Deserializer DeserialiserTest()
	{
		Deserializer deserializer;
		return deserializer;
	}
};

class SerializerTest : public testing::Test
{
public:
	Serializer DeserialiserTest()
	{
		Serializer serializer;
		return serializer;
	}
};


TEST_F(ParserTest, parseLine)
{
	Parser parser;

	std::string correct_1 = "set 1 1";
	std::string correct_2 = "clear 9 7";
	std::string correct_3 = "reset";
	std::string correct_4 = "step";
	std::string correct_5 = "step 4";
	std::string correct_6 = "back";

	std::string incorrect_1 = "steep 1";
	std::string incorrect_2 = "step1";
	std::string incorrect_3 = "step 2 0";
	std::string incorrect_4 = "back 2 0";
	std::string incorrect_5 = "baack";
	std::string incorrect_6 = "back 3 3";
	std::string incorrect_7 = "set 44 2";
	std::string incorrect_8 = "clear 45 7";
	std::string incorrect_9 = "reset 3";
	std::string incorrect_10 = "save 0 9";
	std::string incorrect_11 = "load 5 5";

	ASSERT_NO_THROW(parser.parseCommand(correct_1));
	ASSERT_NO_THROW(parser.parseCommand(correct_2));
	ASSERT_NO_THROW(parser.parseCommand(correct_3));
	ASSERT_NO_THROW(parser.parseCommand(correct_4));
	ASSERT_NO_THROW(parser.parseCommand(correct_5));
	ASSERT_NO_THROW(parser.parseCommand(correct_6));
	

	EXPECT_ANY_THROW(parser.parseCommand(incorrect_1));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_2));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_3));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_4));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_5));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_6));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_7));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_8));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_9));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_10));
	EXPECT_ANY_THROW(parser.parseCommand(incorrect_11));
	
}

TEST_F(DeserializerTest, runRead)
{
	Deserializer deserializer;
	History history_1, history_2;
	Field field_1, field_2;

	std::string zeroName = "";
	std::string fileName = "world.txt";
	
	ASSERT_NO_THROW(deserializer.readFromFile(history_2, fileName, field_2));
	EXPECT_ANY_THROW(deserializer.readFromFile(history_1, zeroName, field_1));
}

TEST_F(SerializerTest, runLoad)
{
	Serializer serializer;
	Deserializer deserialiser;
	History history1, history2;
	Field field1, field2;

	std::string zeroName = "";
	std::string fileName = "world.txt";
	std::string outName = "output.txt";
	
	EXPECT_ANY_THROW(serializer.writeToFile(zeroName, field1));

	history2.initializeHistory();
	deserialiser.readFromFile(history2, fileName, field2);
	
	(*(field2.getField()))[3][2]->setState(true);
	
	ASSERT_NO_THROW(serializer.writeToFile(outName, field2));

}

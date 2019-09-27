#include <iostream>
#include "Strategy.h"
#include "Parser.h"
#include "View.h"
#include "Field.h"

class MyFactory
{

public:

	static Parser& getParser()
	{
		static Parser parser;
		return parser;
	}

	static ConsoleView& getView()
	{
		static ConsoleView view;
		return view;
	}

	static Field& getField()
	{
		static Field field;
		return field;
	}

	static History& getHistory()
	{
		static History history;
		return history;
	}

};
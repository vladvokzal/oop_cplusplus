#include "Parser.h"
#include "View.h"


void Parser::initializeCommandStruct()
{
	command_ = new Command;
	command_->argList = new list<string>;
}

int Parser::getInt(list<string>* argList)
{
	int currentNumber = atoi(argList->back().c_str());
	argList->pop_back();

	return currentNumber;
}


Command* Parser::readInputCommand()
{
	string input;

	getline(cin, input);
	return parseCommand(input);

}

void Parser::parseCoordinates(string& command)
{
	int number = 0;
	
	istringstream iss(command);
	
	for (int i = 0; i < 2; ++i)
	{
		if (!iss.eof())
		{
			iss >> number;
			if (number > 9)
				throw ErrorParametr("This coordinate doesn't exist on the field, only 0 - 9 ");
		}
		
		else
		{
			throw ErrorParametr("Not enough arguments for this command ");
		}
		
		command_->argList->push_back(to_string(number));
	}

	if (!iss.eof())
	{
		throw ErrorParametr("Too many arguments for this command ");
	}
		
}

void Parser::parseStep(string& command)
{
	string step = "1"; //значение по умолчанию

	istringstream iss(command);

	if (!iss.eof())
		iss >> step;
	
	if (step.size() > 4 || !atoi(step.c_str()))
	{
		throw ErrorParametr("Out of range of step ");
	}

	if(atoi(step.c_str()) < 0)
	{
		throw ErrorParametr("Step cann't be negative ");
	}
		

	if (!iss.eof())
	{
		throw ErrorParametr("Too many arguments for this step ");
	}
		
	command_->argList->push_back(step);
}

void Parser::parseReset(string& command)
{
	if (command != "")
		throw ErrorParametr("Command reset does not need any arguments");

}

Command* Parser::parseCommand(string& input)
{
	initializeCommandStruct();

	command_->Id = getCommandNumber(input);

	int offset = strlen(command_->name.c_str()) + 1;
	switch (command_->Id)
	{

	case RESET:
		parseReset(input.erase(0, offset));
		break;

	case SET:
		parseCoordinates(input.erase(0, offset));
		break;

	case CLEAR:
		parseCoordinates(input.erase(0, offset));
		break;

	case STEP:
		parseStep(input.erase(0, offset));
		break;

	case BACK:
		parseStep(input.erase(0, offset));
		break;

	case SAVE:
		parseFilename(input.erase(0, offset));
		break;

	case LOAD:
		parseFilename(input.erase(0, offset));
		break;

	default:
		break;
	}

	return command_ ;
}

int Parser::getCommandNumber(string& command)
{
	string commandArr[7] =
	{ "reset", "set", "clear", "step", "back", "save", "load" };

	string result;
	int commandNumber = -1;

	istringstream iss (command);
	
	getline(iss, result ,' ');

	//проверка имени комманды
	for (int i = 0; i < 7; ++i)
	{
		if (result == commandArr[i])
		{
			commandNumber = i;
			command_->name = commandArr[i];
			return commandNumber;
		}
		
	}
	
	throw ErrorParametr("Incorrect command, can't find it in exist command list ");
}

void Parser::parseFilename(string& command)
{
	string filename;
	
	istringstream iss(command);
	
	if (!iss.eof())
	{
		iss >> filename;
	}
		
	else
	{
		throw ErrorParametr("Zero filename ");
	}
	
	if (!iss.eof())
	{
		throw ErrorParametr("Write only one argumet - file name ");
	}

	command_->argList->push_back(filename);

}

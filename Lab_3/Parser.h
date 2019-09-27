#ifndef PARSER
#define PARSER


#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Errors.h"

using namespace std;


struct Command {
	int Id;
	string name;
	list<string>* argList;
};



class Parser
{

private:
	
	Command* command_;

	enum ComamndExist { RESET, SET, CLEAR, STEP, BACK, SAVE, LOAD };

public:
	
	//разбор введенной пользователем команды
	Command* parseCommand(string& input);

	//соответсвие команды и ее идентификатора
	int getCommandNumber(string& command);

	//получение целого числа из списка аргументов(координат x и y)
	int getInt(list<string>* argList);

	//получение команды из потока ввода
	Command* readInputCommand();
	
	//обработка координат в строке, для команд SET/CLEAR
	void parseCoordinates(string& command);

	//обработка шага игры для команды STEP/BACK
	void parseStep(string& command);

	//обработка пустой строки(предполагается) для команды RESET
	void parseReset(string& command);
	
	//обработка файла
	void parseFilename(string& command);
	
private:
	
	//создаем структуру команды
	void initializeCommandStruct();

};

#endif // !PARSER
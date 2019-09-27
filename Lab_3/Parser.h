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
	
	//������ ��������� ������������� �������
	Command* parseCommand(string& input);

	//����������� ������� � �� ��������������
	int getCommandNumber(string& command);

	//��������� ������ ����� �� ������ ����������(��������� x � y)
	int getInt(list<string>* argList);

	//��������� ������� �� ������ �����
	Command* readInputCommand();
	
	//��������� ��������� � ������, ��� ������ SET/CLEAR
	void parseCoordinates(string& command);

	//��������� ���� ���� ��� ������� STEP/BACK
	void parseStep(string& command);

	//��������� ������ ������(��������������) ��� ������� RESET
	void parseReset(string& command);
	
	//��������� �����
	void parseFilename(string& command);
	
private:
	
	//������� ��������� �������
	void initializeCommandStruct();

};

#endif // !PARSER
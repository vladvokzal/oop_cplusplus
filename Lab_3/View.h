#ifndef VIEW
#define VIEW


#include <iostream>
#include "Model.h"
#include "Field.h"

class ConsoleView 
{

public:

	//������ ����
	void printField(Field& field);

	//������ �������� ������
	void printHelp();
	
	//������ ������
	void printRules();
};

#endif // !VIEW
#ifndef VIEW
#define VIEW


#include <iostream>
#include "Model.h"
#include "Field.h"

class ConsoleView 
{

public:

	//печать поля
	void printField(Field& field);

	//печать страницы помощи
	void printHelp();
	
	//печать правил
	void printRules();
};

#endif // !VIEW
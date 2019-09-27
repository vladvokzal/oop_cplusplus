#ifndef EXECUTOR
#define EXECUTOR


#include <string>
#include "Model.h"
#include "Strategy.h"
#include "Field.h"
#include "Parser.h"
#include "View.h"
#include "MyFactory.h"

class Executor
{

public:

	//запуск синтаксического анализатора, парсера
	void startParsing(Strategy& strategy, History& history, Field& field);

	//загрузка пол€ в файл
	void runSerializer(Field& field, Command* com);
	
	//считывание пол€ из файла
	void runDeserialiser(History& history, Field& field, Command* com);

private:

	MyFactory factory;
	Parser parser = factory.getParser();

	enum ComamndExist { RESET, SET, CLEAR, STEP, BACK, SAVE, LOAD };

};

#endif // !EXECUTOR
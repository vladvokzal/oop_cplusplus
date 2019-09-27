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

	//������ ��������������� �����������, �������
	void startParsing(Strategy& strategy, History& history, Field& field);

	//�������� ���� � ����
	void runSerializer(Field& field, Command* com);
	
	//���������� ���� �� �����
	void runDeserialiser(History& history, Field& field, Command* com);

private:

	MyFactory factory;
	Parser parser = factory.getParser();

	enum ComamndExist { RESET, SET, CLEAR, STEP, BACK, SAVE, LOAD };

};

#endif // !EXECUTOR
#ifndef GAME
#define GAME

#include "Executor.h"
#include "View.h"
#include "Field.h"
#include "Strategy.h"
#include "Parser.h"
#include "Model.h"


class Game
{

public:

	//������ ����
	void runGame();

private:

	Executor executor;
	Field field;
	History history;
	ConsoleView view;
	MyFactory factory;

	//��������� �������� � �������
	void getObjectsFromFactory();

	//���������������� �������� ����� ������� ����
	void prepareNewGame();

};

#endif // !GAME
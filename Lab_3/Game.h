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

	//запуск игры
	void runGame();

private:

	Executor executor;
	Field field;
	History history;
	ConsoleView view;
	MyFactory factory;

	//получение объектов с фабрики
	void getObjectsFromFactory();

	//подготовительные действия перед началом игры
	void prepareNewGame();

};

#endif // !GAME
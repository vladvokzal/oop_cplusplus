#include "Game.h"

void Game::getObjectsFromFactory()
{
	this->field = factory.getField();
	this->history = factory.getHistory();
	this->view = factory.getView();
}

void Game::prepareNewGame()
{
	history.initializeHistory();
	view.printHelp();	
}

void Game::runGame()
{
	getObjectsFromFactory();
	prepareNewGame();

	view.printRules();
	view.printField(field);

	Strategy strategy(field, history);

	while (!cin.eof())
	{
		cout << "Enter command: ";

		try
		{
			executor.startParsing(strategy, history, field);
		}
		catch (ErrorParametr &e)
		{
			system("cls");
			std::cout << e.what() << endl;;
		}
		catch (ErrorGameOver &ec)
		{
			std::cout << ec.what() << endl;
			getchar();
			prepareNewGame();
			strategy.reset();
			system("cls");
		}

		strategy.getIterNumber();
		view.printField(field);
	}

	strategy.clearGameData();
	getchar();
}
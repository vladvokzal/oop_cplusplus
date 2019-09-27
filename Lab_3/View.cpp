#include "View.h"

using namespace std;

void ConsoleView::printRules()
{
	cout << "Welcome to Conway's Game of life!" << endl;
	cout << "Notiece the rules:" << endl;
	cout << '\t' << "1. Game turn step by step" << endl;
	cout << '\t' << "2. Game take place on tor fiel size 10x10, from 0 - 9 in column and 0-9 in row" << endl;
	cout << '\t' << "3. Each Cell have 8 neighbours (horizontal and diag.)" << endl;
	cout << '\t' << "4. If die Cell have 3 neighbour, than in next step it will be alive Cell" << endl;
	cout << '\t' << "5. If alive Cell have less than 2 alive neighbour, than it Cell die because of lonely" << endl;
	cout << '\t' << "6. If alive Cell have more than 3 alive neightbour, than it Cell die because of overpopulation" << endl;
	cout << '\t' << "7. Game is over than: " << endl;
	cout << "--------->" << "There is no alive Cells in a field" << endl;
	cout <<	"--------->" << "Avlive config. does't have any movements" << endl;
}


void ConsoleView::printHelp() 
{
	cout << "This Game accepted the following command: " << endl;
	cout << '\t' << "reset - clear the field and make counter of iterations = 0 " << endl;
	cout << '\t' << "set X Y - put the Cell at the (X,Y) position at the field" << endl;
	cout << '\t' << "clear X Y - clear (X,Y) position at the field " << endl;
	cout << '\t' << "step (N) - move game at N itetations next, without number N = 1 " << endl;
	cout << '\t' << "back - move game by 1 previous step " << endl;
	cout << '\t' << "save [filename] - save current state of a game at the [filename] " << endl;
	cout << '\t' << "load [filename] - load the state of a game from [filename] " << endl;
	
}

void ConsoleView::printField(Field& field)
{
	//field.printField();

	int SIZE = field.getFieldSize();
	auto curField = field.getField();

	cout << "  ";

	for (int k = 0; k < SIZE; k++)
		cout << k << "  ";
	cout << endl;

	for (int i = 0; i < SIZE; i++)
	{
		cout << i << " ";
		for (int j = 0; j < SIZE; j++)
		{
			if ((*curField)[i][j]->getState() == true)
				cout << "*";
			else
				cout << ".";
			cout << "  ";
		}
		cout << endl;
	}
	cout << '\n' << endl;

}

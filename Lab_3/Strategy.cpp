#include "Strategy.h"


int Strategy::modulus(int number, int SIZE)
{
	int result;
	if (number < 0)
		return (number + SIZE);
	result = number % SIZE;
	return result;
}

void Strategy::updateNeigh(int x, int y)
{
	int SIZE = field.getFieldSize();
	Cell* tmpCell = (*(field.getField()))[x][y];
	tmpCell->setDefaultNeighbour();

	//�������� ���� ������� ���������� ������
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			//������ �� ���� ������ � ������������ (x,y)
			if (i == 0 && j == 0)
				continue;

			Cell* neiCell = (*(field.getField()))[modulus((x + i), SIZE)][modulus((y + j), SIZE)];
			if (neiCell->getState())//==����� ������
				tmpCell->incrementNeighbour();
		}
	}

}

void Strategy::writeToHistory(int iteration, int x, int y, bool state)
{
	(*(history.getHistory()))[iteration].push_back({ state, x, y });
}

bool Strategy::chekIsGameOver()
{
	bool allDead = true;
	int SIZE = field.getFieldSize();
	int iteration = history.getIterations();
	auto mymap = (*(history.getHistory()));
	
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			if ((*(field.getField()))[i][j]->getState())//���� ������ �����, �� �� ��� ������
				allDead = false;

	auto iter = mymap.find(iteration);//���� ������

	//���� �� ���������� �������� ��������� �� ���� ��� ��� ������, �� ����� ����
	if ( ( iter == mymap.end() ) || (allDead == true) )
		return true;
	else
		return false;
}

void Strategy::set(int x, int y)
{
	//�������� ����� ��������
	int iteration = history.getIterations();

	Cell* cellOur = (*(field.getField()))[x][y];
	
	if (cellOur->getState())//true
		return;

	cellOur->setState(true);

	//����� � ������� ������� �������� � ���������� � ��� (x,y)
	writeToHistory(iteration, x, y, true);

	history.incrementIterations();
}

void Strategy::clear(int x, int y)
{
	int iteration = history.getIterations();

	Cell* cellOur = (*(field.getField()))[x][y];

	if (!cellOur->getState())//false
		return;

	cellOur->setState(false);

	writeToHistory(iteration, x, y, false);
	history.incrementIterations();
}

void Strategy::step(int step)
{
	int SIZE = field.getFieldSize();
	
	//��������� step ����� ����
	for (int i = 1; i <= step; ++i)
	{

	//��������� �������
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			updateNeigh(i, j);
		}
	}

	//�� ������ ���� ��������� ��� ������� �������� / ��������� ������
	conditions();
	
	if (chekIsGameOver())
	{
		throw ErrorGameOver("Game is over (field config doesn't change OR all cells die), to start again press any key... ");
	}

	history.incrementIterations();

	}

}

void Strategy::back(int backStep)
{	
	int SIZE = field.getFieldSize();
	auto mymap = (*(history.getHistory()));
	int iteration;

	Cell* tmpCell;
	
	bool state;
	int x, y;
	
	for (int i = 1; i <= backStep; ++i)
	{
		iteration = history.getIterations();
		
		if (iteration == 1)
		{
			throw ErrorParametr("This is beginning state of field, moving back undeffined ");
		}
		
		//������������� �������� back �� 1 ��� �����
		for (auto it = mymap[iteration - 1].begin(); it != mymap[iteration - 1].end(); ++it)
		{
			//�������� ��������� � ���������� ���������� ������
			state = it->state;
			x = it->x;
			y = it->y;

			tmpCell = (*(field.getField()))[x][y];

			if (state == true)
			{
				tmpCell->setState(false);
			}
			else
			{
				tmpCell->setState(true);
			}

		}

		mymap[iteration - 1].clear();

		//��������� �������
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				updateNeigh(i, j);
			}
		}

		history.decrementIterations();
	}

}


void Strategy::conditions()
{
	int i, j;
	int iteration = history.getIterations();
	int SIZE = field.getFieldSize();

	for (i = 0; i < SIZE; ++i)
	{
		for (j = 0; j < SIZE; ++j)
		{
			Cell* cellOur = (*(field.getField()))[i][j];

			if (cellOur->getState() == false && cellOur->getNeightbourCount() == 3)
			{
				cellOur->setState(true);
				writeToHistory(iteration, i, j, true);
			}
			else if (cellOur->getState() == true && (cellOur->getNeightbourCount() < 2))
			{
				cellOur->setState(false);
				writeToHistory(iteration, i, j, false);
			}
			else if (cellOur->getState() == true && (cellOur->getNeightbourCount() > 3))
			{
				cellOur->setState(false);
				writeToHistory(iteration, i, j, false);
			}
		}
	}
}

void Strategy::reset()
{
	history.clearHistory();

	auto curField = field.getField();
	int WINDOW_WIDTH = field.getFieldSize();

	for (int i = 0; i < WINDOW_WIDTH; ++i)
	{
		for (int j = 0; j < WINDOW_WIDTH; ++j)
		{
			(*curField)[i].clear();
		}
	}

	for (int i = 0; i < WINDOW_WIDTH; ++i)
	{
		for (int j = 0; j < WINDOW_WIDTH; ++j)
		{
			Cell* curCell = new Cell(false);

			(*curField)[i].push_back(curCell);
		}
	}

	history.initializeHistory();
}


void Strategy::getIterNumber()
{
	cout << "Iteration number: " << history.getIterations() << endl;
}

void Strategy::clearGameData()
{
	history.clearHistory();
}
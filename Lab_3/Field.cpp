#include "Field.h"
#include "Model.h"

Field::Field()
{
	curField = new fieldVector(WINDOW_WIDTH * WINDOW_WIDTH * sizeof(Cell));
	
	for (int i = 0; i < WINDOW_WIDTH; ++i)
	{
		for (int j = 0; j < WINDOW_WIDTH; ++j)
		{
			//создаем клетку по умолчанию мертвой и 0 соседей
			Cell* curCell = new Cell(false);

			(*curField)[i].push_back(curCell);
		}
	}
}


Field::~Field()
{	
	for (int i = 0; i < WINDOW_WIDTH; ++i)
		for (int j = 0; j < WINDOW_WIDTH; ++j)
			delete (*curField)[i][j];

	delete curField;
}

int Field::getFieldSize() const
{
	return WINDOW_WIDTH;
}

Field::fieldVector* Field::getField()
{
	return curField;
}

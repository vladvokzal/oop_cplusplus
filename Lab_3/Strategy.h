#ifndef STRATEGY
#define STRATEGY

#include "Field.h"
#include "Model.h"
#include "Errors.h"
#include "History.h"
#include <memory>


class Strategy 
{

public:

	Strategy(Field& fieldIn, History& historyIn) : field(fieldIn), history(historyIn) {}

	//установить живую клетку в позицию (x,y)
	void set(int x, int y);

	//убить клетку в позиции (x,y)
	void clear(int x, int y);

	//продвинуть игру на STEP шагов вперед
	void step(int step);

	//вернуть ход игры на 1 назад (backStep = 1)
	void back(int backStep);

	//сброс поля
	void reset();

	//получение номера итерации поля
	void getIterNumber();

	void clearGameData();

private:
	
	Field field;

	History history;

	//условия оживания/умирания клетки
	void conditions();
	
	//получение вычета x по модулю SIZE
	int modulus(int x, int SIZE);

	//обновление соседие у клеток поля
	void updateNeigh(int x, int y);

	//запись в историю игры
	void writeToHistory(int iteration, int x, int y, bool state);

	//проверить конец игры или нет
	bool chekIsGameOver();

};

#endif // !STRATEGY
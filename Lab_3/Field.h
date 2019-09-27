#ifndef FIELD
#define FIELD

#include <vector>
#include <map>
#include <list>
#include <string>
#include "Model.h"
#include "History.h"

using namespace std;

class Field
{

private:

	static const int WINDOW_WIDTH = 10;

	using CellVector = vector<Cell*>;
	using fieldVector = vector< CellVector>;

	fieldVector* curField;
	
public:
	
	Field();
	
	~Field();
	
	//получение размера поля игры
	int getFieldSize() const;

	//отдаем наше поле в пользование извне
	fieldVector* getField();
	
};

#endif // !FIELD
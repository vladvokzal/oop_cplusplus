#ifndef MODEL
#define MODEL

#include <vector>
#include <iostream>


class Cell
{

public:

	Cell(bool st = false, size_t ngh = 0) : Cellstate(st), CellNeighbour(ngh) {}
	
	void setState(bool state);
	
	bool getState();
	
	void setDefaultNeighbour();

	size_t getNeightbourCount();

	void incrementNeighbour();

private:

	bool Cellstate;

	size_t CellNeighbour;

};

#endif // !MODEL
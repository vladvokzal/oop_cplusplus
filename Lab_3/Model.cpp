#include "Model.h"



void Cell::setState(bool state)
{
	if (Cellstate == state){
		return;
	}

	Cellstate = state;
}

bool Cell::getState()
{
	return Cellstate;
}

void Cell::setDefaultNeighbour()
{
	CellNeighbour = 0;
}

size_t Cell::getNeightbourCount()
{
	return CellNeighbour;
}

void Cell::incrementNeighbour()
{
	++CellNeighbour;
}



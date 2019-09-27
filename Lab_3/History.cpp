#include "History.h"

void History::initializeHistory()
{
	map_ = new historyMap;
	iteration = 1;
}

void History::clearHistory()
{
	delete map_;
	map_ = nullptr;
}


History::historyMap* History::getHistory()
{
	return map_;
}

int History::getIterations()
{
	return iteration;
}

void History::incrementIterations()
{
	iteration++;
}

void History::decrementIterations()
{
	iteration--;
}
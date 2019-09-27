#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <map>
#include <list>
#include <string>

using namespace std;

class History
{

private:

	int iteration;

	struct History_str {
		bool state;
		int x;
		int y;
	};


	typedef map<int, list<History_str> > historyMap;

	historyMap* map_;

public:

	historyMap* getHistory();

	int getIterations();

	void incrementIterations();

	void decrementIterations();

	void initializeHistory();

	void clearHistory();

};

#endif // !HISTORY_H

#include "Deserializer.h"

void Deserializer::readFromFile(History& history, string& filename, Field& field) const
{
	string lexem;

	if (filename == "")
	{
		throw ErrorParametr("Zero file ");
	}

	ifstream fs_in;
	fs_in.open(filename.c_str());

	if (!fs_in.is_open())
	{
		throw ErrorParametr("Input file doesn't exist ");
	}

	
	history.initializeHistory();
	int SIZE = field.getFieldSize();
	Cell* curCell;

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			curCell = new Cell;

			fs_in >> lexem;

			if (lexem == "1")
			{
				curCell->setState(true);
			}
			else if (lexem == "0")
			{
				curCell->setState(false);
			}
			else
			{
				fs_in.close();
				throw ErrorParametr("Input lexem is unreadable, in file should be only '0' and '1' ");
			}

			(*(field.getField()))[i][j] = curCell;
		}
	}


	fs_in.close();

}
#include "Serializer.h"

void Serializer::writeToFile(string& filename, Field& field) const
{

	if (filename == ""){
		throw ErrorParametr("Zero file ");
	}

	int SIZE = field.getFieldSize();

	ofstream fs_out;
	fs_out.open(filename.c_str());

	Cell* curCell;

	if (!fs_out.is_open()){
		throw ErrorParametr("Can't find output file ");
	}

	for (int i = 0; i < SIZE; ++i){
		for (int j = 0; j < SIZE; ++j){
			curCell = (*(field.getField()))[i][j];
			
			if (curCell->getState()){
				fs_out << "1 ";
			}
			else{
				fs_out << "0 ";
			}
		}

		fs_out << endl;
	}

	fs_out.close();
	
}
#ifndef SERIALISER
#define SERIALISER

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Field.h"
#include "Errors.h"


using namespace std;

class Serializer
{

public:

	//������ ���� � ����
	void writeToFile(string& filename, Field& field) const;
	
};

#endif // !SERIALISER

#ifndef DESERIALIZER
#define DESERIALIZER

#include <fstream>
#include <iostream>
#include "Field.h"
#include "Errors.h"

class Deserializer
{

public:
	
	//ñ÷èòûâàíèå ïîëÿ èç ôàéëà
	void readFromFile(History& history, string& filename, Field& field) const;

};

#endif // !DESERIALIZER

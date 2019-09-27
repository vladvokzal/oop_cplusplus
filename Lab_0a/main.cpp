#include "module1.h"
#include "module2.h"
#include "module3.h"
#include <iostream>

int main(int argc, char** argv)
{
	using std::cout;
	/* Another way: 
			using namespace std; 
	But it can cause a problems soon
	*/

	cout << "Hello world!" << "\n";
	cout << Module1::getMyName() << "\n";
	cout << Module2::getMyName() << "\n";

	using namespace Module1;
	cout << getMyName() << "\n"; //(A)
	cout << Module2::getMyName() << "\n";

	using Module2::getMyName; 
	/* Also: 
			using namespace Modele2;
			std::cout<< Modele2::getMyName() << "\n";
	*/ //(B)
	cout << getMyName() << "\n"; // (C)

	using Module2::getMyName;
	cout << getMyName() << "\n"; //(D)

	using namespace Module3;
	cout << Module3::getMyName() << "\n";

}
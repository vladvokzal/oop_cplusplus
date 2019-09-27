#include <iostream>
#include <iterator>
#include <fstream>
#include <list>
#include "sort.h"

using namespace std;

int main(int argc, char** argv)
{
	int INPUT_FILE = 1; //input argument
	int OUTPUT_FILE = 2;//output argument

	ifstream fs_in(argv[INPUT_FILE]);
	ofstream fs_out(argv[OUTPUT_FILE]);

	string str;
	list<string> mylist;

	if (argc != 3)
	{
		printf("Usage: prog-name.exe <input_file> <output_file> \n");
		return 1;
	}


	if (!fs_in)
	{
		cout << "Input file doesn't exist \n";
		return 1;
	}

	while(!fs_in.eof())
	{
		getline(fs_in, str);
		mylist.push_back(str);
	}

	fs_in.close();

	using namespace sort;

	sort_strings(mylist);

	copy(mylist.begin(), mylist.end(), std::ostream_iterator<string>(fs_out));

	fs_out.close();

	return 0;
}
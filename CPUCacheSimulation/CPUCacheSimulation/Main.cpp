#include <iostream>
#include <fstream>
#include "CPUTrace.h"
#include "Cache.h"

using namespace std;

int main()
{
	ifstream fs;
	fs.open("trace.txt");

	if ( !fs.good() )
	{
		cout << "Could not open trace.txt" << endl;
		cin.ignore();
		return 0;
	}

	CPUTrace trace;
	CPUInstruction instruction;
	MainMemory memory;
	Cache cache(&memory);
	
	while (!fs.eof())
	{
		trace.GetNextInstruction(instruction, fs);

		if (instruction.isWrite())
		{
			cache.Write(instruction.getAddress(), instruction.getData());
		}
		else
		{
			cache.Read(instruction.getAddress());
		}
	}
	cin.ignore();
	return 0;
}
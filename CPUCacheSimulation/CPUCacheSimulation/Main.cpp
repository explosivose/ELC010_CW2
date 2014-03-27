#include <iostream>
#include <fstream>
#include <string>
#include "CPUTrace.h"
#include "Cache.h"

using namespace std;

int main()
{
	// ask the user for cache simulation parameters


	// open trace file for reading
	ifstream tracefile;
	tracefile.open("trace.txt");

	if ( !tracefile.good() )
	{
		cout << "Could not open trace.txt" << endl;
		cout << "Will now exit..." << endl;
		cin.ignore();
		return 0;
	}

	// open output.log for writing
	ofstream outputfile;
	outputfile.open("output.log");

	if ( !outputfile.good() )
	{
		cout << "Could not open output.log" << endl;
		cout << "Will now exit..." << endl;
		cin.ignore();
		return 0;
	}

	// redirect cout stream to outputfile stream
	streambuf *outputbuf, *backupbuf;
	backupbuf = cout.rdbuf();
	outputbuf = outputfile.rdbuf();
	cout.rdbuf(outputbuf);

	// start CPU Cache Simulation
	CPUTrace trace;
	CPUInstruction instruction;
	MainMemory memory(1048575);
	Cache cache(&memory, 1024, 2);
	
	cout << endl;
	cout << "SIMULATION START" << endl;
	cout << endl;

	while (!tracefile.eof())
	{
		trace.GetNextInstruction(instruction, tracefile);

		if (instruction.isWrite())
		{
			cout << "WRITE" << endl;
			cache.Write(instruction.getAddress(), instruction.getData());
			cout << endl;
		}
		else
		{
			cout << "READ" << endl;
			cache.Read(instruction.getAddress());
			cout << endl;
		}
	}
	tracefile.close();

	cout << endl;
	cout << "SIMULATION END" << endl;
	cout << endl;

	// restore cout stream buffer
	cout.rdbuf(backupbuf);
	outputfile.close();

	cout << "Simulation Complete." << endl;
	cout << "See output.log file for details" << endl;

	cin.ignore();
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include "CPUTrace.h"
#include "Cache.h"

using namespace std;

int main()
{
	ifstream tracefile;
	tracefile.open("trace.txt");

	if ( !tracefile.good() )
	{
		cout << "Could not open trace.txt" << endl;
		cout << "Will now exit..." << endl;
		cin.ignore();
		return 0;
	}

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
	MainMemory memory(16348);
	Cache cache(&memory);
	
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

	// restore cout stream buffer
	cout.rdbuf(backupbuf);
	outputfile.close();

	cout << "Simulation Complete. See output.log file for details" << endl;

	cin.ignore();
	return 0;
}
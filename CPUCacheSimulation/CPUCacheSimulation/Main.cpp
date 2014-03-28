#include <iostream>
#include <fstream>
#include <string>
#include "CPUTrace.h"
#include "Cache.h"

using namespace std;

int main()
{
	// ask the user for cache simulation parameters
	cout << "CPU Cache Simulation" << endl;
	cout << "Author:\tMatt Blickem" << endl;
	cout << "March 2014" << endl;
	cout << endl;

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

	// user input

	unsigned int cacheLineLength = 16;			// default line length in bytes
	unsigned int memorySize = 65535;				// default memory size in bytes
	unsigned int cacheSize = 1023;				// default cache size in bytes
	unsigned int numberOfWays = 1;				// default number of cache ways
	bool simulate = false;

	int choice;
	while (!simulate)
	{
		cout << endl << endl;
		cout << "Memory Size:\t\t" << memorySize << " Bytes" << endl;
		cout << "Cache Size:\t\t" << cacheSize << " Bytes" << endl;
		cout << "Cache Line Length:\t" << cacheLineLength << " words" << endl;
		cout << "Number of ways:\t\t" << numberOfWays << endl;
		cout << endl;
		cout << "Enter one of the following integer options:" << endl;
		cout << "1. Change Memory Size" << endl;
		cout << "2. Change Cache Size" << endl;
		cout << "3. Change Cache Line Length" << endl;
		cout << "4. Change number of ways" << endl;
		cout << "5. Start Simulation" << endl;
		for (choice = -1; !(1 <= choice && choice <= 5); )
		{
			cout << "Your choice: ";
			if(!(cin >> choice))
			{
				cout << "Invalid input." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');	// ignore everything until user presses enter
			}
		}
		switch(choice)
		{
		default:
			cout << "Invalid choice." << endl;
			break;
		case 1:
			unsigned int ms;
			for (ms = 0; !(4095 <= ms && ms <= 4194303); )
			{
				cout << "New Memory Size (4095 to 4194303 bytes): ";
				if(!(cin >> ms))
				{
					cout << "Invalid input." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	// ignore everything until user presses enter
				}
			}
			memorySize = ms;
			break;
		case 2:
			unsigned int cs;
			for (cs = 0; !(1023 <= cs && cs <= memorySize); )
			{
				cout << "New Cache Size (4095 to " << memorySize << " bytes): ";
				if(!(cin >> cs))
				{
					cout << "Invalid input." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	// ignore everything until user presses enter
				}
			}
			cacheSize = cs;
			break;
		case 3:
			unsigned int ll;
			for (ll = 0; !(ll==4 || ll==8 || ll==16); )
			{
				cout << "New Cache Line Length (4, 8 or 16 words): ";
				if(!(cin >> ll))
				{
					cout << "Invalid input." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	// ignore everything until user presses enter
				}
			}
			cacheLineLength = ll;
			break;
		case 4:
			unsigned int cw;
			for (cw = 0; !(cw==1 || cw==2 || cw==4); )
			{
				cout << "New Cache Ways (1, 2 or 4): ";
				if(!(cin >> cw))
				{
					cout << "Invalid input." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	// ignore everything until user presses enter
				}
			}
			numberOfWays = cw;
			break;
		case 5:
			simulate = true;
			break;
		}

	}
	
	// start simulation

	// redirect cout stream to outputfile stream
	streambuf *outputbuf, *backupbuf;
	backupbuf = cout.rdbuf();
	outputbuf = outputfile.rdbuf();
	cout.rdbuf(outputbuf);

	// start CPU Cache Simulation
	CPUTrace trace;
	CPUInstruction instruction;
	CacheBlock::setLineLength(cacheLineLength*4);
	MainMemory memory(memorySize);
	Cache cache(&memory, cacheSize, numberOfWays);
	
	
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
	cout << fixed << "Cache Miss Rate:\t" << cache.MissRate() << endl;

	// restore cout stream buffer
	cout.rdbuf(backupbuf);
	outputfile.close();

	cout << "Simulation Complete." << endl;
	cout << "See output.log file for details" << endl;

	cin.clear();
	cin.ignore();

	return 0;
}
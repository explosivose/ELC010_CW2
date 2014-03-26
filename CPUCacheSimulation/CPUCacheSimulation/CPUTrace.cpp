#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "CPUTrace.h"

using namespace std;

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

CPUTrace::CPUTrace(void)
{

}

CPUTrace::~CPUTrace(void)
{
}


// public functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

void CPUTrace::GetNextInstruction(CPUInstruction& i, ifstream& fs)
{
	if ( fs.good() )
	{
		string readLine;
		getline(fs, readLine);
		if (fs.eof()) return;

		bool write = false;
		unsigned int address = strtoul(readLine.substr(4, 8).c_str(), NULL, 16);
		unsigned int data = 0;
		
		// using string length to determine whether it's a read or a write
		// bad... should be using the first character which will be either R or W
		if ( readLine.length() > 13 )	
		{
			write = true;
			data = strtoul(readLine.substr(15, 8).c_str(), NULL, 16);
		}

		if ( write )
		{
			i = CPUInstruction(address, data);
		}
		else
		{
			i = CPUInstruction(address);
		}
	}
	else
	{
		cout << "Could not read trace file!" << endl;
	}
}

// Private Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//


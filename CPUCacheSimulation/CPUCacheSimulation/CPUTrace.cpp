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

// remember to document that the file must only use address and data hex values that are 4 words long
void CPUTrace::GetNextInstruction(CPUInstruction& i, ifstream& fs)
{
	if ( fs.good() )
	{
		string readLine;
		getline(fs, readLine);
		if (fs.eof()) return;

		unsigned int address = strtoul(readLine.substr(4, 8).c_str(), NULL, 16);
		unsigned int data = 0;
		
		string rw = readLine.substr(0,1);

		if ( rw == "W" || rw == "w" )	
		{
			data = strtoul(readLine.substr(15, 8).c_str(), NULL, 16);
			i = CPUInstruction(address, data);
		}
		else if ( rw == "R" || rw == "r" )
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


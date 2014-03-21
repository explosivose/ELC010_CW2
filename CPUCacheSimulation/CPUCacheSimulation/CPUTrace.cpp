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
	init();
}

CPUTrace::~CPUTrace(void)
{
}


// public functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

void CPUTrace::GetNextInstruction(CPUInstruction &i)
{
	if ( !ready ) 
	{
		cout << "Could not get next instruction!" << endl;
		return;
	}

	string readLine;
	getline(f, readLine);

	bool write = false;
	unsigned int address = strtoul(readLine.substr(5, 8).c_str(), NULL, 16);
	unsigned int data = 0;

	if ( readLine.length() > 13 )
	{
		write = true;
		data = strtoul(readLine.substr(14, 8).c_str(), NULL, 16);
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

// Private Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

void CPUTrace::init()
{
	f.open("trace.txt", ios_base::in);
	if ( !f.good() )
	{
		cout << "Could not open trace.txt" << endl;
		ready = false;
	}
	else
	{
		ready = true;
	}
}
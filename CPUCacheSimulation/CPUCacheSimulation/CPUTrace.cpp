#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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

void CPUTrace::init()
{
	fstream fs;
	string traceString;
	fs.open("trace.txt", ios_base::in);
	if ( !fs.good() )
	{
		cout << "Could not open trace.txt" << endl;
		ready = false;
	}
	else
	{
		// copy trace file contents to trace string
		fs.seekg(0, ios::end);
		traceString.reserve(fs.tellg());		// (allocating memory for string upfront)
		fs.seekg(0, ios::beg);
		traceString.assign((istreambuf_iterator<char>(fs)),istreambuf_iterator<char>());
		trace= istringstream(traceString);
		ready = true;
	}
	fs.close();
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
	getline(trace, readLine);
	

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


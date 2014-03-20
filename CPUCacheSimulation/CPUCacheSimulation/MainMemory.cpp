#include <iostream>
#include "Cache.h"

using namespace std;

// Main Memory Statics
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

// main memory length measured in bytes
// default length is 4096
unsigned int MainMemory::length = 4096;

// sets a new main memory length
// todo: resize existing data*
//		OR: do nothing if there are any instances of MainMemory
void MainMemory::setLength(const unsigned int len)
{
	MainMemory::length = len;
}

// return the length of main memory
unsigned int MainMemory::getLength()
{
	return MainMemory::length;
}

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

// constructor allocates memory for data*
MainMemory::MainMemory()
{
	Data = new unsigned int[MainMemory::length];
}

// destructor releases memory used by data*
MainMemory::~MainMemory()
{
	delete [] Data;
}

// Getter functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

unsigned int MainMemory::Read(unsigned int address)
{
	if ( ValidAddress(address) )
	{
		return Data[address];
	}
	else
	{
		return 0;
	}
}

// Setter functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

void MainMemory::Write(unsigned int address, unsigned int data)
{
	if ( ValidAddress(address) )
	{
		Data[address] = data;
	}
}

// Private Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

bool MainMemory::ValidAddress(unsigned int address)
{
	// check range of address
	if (address > MainMemory::length)
	{
		cout << "Memory address out of range!!" << endl;
		return false;
	}
	else
	{
		return true;
	}
}
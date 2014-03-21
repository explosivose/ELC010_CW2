#include <iostream>
#include "Cache.h"

using namespace std;

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

// constructor allocates memory for data*
MainMemory::MainMemory(void)
{
	length = 4096;
	Data = new unsigned int[length];
}

MainMemory::MainMemory(const unsigned int size)
{
	length = size;
	Data = new unsigned int[length];
}

// destructor releases memory used by data*
MainMemory::~MainMemory(void)
{
	delete [] Data;
}

// public functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

unsigned int MainMemory::Read(const unsigned int address)
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

void MainMemory::Write(const unsigned int address, const unsigned int data)
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

bool MainMemory::ValidAddress(const unsigned int address)
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
#include <iostream>
#include "Cache.h"

using namespace std;

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

// constructor allocates memory for data*
MainMemory::MainMemory()
{
	length = 4096;
	Data.resize(length);
	for (unsigned int i = 0; i < length; i++)
	{
		Data[i].resize(CacheBlock::getLineLengthWords(), 0);				// initialise to zero
	}
}

MainMemory::MainMemory(const unsigned int size)
{
	length = size;
	Data.resize(length);
	for (unsigned int i = 0; i < length; i++)
	{
		Data[i].resize(CacheBlock::getLineLengthWords(), 0);				// initialise to zer
	}
}

// destructor releases memory used by data*
MainMemory::~MainMemory(void)
{
	
}

// public functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

std::vector<unsigned int> MainMemory::ReadBlock(const unsigned int address)
{
	
	if ( ValidAddress(address) )
	{
		return Data[address];
	}
	else
	{
		return Data[0];
	}
}

void MainMemory::WriteBlock(const unsigned int address, const vector<unsigned int>& data)
{
	if ( ValidAddress(address) )
	{
		for (unsigned int i = 0; i < CacheBlock::getLineLengthWords(); i++)
		{
			Data[address][i] = data[i];
		}
		
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
	if (address >= MainMemory::length)
	{
		cout << "Memory address out of range!!" << endl;
		return false;
	}
	else
	{
		return true;
	}
}
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
	init();
}

MainMemory::MainMemory(const unsigned int size)
{
	length = size;
	init();
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

// initialisation
void MainMemory::init()
{
	Data.resize(length);
	for (unsigned int i = 0; i < length; i++)
	{
		Data[i].resize(CacheBlock::getLineLengthWords());
	}
	cout << "---Main Memory Parameters---" << endl;
	cout << "Memory Size:\t" << length << endl;
	cout << endl;
}

// return the length of main memory
unsigned int MainMemory::getLength()
{
	return MainMemory::length;
}

bool MainMemory::ValidAddress(const unsigned int address)
{
	// check that the first few bits of the address are zero
	// the number of bits to check is the number of bits required to express Cache Line Length 
	
	// extracting the first few bits:
	// bits = address & (powbase2(cacheLineLength) -1)
	//    Data[address][bits] 

	// (powbase2(cacheLineLength) >> address) is what should be used to index Data[]
	// then address & cache

	// check range of address
	if ( address >= MainMemory::length)
	{
		cout << "Memory address out of range!!" << endl;
		return false;
	}
	else
	{
		return true;
	}
}
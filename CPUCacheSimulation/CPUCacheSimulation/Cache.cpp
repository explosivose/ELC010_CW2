#include <iostream>
#include "Cache.h"

using namespace std;

// Cache Statics
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

// cache length measured in bytes
// default length is 1024 bytes
unsigned int Cache::length = 1024;

void Cache::setCacheLength(const unsigned int len)
{
	Cache::length = len;
}

unsigned int Cache::getCacheLength()
{
	return Cache::length;
}

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

Cache::Cache()
{
	block = new CacheBlock[Cache::length];
	cacheReady = false;
}

Cache::Cache(MainMemory* mainMemory)
{
	block = new CacheBlock[Cache::length];
	memory = mainMemory;
	cacheReady = true;
}

Cache::Cache()
{
	delete [] block;
}

// Public function
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

unsigned int Cache::Read(unsigned int address)
{

}

void Cache::Write(unsigned int address, unsigned int data)
{

}

// Private functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

bool Cache::Hit(unsigned int index, unsigned int tag)
{

}

bool Cache::ValidIndex(unsigned int index)
{
	// check range of address
	if (index > Cache::length)
	{
		cout << "Cache index out of range!!" << endl;
		return false;
	}
	else
	{
		return true;
	}
}
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include "Util.h"
#include "Cache.h"

using namespace std;

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

Cache::Cache()
{
	length = 1024;
	cacheReady = false;
}

Cache::Cache(MainMemory* mainMemory)
{
	length = 1024;
	memory = mainMemory;
	init();
}

Cache::Cache(MainMemory* mainMemory, unsigned int size)
{
	length = size;
	memory = mainMemory;
	init();
}

Cache::~Cache()
{
	
}

// Public function
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

unsigned int Cache::Read(const unsigned int address)
{
	// from address take the tag, index, select bits 
	// bits to extract = pow(2, length) - 1 << offset

	unsigned int sel = (powbase2(selectBitsLength) - 1) << 0;
	sel &= address;
	unsigned int index = (powbase2(indexLength) - 1) << selectBitsLength;
	index &= address;
	unsigned int tag = (powbase2(tagLength) - 1) << (selectBitsLength + indexLength);
	tag &= address;

	// using bitset to print binary
	std::bitset<32> b_address(address);
	std::bitset<32> b_sel(sel);
	std::bitset<32> b_index(index);
	std::bitset<32> b_tag(tag);

	cout << "Address: \t" + b_address.to_string() + " has been separated into: " << endl;
	cout << "select: \t" + b_sel.to_string() << endl;
	cout << "index: \t\t" + b_index.to_string() << endl;
	cout << "tag: \t\t" + b_tag.to_string() << endl;
	
	return 0;
}

void Cache::Write(unsigned int address, unsigned int data)
{

}

// Private functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

void Cache::init()
{
	// calculate length of bits to extract from cpu addresses
	// for log2() i'm using maths: log2(x) = log(x)/log(2)

	// number of select bits depends on the number of words in a cache line
	//		= floor(log2(CacheBlock::lineLength/4)) + 1
	//		floor(log2(16/4)) + 1 = 3 (should be 2....)
	// the select bits are the first bits in the address (from the left)
	selectBitsLength = ceil(log(CacheBlock::getLineLength()/4)/log(2));
	
	// number of index bits depends on number of cache blocks
	//		= floor(log2(Cache::length)) + 1
	//		floor(log2(1024)) + 1 = 11
	indexLength = ceil(log(length)/log(2));

	// number of tag bits depends on memory length and cache length
	//		= floor(log2(Memory::length / Cache::length)) + 1
	//		floor(log2(4096/1024)) + 1 = 3 (should be 2...)
	tagLength = ceil(log(memory->getLength()/length)/log(2));
	
	// intialise the cache blocks
	block.resize(length);
	/*
	block.reserve(length);
	for (unsigned int i = 0; i < length; i++)
		block.push_back( CacheBlock() );*/

	cacheReady = true;
}

// this function should also resize the block!
void Cache::setLength(const unsigned int len)
{
	length = len;
}

unsigned int Cache::getLength()
{
	return length;
}


bool Cache::Hit(unsigned int index, unsigned int tag)
{
	if (!ValidIndex(index)) return false;

	bool hit = false;

	if (block[index].isValid())
	{
		if (block[index].Tag() == tag)
		{
			hit = true;
		}
	}
	
	return hit;
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
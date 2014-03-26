#include <iostream>
#include <iomanip>
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
	ProcessAddress(address);	// extract sel, index and tag
	cout << hex << "Address:\t" << address << endl;
	cout << "Cache Read..." << endl;
	if (!Hit())
	{
		cout << "Cache Miss!" << endl;
		if ( block[index].isDirty() )
		{
			cout << "Writeback!" << endl;
			memory->WriteBlock(address, block[index].ReadLine());
		}
		cout << "Cache Line Fill From Memory!" << endl;
		block[index].LineFillFromMemory(tag, memory->ReadBlock(address));
	}
	else 
	{
		cout << "Cache Hit!" << endl;
	}

	unsigned int data = block[index].ReadWord(sel);

	cout << "Cache Read Data: " << hex << data << endl;
	cout << endl;
	/*
	bitset<32> b_data(block[index].ReadWord(sel));
	cout << "Data: \t\t" + b_data.to_string() + " from cache read." << endl;
	cout << endl;
	*/

	return data;
}

void Cache::Write(unsigned int address, unsigned int data)
{
	ProcessAddress(address);
	cout << hex << "Address:\t" << address << "\tData:\t" << data << endl;
	cout << "Cache Write..." << endl;
	if (!Hit())
	{
		if ( block[index].isDirty() )
		{
			cout << "Writeback!" << endl;
			memory->WriteBlock(address, block[index].ReadLine());
		}
		cout << "Cache Line Fill From Memory!" << endl;
		block[index].LineFillFromMemory(tag, memory->ReadBlock(address));
	}
	
	// re-evaluate cache hit to check that LineFillFromMemory was successful
	// maybe change LineFillFromMemory to return true on success
	if (Hit())
	{
		cout << "Write data word to cache!" << endl;
		block[index].WriteWord(sel, data);
		block[index].isDirty(true);
	}
	else
	{
		cout << "Could not write to cache!" << endl;
	}
	cout << endl;

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
	selectBitsLength = ceil(log(CacheBlock::getLineLengthWords())/log(2));
	
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

void Cache::ProcessAddress(unsigned int address)
{
	// from address take the tag, index, select bits 
	// bits to extract = pow(2, length) - 1 << offset

	sel = (powbase2(selectBitsLength) - 1) << 0;
	sel &= address;
	sel = sel >> 0;

	index = (powbase2(indexLength) - 1) << selectBitsLength;
	index &= address;
	index = index >> selectBitsLength;

	tag = (powbase2(tagLength) - 1) << (selectBitsLength + indexLength);
	tag &= address;
	tag = tag >> (selectBitsLength + indexLength);


	/* using bitset to print binary
	bitset<32> b_address(address);
	//bitset<32> b_sel(sel);
	//bitset<32> b_index(index);
	//bitset<32> b_tag(tag);

	cout << "Address: \t" + b_address.to_string() << endl;
	//cout << "select: \t"  + b_sel.to_string() << endl;
	//cout << "index: \t\t" + b_index.to_string() << endl;
	//cout << "tag: \t\t"   + b_tag.to_string() << endl;
	//*/
}

bool Cache::Hit()
{
	if (!ValidIndex()) return false;

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

bool Cache::ValidIndex()
{
	// check range of address
	if (index >= Cache::length)
	{
		cout << "Cache index out of range!!" << endl;
		return false;
	}
	else
	{
		return true;
	}
}

void Cache::Evict(unsigned int address)
{

}
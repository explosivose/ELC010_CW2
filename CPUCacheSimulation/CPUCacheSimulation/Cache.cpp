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
	ways = 1;
}

Cache::Cache(MainMemory* mainMemory)
{
	length = 1024;
	memory = mainMemory;
	ways = 1;
	init();
}

Cache::Cache(MainMemory* mainMemory, unsigned int size)
{
	length = size;
	memory = mainMemory;
	ways = 1;
	init();
}

Cache::Cache(MainMemory* mainMemory, unsigned int size, unsigned int Ways)
{
	length = size;
	memory = mainMemory;
	ways = Ways;
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
	cout << hex << "Addr:\t0x" << address << endl;
	ProcessAddress(address);	// extract sel, index and tag
	
	cout << "Cache Read..." << endl;
	unsigned int w = -1;
	for (unsigned int i = 0; i < ways; i++)
	{
		if (Hit(i)) w = i;
	}

	if( w == -1 )
	{
		cout << "Cache Miss!" << endl;
		misses++;
		w = Evict(address);
	}
	else 
	{
		cout << "Cache Hit!" << endl;
		cout << "Using way:\t" << w << endl;
		hits++;
	}

	unsigned int data = block[w][index].ReadWord(sel);
	cout << hex << "Cache Read Data: 0x" << data << endl;
	/*
	bitset<32> b_data(block[index].ReadWord(sel));
	cout << "Data: \t\t" + b_data.to_string() + " from cache read." << endl;
	cout << endl;
	*/

	return data;
}

void Cache::Write(unsigned int address, unsigned int data)
{
	cout << hex << "Addr:\t0x" << address << "\tData:\t0x" << data << endl;
	ProcessAddress(address);	// extract sel, index and tag
	cout << "Cache Write..." << endl;
	unsigned int w = -1;
	for (unsigned int i = 0; i < ways; i++)
	{
		if (Hit(i)) w = i;
	}

	if (w == -1)
	{
		cout << "Cache Miss!" << endl;
		misses++;
		w = Evict(address);
	}
	else 
	{
		cout << "Cache Hit!" << endl;
		cout << "Using way:\t" << w << endl;
		hits++;
	}
	
	cout << "Write data word to cache!" << endl;
	block[w][index].WriteWord(sel, data);
	block[w][index].isDirty(true);
	

}

float Cache::MissRate()
{
	cout << dec << "Hits:\t" << hits << "\tMisses:\t" << misses << endl;
	float m = misses;
	float hm = hits+misses;
	return m / hm;
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
	//		= ceil(log2(CacheBlock::lineLength/4)) 
	// the select bits are the first bits in the address (from the left)
	selectBitsLength = ceil(log(CacheBlock::getLineLengthWords())/log(2));
	
	// number of index bits depends on number of cache blocks
	//		= ceil(log2((Cache::length/ways)/CacheBlock::lineLength))
	indexLength = ceil(log((length/ways)/CacheBlock::getLineLengthBytes())/log(2));
	//indexLength = ceil(log(length)/log(2)); // this is incorrect!

	// number of tag bits depends on memory length and cache length
	//		= ceil(log2(Memory::length / Cache::length)) 
	//		ceil(log2(4096/1024)) = 2
	tagLength = ceil(log(memory->getLength()/length)/log(2));
	

	// intialise the cache blocks
	block.resize(ways);
	for (unsigned int w = 0; w < ways; w++)
	{
		block[w].resize(length/ways);
	}
	rr = 0;
	hits = 0;
	misses = 0;
	reads = 0;
	writes = 0;
	cacheReady = true;

	cout << "---Cache Parameters---" << endl;
	cout << "Number of ways:\t" << ways << endl;
	cout << "Cache Size:\t" << length << endl;
	cout << "Index Length:\t" << indexLength << endl;
	cout << "Tag Length:\t" << tagLength << endl;
	cout << endl;

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

	cout << hex << "Tag:\t0x" << tag << endl;
	cout << hex << "Index:\t0x" << index << endl;

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

bool Cache::Hit(unsigned int w)
{
	if (!ValidIndex()) return false;

	bool hit = false;


	if (block[w][index].isValid())
	{
		if (block[w][index].Tag() == tag)
		{
			hit = true;
		}
	}
	

	return hit;
}

bool Cache::ValidIndex()
{
	// check range of address
	if (index >= length/ways)
	{
		cout << "Cache index out of range!!" << endl;
		return false;
	}
	else
	{
		return true;
	}
}

// figure out where in main memory the indexed cache block belongs and write it back

// eviction shall select which way index to use in cache

// Evict() is called on cache miss
// find a cache block to populate
// writeback to main memory if we're using a valid dirty block
// return the ways index that was used
unsigned int Cache::Evict(unsigned int address)
{
	
	// first find invalid cache blocks to use
	for (unsigned int w = 0; w < ways; w++)
	{
		if ( !block[w][index].isValid() )
		{
			cout << "Using way:\t" << w << endl;
			cout << "Cache Fill from memory!" << endl;
			block[w][index].LineFillFromMemory(tag, memory->ReadBlock(address));
			return w;
		}
	}
	
	cout << "All mapped cache blocks are in use." << endl;

	// next favour clean cache blocks
	// this shouldn't really happen though!
	// just use round robin after failing to find invalid cache block
	for (unsigned int w = 0; w < ways; w++)
	{
		if ( !block[w][index].isDirty() )
		{
			cout << "Using way:\t" << w << endl;
			cout << "Cache fill from memory!" << endl;
			block[w][index].LineFillFromMemory(tag, memory->ReadBlock(address));
			return w;
		}
	}

	cout << "All mapped cache blocks are dirty." << endl;

	// round robin method for writebacks
	unsigned int w = rr;
	rr++;
	if (rr >= ways) rr = 0;
	cout << "Using way:\t" << w << endl;
	// reconstruct address
	unsigned int t = block[w][index].Tag() << (selectBitsLength + indexLength);
	unsigned int i = index << selectBitsLength;
	unsigned int addr = t | i;
	cout << "Writeback!" << endl;
	cout << hex << "\tAddr:\t0x" << addr << endl;
	memory->WriteBlock(addr, block[w][index].ReadLine());

	cout << "Cache line fill from memory!" << endl;
	block[w][index].LineFillFromMemory(tag, memory->ReadBlock(address));
	return w;

}	
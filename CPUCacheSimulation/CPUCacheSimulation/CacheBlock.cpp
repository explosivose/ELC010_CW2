#include <iostream>
#include "Cache.h"

using namespace std;

// Cache Block Statics
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

// Cache Line Length measured in bytes
// Default length is 16 bytes (4 data words)
unsigned int CacheBlock::lineLength = 16;

// sets a new cache line length
// in future this should also resize the line*
// or do nothing if there are any instances of CacheBlock
void CacheBlock::setLineLength(const unsigned int length)
{
	CacheBlock::lineLength = length;
}

// return the length of a cache line
unsigned int CacheBlock::getLineLengthBytes()
{
	return CacheBlock::lineLength;
}

unsigned int CacheBlock::getLineLengthWords()
{
	return CacheBlock::lineLength/4;
}

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

// constructor alocates memory for cache line
CacheBlock::CacheBlock()
{
	line.resize(CacheBlock::lineLength/4, 0);
	valid = false;
}

// destructor releases memory used by cache line
CacheBlock::~CacheBlock()
{

}

// Cache Block getters
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

// return the valid flag for this cache block
bool CacheBlock::isValid()
{
	return valid;
}

// return the dirty flag for this cache block (can only be dirty if valid)
bool CacheBlock::isDirty()
{
	return dirty && valid;
}

// return the tag for this cache block
unsigned int CacheBlock::Tag()
{
	return tag;
}

vector<unsigned int> CacheBlock::ReadLine()
{
	return line;
}

unsigned int CacheBlock::ReadWord(const unsigned int offset)
{
	if (offset > CacheBlock::lineLength)
	{
		cout << "Error! Data offset greater than cache line length" << endl;
		return 0;
	}
	
	return line[offset];
}

// Cache Block setters
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
// 

// set the valid flag for this cache block
void CacheBlock::isValid(const bool v)
{
	valid = v;
}

// set the dirty flag for this cache block
void CacheBlock::isDirty(const bool d)
{
	dirty = d;
}

void CacheBlock::WriteWord(const unsigned int offset, const unsigned int data)
{
	if (offset > line.size())
	{
		cout << "Error! Data offset greater than cache line length" << endl;
		return;
	}
	line[offset] = data;
}

	// problem with the two LineFill functions: size of data[] cannot be determined here.
	// if size of data[] is less than CacheBlock::lineLength, we're writing garbage to line[]!
	// use C++ vectors instead? then change function to return bool indicating success
	//	(another advantage of using vectors instead: much easier to debug! data in vectors is exposed to debugger)
	// or ensure that only memory blocks are passed somehow (since their size is always CacheBlock::lineLength)

// fill the cache line with data
void CacheBlock::LineFillFromCPU(const unsigned int Tag, const vector<unsigned int>& data)
{
	if (line.size() == data.size())
	{
		tag = Tag;
		valid = true;
		dirty = true;
		line = data;
	}
	else
	{
		cout << "Line Fill Error: CPU data size differs to cache line size!" << endl;
	}
}

void CacheBlock::LineFillFromMemory(const unsigned int Tag, const vector<unsigned int>& data)
{
	if (line.size() == data.size())
	{
		tag = Tag;
		valid = true;
		dirty = false;
		line = data;
	}
	else
	{
		cout << "Line Fill Error: Memory block size differs to cache line size!" << endl;
	}
}
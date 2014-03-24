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
unsigned int CacheBlock::getLineLength()
{
	return CacheBlock::lineLength;
}

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

// constructor alocates memory for cache line
CacheBlock::CacheBlock()
{
	line = new unsigned int[CacheBlock::lineLength]();
	valid = false;
}

// destructor releases memory used by cache line
CacheBlock::~CacheBlock()
{
	delete[] line;
	line = 0;
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

// return the dirty flag for this cache block
bool CacheBlock::isDirty()
{
	return dirty;
}

// return the tag for this cache block
unsigned int CacheBlock::Tag()
{
	return tag;
}

unsigned int CacheBlock::ReadData(const unsigned int offset)
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

// fill the cache line with data
void CacheBlock::LineFill(const unsigned int Tag, const unsigned int* data)
{
	tag = Tag;
	for (unsigned int i = 0; i < CacheBlock::lineLength; i++)
	{
		line[i] = data[i];
	}
}
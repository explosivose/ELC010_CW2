#include "types.h"
#include "Cache.h"

/// Length is measured in bytes
/// Default length is 4 words, 16 bytes, 128 bits
u16 CacheLine::Length = 16;

/// DataLength is measured in bytes
/// Default length is 1 word, 4 bytes, 32 bits
u16 CacheLine::DataLength = 4;

/// IndexLength is measured in bytes
/// Default length is 6 bits
u16 CacheLine::IndexLength = 1;

/// TagLength is measured in bytes
/// Default length is 2 bits
u16 CacheLine::TagLength = 1;

CacheLine::CacheLine()
{
    pLine = new u8[Length];
}

CacheLine::~CacheLine()
{
    delete [] pLine;
}

bool CacheLine::IsValid()
{
    return (pLine[0] != 0);
}

u16 CacheLine::getLength()
{
    return Length;
}

#include <types.h>
#include <Cache.h>

/****   Cache Line byte map
    [ 0] valid flag (bool)
    [ 1] dirty bit (bool)
    [ 2] tag
    [ 3] data
    [ 4] data
    [ 5] data
    [ 6] data
    [ 7]
    [ 8]
    [ 9]
    [10]
    [11]
    [12]
    [13]
    [14]
    [15]
 ****/

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

u16 CacheLine::getLength()
{
    return Length;
}

bool CacheLine::IsValid()
{
    return (pLine[0] != 0);
}

bool CacheLine::IsDirty()
{
    return (pLine[1] != 0);
}

u8 CacheLine::getTag()
{
    return pLine[2];
}



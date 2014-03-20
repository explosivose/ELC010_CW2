#include <types.h>
#include <Cache.h>

/* Cache Byte Map

[ 0] valid flag (bool)
[ 1] dirty flag (bool)
[ 2] tag (2 bit for task one)
[ 3] data word 1
[ 4] data word 1
[ 5] data word 1
[ 6] data word 1
[ 7] data word 2
[ 8] data word 2
[ 9] data word 2
[10] data word 2
[11] data word 3
[12] data word 3
[13] data word 3
[14] data word 3
[15] data word 4
[16] data word 4
[17] data word 4
[18] data word 4

*/

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



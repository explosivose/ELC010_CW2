#include "types.h"
#include "Cache.h"

Cache::Cache()
{
    Size = 1024;
    LineCount = Size / CacheLine::getLength();
    pLine = new CacheLine[LineCount];
}

Cache::~Cache()
{
    delete [] pLine;
}

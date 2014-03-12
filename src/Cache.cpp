#include <types.h>
#include <Cache.h>
#include <math.h>

Cache::Cache()
{
    Size = 1024;
    LineCount = Size / CacheLine::getLength();

    u16 r = LineCount % 8;
    if (r != 0) IndexLength = LineCount + 8 - r;
    IndexLength = log2(LineCount);


    pLine = new CacheLine[LineCount];
}

Cache::~Cache()
{
    delete [] pLine;
}

u32 Cache::Read(u32 address)
{


    // Cache hit?

        // no
            // locate cache line to use
            // if its valid & dirty do a writeback then evict
            // copy data from main memory into cache line
            // mark as valid & not dirty
        //yes
            //return data

}

void Cache::Write(u32 address, u32 data)
{
    // Cache hit?
        // no
            // locate cache line to use
            // if its valid & dirty do a writeback then evict
            // copy u32data into cache line
            // mark as dirty
        // yes
            // write new data into cache line
            // mark as dirty
}

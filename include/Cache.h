/****   Cache Line Basics
    *   one byte (B) is 8 bits (b)
    *   one word is 4 bytes (32 bit word)

    *   cache line length is 4 words (16 bytes, 128 bits)
    *   data is 1 word (4 bytes, 32 bits)

    *   number of cache lines = cache memory (1024B) / cache line length (16B) = 64 (2^6)
    *   6 bit index

    *   4096 bytes / 1024 bytes = 4 (2^2)
    *   2 bit tag
    *   there are four memory locations mapped to each cache line

    *   128 bits in a cache line, 6 bit index, 2 bit tag, 1 bit valid flag, 1 dirty bit
 ****/

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

class CacheLine
{
    public:
        CacheLine();
        ~CacheLine();
        bool IsValid();
        static u16 getLength();
    protected:
    private:
        static u16 Length;          // 4 words, 16 bytes, 128 bits
        static u16 DataLength;      // 1 words,  4 bytes,  32 bits
        static u16 IndexLength;     // 0 words,  0 bytes,   6 bits
        static u16 TagLength;       // 0 words,  0 bytes,   2 bits
        u8* pLine;
};


/****   Cache Basics
    *   one byte (B) is 8 bits (b)
    *   one word is 4 bytes (32 bit word)
    *   main memory is 4096 bytes
    *   cache memory is 1024 bytes
    *   cache is direct mapped to main memory

    *   number of cache lines = cache memory (1024B) / cache line length (16B) = 64 (2^6)
    *   6 bit index
    *   2 bit tag
    *   there are four memory locations mapped to each cache line
 ****/
class Cache
{
    public:
        Cache();
        ~Cache();
    protected:
    private:
        u16 Size;           // The number of bytes in the cache
        u16 LineCount;
        CacheLine* pLine;
};

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



class CacheLine
{
    public:
        CacheLine();
        ~CacheLine();
        bool IsValid();             // if true: contains a valid copy of main memory data
        bool IsDirty();             // if true: data has been modified and needs to be written back to main memory
        u8 getTag();
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
    *   main memory is 4096 bytes (2^12)
    *   cache memory is 1024 bytes (2^10)
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
        u32 Read(u32);       // memory request from CPU
        void Write(u32, u32);
    protected:
    private:
        u16 Size;           // The number of bytes in the cache
        u16 LineCount;      // number of cache lines
        u16 IndexLength;    // number of bytes required to index cache length
        CacheLine* pLine;
};

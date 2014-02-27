#include <iostream>

using namespace std;

/****   Task 1 Cache Memory Simulation
    *   one byte (B) is 8 bits (b)
    *   one word is 4 bytes (32 bit word)
    *   main memory is 4096 bytes
    *   cache memory is 1024 bytes
    *   cache is direct mapped to main memory
    *   cache line length is 4 words (16 bytes, 128 bits)
    *   data is 1 word (4 bytes, 32 bits)

    *   number of cache lines = cache memory (1024B) / cache line length (16B) = 64 (2^6)
    *   6 bit index

    *   4096 bytes / 1024 bytes = 4 (2^2)
    *   2 bit tag
    *   there are four memory locations mapped to each cache line

    *   128 bits in a cache line, 6 bit index, 2 bit tag, 1 bit valid flag,
 ****/

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

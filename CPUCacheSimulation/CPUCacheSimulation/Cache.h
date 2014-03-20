#include <vector>

/* Cache Simulation

Implemented as Cache container class and CacheBlock class

Cache Byte Map

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

Cache Line Word Map
[ 1] (int) data word
[ 2] (int) data word
[ 3] (int) data word
[ 4] (int) data word

*/

class MainMemory
{
	public:

		// class statics
		// note probably don't need statics for MainMemory!
		// because there's only ever gonna be one mainMemory...
		static void setLength(const unsigned int);
		static unsigned int getLength();

		// constructor / destructor
		MainMemory();
		~MainMemory();

		unsigned int Read(unsigned int address);				// return data at memory address
		void Write(unsigned int address, unsigned int data);	// write data to memory address

	private:

		static unsigned int length;
		unsigned int* Data;

		bool ValidAddress(unsigned int address);
};

class CacheBlock
{
	public:
		
		// class statics
		static void setLineLength(const unsigned int);
		static unsigned int getLineLength();
		
		// constructor / destructor
		CacheBlock();
		~CacheBlock();
		
		// getters
		bool isValid();
		bool isDirty();
		int Tag();											// returns the tag of this block
		int ReadData(const unsigned int);					// returns a data word from the cache line

		// setters
		void isValid(const bool);
		void isDirty(const bool);
		void LineFill(const unsigned int*);					// copy data into cache line
	
	private:
		
		static unsigned int lineLength;
		bool valid;
		bool dirty;
		int tag;	
		unsigned int* line;
		
};



class Cache
{
	public:

		// class statics
		// note: probably dont need statics for Cache!
		// because there's only ever gonna be one cache here...
		static void setLength(const unsigned int);
		static unsigned int getLength();

		// constructor / destructor
		Cache();
		Cache(MainMemory*);
		~Cache();

		unsigned int Read(unsigned int address);				// return data at memory address
		void Write(unsigned int address, unsigned int data);	// write data to memory address

	private:

		static unsigned int length;

		void init();
		bool Hit(unsigned int index, unsigned int tag);		// true or false for cache hit
		bool ValidIndex(unsigned int index);				// check address range
		
		bool cacheReady;									// false if no reference to MainMemory;
		unsigned int selectBitsLength;						// number of bits required to select a data word
		unsigned int indexLength;							// number of bits required to index the cache
		unsigned int tagLength;								// number of bits required for tag

		MainMemory* memory;									// pointer to single instance of main memory
		std::vector<CacheBlock> block;							// dynamic array of cache blocks

};
#include <ostream>
#include "CPUTrace.h"
#include "Cache.h"

using namespace std;

int main()
{
	CPUTrace trace;
	CPUInstruction instruction;
	MainMemory memory;
	Cache cache;

	trace = CPUTrace();
	memory = MainMemory();
	cache = Cache(&memory);

	trace.GetNextInstruction(instruction);

	if (instruction.isWrite())
	{
		cache.Write(instruction.getAddress(), instruction.getData());
	}
	else
	{
		cache.Read(instruction.getAddress());
	}

	return 0;
}
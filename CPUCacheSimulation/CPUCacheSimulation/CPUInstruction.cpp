#include "CPUTrace.h"

using namespace std;

// Constructor / Destructor
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//

CPUInstruction::CPUInstruction(void)
{
	write = false;
	address = 0;
	data = 0;
}

CPUInstruction::CPUInstruction(const unsigned int Address)
{
	write = false;
	address = Address;
	data = 0;
}

CPUInstruction::CPUInstruction(const unsigned int Address, const unsigned int Data)
{
	write = true;
	address = Address;
	data = Data;
}

CPUInstruction::~CPUInstruction(void)
{
}


// public functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

bool CPUInstruction::isWrite()
{
	return write;
}

unsigned int CPUInstruction::getAddress()
{
	return address;
}

unsigned int CPUInstruction::getData()
{
	return data;
}

// Private Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
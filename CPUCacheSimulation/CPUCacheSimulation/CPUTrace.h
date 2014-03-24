#pragma once
#include <sstream>

class CPUInstruction
{
	public:
		CPUInstruction(void);
		CPUInstruction(const unsigned int address);
		CPUInstruction(const unsigned int address, const unsigned int data);
		~CPUInstruction(void);
		bool isWrite();
		unsigned int getAddress();
		unsigned int getData();
	private:	
		bool write;
		unsigned int address;
		unsigned int data;
};

class CPUTrace
{
	public:
		CPUTrace(void);
		~CPUTrace(void);
		void GetNextInstruction(CPUInstruction&);
	private:
		void init();
		std::istringstream trace;	// can't be doing this....

		// suggest that fstream exists in main and CPUTrace::GetNextInstruction(CPUInstruction& i, fstream& fs)
		
		bool ready;
		
};


#pragma once
#include<fstream>

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
		void GetNextInstruction(CPUInstruction&, std::ifstream&);
	private:


};


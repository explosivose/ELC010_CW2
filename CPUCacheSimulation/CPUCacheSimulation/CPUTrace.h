#pragma once

using namespace std;

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
		
		bool ready;
		fstream f;
};


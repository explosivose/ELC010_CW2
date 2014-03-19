#include <types.h>
#include <iostream>             // required for cout
#include <fstream>              // required for fstream
#include <string>               // required for string overloads of fstream methods
#include <cstdlib>              // required for strtoul()
#include <CPUInstruction.h>
#include <CPUTrace.h>

using namespace std;

/// CONSTRUCTOR
CPUTrace::CPUTrace()
{
    init();
}

/// DESTRUCTOR
CPUTrace::~CPUTrace()
{
    //dtor
}

/// PUBLIC METHODS
void CPUTrace::GetNextInstruction(CPUInstruction &i)
{
    string readLine;
    getline(f, readLine);

    u32 address = strtoul(readLine.substr(5, 8).c_str(), NULL, 16 );
    i.setAddress(address);

    if ( readLine.length() < 13 )
    {
        i.setRead();
    }
    else
    {
        i.setWrite();
        u32 data = strtoul(readLine.substr(14, 8).c_str(), NULL, 16 );
        i.setData(data);
    }
}

/// PRIVATE METHODS
void CPUTrace::init()
{
    f.open("trace.txt", ios_base::in);
    if ( !f.good() )
    {
        cout << "Could not open trace.txt" << endl;
        ready = false;
    }
    else
    {
        ready = true;
    }
}


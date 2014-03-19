#ifndef CPUTRACE_H
#define CPUTRACE_H

using namespace std;

class CPUTrace
{
    public:
        CPUTrace();
        void GetNextInstruction(CPUInstruction &i);
        ~CPUTrace();
    private:
        bool ready = false;
        fstream f;

        void init();
};

#endif // CPUTRACE_H

#ifndef CPUINSTRUCTION_H
#define CPUINSTRUCTION_H


class CPUInstruction
{
    public:
        CPUInstruction();
        CPUInstruction(u32 address);
        CPUInstruction(u32 address, u32 data);
        u32 Address();
        void setAddress(u32);
        u32 Data();
        void setData(u32);
        bool IsRead();
        void setRead();
        bool IsWrite();
        void setWrite();
        ~CPUInstruction();
    private:
        bool m_Write = false;
        u32 m_Address = 0;
        u32 m_Data = 0;
};

#endif // CPUINSTRUCTION_H

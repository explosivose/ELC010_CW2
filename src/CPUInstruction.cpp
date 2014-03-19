#include <types.h>
#include <CPUInstruction.h>


CPUInstruction::CPUInstruction()
{
    //ctor
}

CPUInstruction::CPUInstruction(u32 address)
{
    m_Write = false;
    m_Address = address;
}

CPUInstruction::CPUInstruction(u32 address, u32 data)
{
    m_Write = true;
    m_Address = address;
    m_Data = data;
}

void CPUInstruction::setAddress(u32 address)
{
    m_Address = address;
}

u32 CPUInstruction::Address()
{
    return m_Address;
}

void CPUInstruction::setData(u32 data)
{
    m_Data = data;
}

u32 CPUInstruction::Data()
{
    return m_Data;
}

void CPUInstruction::setRead()
{
    m_Write = false;
}

bool CPUInstruction::IsRead()
{
    return !m_Write;
}

void CPUInstruction::setWrite()
{
    m_Write = true;
}

bool CPUInstruction::IsWrite()
{
    return m_Write;
}

CPUInstruction::~CPUInstruction()
{
    //dtor
}

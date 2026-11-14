// Z:\Toshi\Source\TKernel\TDateTime.cpp - wall-clock time and its packed form.
#define TOSHI_KERNEL_BUILD
#define TOSHI_API __declspec(dllexport)
#include "TKernelMisc.h"

namespace Toshi {

// date: year in bits 16-31, month in bits 8-15, day in bits 0-7.
// time: hour in bits 24-31, minute in bits 16-23, second in bits 8-15 (the low byte is unused).
void TDateTime::Pack(unsigned int& date, unsigned int& time)
{
    date = (year << 16) | (month << 8) | day;
    time = (hour << 24) | (minute << 16) | (second << 8);
}

void TDateTime::UnPack(unsigned int& date, unsigned int& time)
{
    year = (unsigned short)(date >> 16);
    month = (unsigned char)(date >> 8);
    day = (unsigned char)date;
    hour = (unsigned char)(time >> 24);
    minute = (unsigned char)(time >> 16);
    second = (unsigned char)(time >> 8);
}

} // namespace Toshi

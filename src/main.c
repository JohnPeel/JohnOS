/*
    This file is part of JohnOS.

    JohnOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    JohnOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with JohnOS.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <main.h>

#define asm __asm__ __volatile__

inline void outb(unsigned short port, unsigned char val)
{
    asm("outb %0, %1" : : "a"(val), "Nd"(port));
}

inline void outw(unsigned short port, unsigned int val)
{
    asm("outw %0, %1" : : "a"(val), "Nd"(port));
}

inline void outl(unsigned short port, unsigned long val)
{
    asm("outl %0, %1" : : "a"(val), "Nd"(port));
}

inline unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

inline unsigned int inw(unsigned short port)
{
    unsigned int ret;
    asm("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

inline unsigned long inl(unsigned short port)
{
    unsigned long ret;
    asm("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void main(void)
{
    unsigned char *videoram = (unsigned char *) 0xb8000;
    videoram[0] = 65;
    videoram[1] = 0x07;
    
    for (;;);
}
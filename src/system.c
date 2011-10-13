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

#include <system.h>

void outb(uint16_t port, uint8_t val)
{
	asm("outb %0, %1" : : "a"(val), "Nd"(port));
}

void outw(uint16_t port, uint16_t val)
{
	asm("outw %0, %1" : : "a"(val), "Nd"(port));
}

void outl(uint16_t port, uint32_t val)
{
	asm("outl %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm("inw %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

uint32_t inl(uint16_t port)
{
	uint32_t ret;
	asm("inl %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

void io_wait(void)
{
	asm("outb %%al, $0x80" : : "a"(0));
}

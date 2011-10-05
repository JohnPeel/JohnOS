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

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#define asm __asm__ __volatile__

extern void outb(unsigned short port, unsigned char val);
extern void outw(unsigned short port, unsigned int val);
extern void outl(unsigned short port, unsigned long val);
extern unsigned char inb(unsigned short port);
extern unsigned int inw(unsigned short port);
extern unsigned long inl(unsigned short port);

#endif
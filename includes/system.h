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

#include <stdint.h>

#define asm __asm__ __volatile__

extern void outb(uint16_t port, uint8_t val);
extern void outw(uint16_t port, uint16_t val);
extern void outl(uint16_t port, uint32_t val);
extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);
extern uint32_t inl(uint16_t port);
extern void io_wait(void);

#endif
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

#ifndef __SCREEN_H_
#define __SCREEN_H_

#include <stdint.h>

#define LINE_LENGTH 0x50

extern uint16_t *vmem;
extern uint8_t attrib;

extern void clear_line(const uint8_t line);
extern void cls(void);
extern void update_csr(const uint8_t x, const uint8_t y);
extern void set_char(uint8_t x, uint8_t y, const uint8_t c);
extern void set_line(const uint8_t line, const int8_t *str);
extern void setattrib(const uint8_t fg, const uint8_t bg);
extern void init_video(void);

#endif
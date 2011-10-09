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

#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include <stdint.h>

#define CONSOLE_LINE_LENGTH 0x4E
#define CONSOLE_BUFFER_LENGTH 0x666

extern int8_t buffer[CONSOLE_BUFFER_LENGTH];

extern void console_clear_line(const uint8_t line);
extern void console_clear(void);
extern void console_update(void);
extern void console_set_line(const uint8_t line, const int8_t *s);
extern void console_print(const char *s);
extern void console_setup(void);

#endif
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

extern unsigned short *vmem;
extern unsigned short attrib;

extern void clear_line(const int line);
extern void cls(void);
extern void update_csr(const unsigned char x, const unsigned char y);
extern void set_char(unsigned char x, unsigned char y, const char c);
extern void set_line(const int line, const char *str);
extern void setattrib(const char fg, const char bg);
extern void init_video(void);

#endif
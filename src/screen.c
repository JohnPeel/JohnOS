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

#include <screen.h>
#include <system.h>
#include <string.h>

unsigned short *vmem;
unsigned short attrib = 0x07;

void clear_line(const int line)
{
	memsetw(vmem + (line * 80), 0x20 + (attrib << 8), 80);
}

void cls(void)
{
	int i;
	for (i = 0; i < 25; i++)
		clear_line(i);
}

void update_csr(const unsigned char x, const unsigned char y)
{
	unsigned int c = (unsigned int)((y * 80) + x);
	
	outb(0x3D4, 14);
	io_wait();
	outb(0x3D5, (unsigned char)((c >> 8) & 0xFF));
	io_wait();
	outb(0x3D4, 15);
	io_wait();
	outb(0x3D5, (unsigned char)(c & 0xFF));
	io_wait();
}

void set_char(unsigned char x, unsigned char y, const char c)
{
	unsigned int *n = (unsigned int *)&vmem[y * 80 + x];
	*n = (unsigned int)(c | (attrib << 8));
}

void set_line(const int line, const char *str) {
	clear_line(line);
	unsigned char x = 0, y = (unsigned char)line;
	int i;
	for (i = 0; i < strlen(str); i++) {
		switch (str[i]) {
			case '\n':
				x = 0;
				y++;
				break;
			case 0x09:
				x = (unsigned char)((x + 8) & ~(8 - 1));
				break;
			case '\r':
				x = 0;
				break;
			default:
				set_char(x++, y, str[i]);
				break;
		}
		
		if (x >= 80) {
			x = 0;
			y++;
		}
	}
	update_csr(x, y);
}

void setattrib(const char fg, const char bg)
{
	attrib = (unsigned short)((bg << 4) + (fg & 0x0F));
}

void init_video(void)
{
	vmem = (unsigned short *)0xB8000;
	cls();
}
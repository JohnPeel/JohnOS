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

uint16_t *vmem;
uint8_t attrib = 0x07;

void clear_line(const uint8_t line)
{
	memsetw(vmem + (line * 80), 0x20 + (attrib << 8), 80);
}

void cls(void)
{
	uint8_t i;
	for (i = 0; i < 25; i++)
		clear_line(i);
}

void update_csr(const uint8_t x, const uint8_t y)
{
	uint16_t c = (uint16_t)((y * 80) + x);

	outb(0x3D4, 14);
	io_wait();
	outb(0x3D5, (uint8_t)((c >> 8) & 0xFF));
	io_wait();
	outb(0x3D4, 15);
	io_wait();
	outb(0x3D5, (uint8_t)(c & 0xFF));
	io_wait();
}

void set_char(uint8_t x, uint8_t y, const uint8_t c)
{
	uint16_t *n = &vmem[y * 80 + x];
	*n = (uint16_t)(c | (attrib << 8));
}

void set_line(const uint8_t line, const int8_t *str)
{
	clear_line(line);
	uint8_t x = 0, y = line;
	int32_t i;
	for (i = 0; i < strlen(str); i++) {
		switch (str[i]) {
			case '\n':
				x = 0;
				y++;
				break;
			case 0x09:
				x = (uint8_t)((x + 8) & ~(8 - 1));
				break;
			case '\r':
				x = 0;
				break;
			default:
				set_char(x++, y, (uint8_t)str[i]);
				break;
		}
		
		if (x >= 80) {
			x = 0;
			y++;
		}
	}
	update_csr(x, y);
}

void setattrib(const uint8_t fg, const uint8_t bg)
{
	attrib = (uint8_t)((bg << 4) + (fg & 0x0F));
}

void init_video(void)
{
	vmem = (uint16_t *)0xB8000;
	cls();
}
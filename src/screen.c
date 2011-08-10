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

unsigned short *vidmem;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void update_csr(void)
{
    unsigned char c = csr_y * 80 + csr_x;
    
    outb(0x3D4, 14);
    outb(0x3D5, c >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, c);
}

void clear_line(const int line)
{
    memsetw(vidmem + (line * 80), 0x20 + (attrib << 8), 80);
}

void cls(void)
{
    int i;
    for (i = 0; i < 25; i++)
        clear_line(i);
    
    csr_x = 0;
    csr_y = 0;
    update_csr();
}

void scroll(void)
{
    unsigned short temp;
    
    if(csr_y >= 25)
    {
        temp = csr_y - 25 + 1;
        memcpy(vidmem, vidmem + (temp * 80), ((25 - temp) * 80) * 2);
        clear_line(25 - temp);
        csr_y = 25 - 1;
    }
}

int putc(const char c)
{
    int r = 1;
    if ((c == 0x08) && (csr_x != 0))
    {
        csr_x--;
    }
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    else if(c == '\r')
    {
        csr_x = 0;
    }
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    else if(c >= ' ')
    {
        unsigned short *where = vidmem + (csr_y * 80 + csr_x);
        *where = c | (attrib << 8);
        csr_x++;
    }
    else
    {
        r = 0;
    }
    
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }
    
    scroll();
    update_csr();
    return r;
}

int puts(const char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++) 
        putc(s[i]);
    return i;
}

void settextmode(const char fg, const char bg)
{
    attrib = (bg << 4) + (fg & 0x0F);
}

void init_video(void)
{
    vidmem = (unsigned short *)0xB8000;
    cls();
}
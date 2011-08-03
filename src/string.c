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

#include <string.h>

void *memcpy(void *dest, void *src, size_t num)
{
    unsigned char *d = dest, *s = src;
    for (; num >= 0; num--) d[num] = s[num];
    return d;
}

void *memcpyw(void *dest, void *src, size_t num)
{
    unsigned short *d = dest, *s = src;
    for (; num >= 0; num--) d[num] = s[num];
    return d;
}

void *memset(void *ptr, int value, size_t num)
{
    unsigned char *dest = ptr;
    for (; num >= 0; num--) dest[num] = (unsigned char)value;
    return dest;
}

void *memsetw(void *ptr, int value, size_t num)
{
    unsigned short *dest = ptr;
    for (; num >= 0; num--) dest[num] = (unsigned short)value;
    return dest;
}

size_t strlen(const char *str) {
  size_t len;
  for (len = 0; str[len] != '\0'; len++);
  return len;
}
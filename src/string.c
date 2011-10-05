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
    for (; num >= 0; num--) *d++ = *s++;
    return dest;
}

void *memcpyw(void *dest, void *src, size_t num)
{
    unsigned short *d = dest, *s = src;
    for (; num >= 0; num--) *d++ = *s++;
    return dest;
}

void *memset(void *ptr, const int value, size_t num)
{
    unsigned char *dest = ptr;
    for (; num >= 0; num--) *dest++ = (unsigned char)value;
    return dest;
}

void *memsetw(void *ptr, const int value, size_t num)
{
    unsigned short *dest = ptr;
    for (; num >= 0; num--) *dest++ = (unsigned short)value;
    return dest;
}

size_t strlen(const char *str)
{
  size_t len;
  for (len = 0; str[len] != '\0'; len++);
  return len;
}

long pow(const long base, const long exp)
{
	long i, l = 1;
	for (i = exp; i > 0; i--)
		l *= base;
	return l;
}

size_t llen(const long l)
{
	size_t j = 0;
	while (l >= pow(10, (long)j))
		j++;
	return j >= 1 ? j : 1; //Must be >= 1
}

size_t ilen(const int i)
{
	return llen((long)i);
}

char *ltoa(const long l, char *dest, const size_t len)
{		
	long p, i = l;
	for (p = 1; p <= len; p++) {
		dest[len - p] = (char)((i % 10) + 48);
		i /= 10;
	}
	return dest;
}

char *itoa(const int i, char *d, const size_t len)
{		
	return ltoa((long)i, d, len);
}



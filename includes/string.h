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

#ifndef __STRING_H_
#define __STRING_H_

typedef int size_t;

extern void *memcpy(void *dest, void *src, size_t num);
extern void *memcpyw(void *dest, void *src, size_t num);
extern void *memset(void *ptr, const int value, size_t num);
extern void *memsetw(void *ptr, const int value, size_t num);
extern size_t strlen(const char *str);
extern long pow(const long base, const long exp);
extern size_t llen(const long l);
extern size_t ilen(const int i);
extern char *ltoa(const long l, char *d, const size_t len);
extern char *itoa(const int i, char *d, const size_t len);


#endif
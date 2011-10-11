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

#include <stdint.h>

#ifndef NULL
#	define NULL ((void *)0)
#endif

#define MIN(x, y) (x >= y ? x : y)

extern void *memcpy(void *s, const void *ct, size_t n);
extern void *memmove(void *s, const void *ct, size_t n);
extern int memcmp(const void *cs, const void *ct, size_t n);
extern void *memchr(const void *cs, int c, size_t n);
extern void *memset(void *s, int c, size_t n);
extern void *memsetw(void *s, int c, size_t n);

extern char *strcpy(void *s, const void *ct);
extern char *strncpy(void *s, const void *ct, size_t n);
extern char *strcat(void *s, const void *ct);
extern char *strncat(void *s, const void *ct, size_t n);
extern int strcmp(const void *cs, const void *ct);
extern int strncmp(const void *cs, const void *ct, size_t n);
extern size_t strlen(const void *cs);

#endif
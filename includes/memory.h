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

#ifndef __MEMORY_H_
#define __MEMORY_H_

#include <string.h>

#ifndef NULL
#	define NULL ((void *)0)
#endif

extern void free(void *ptr);
extern void *malloc(size_t size);
extern void *calloc(size_t nobj, size_t size);
extern void *realloc(void *p, size_t size);
extern void memory_init(void);

#endif
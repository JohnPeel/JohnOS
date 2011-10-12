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

#include <stdint.h>

#ifndef NULL
#	define NULL ((void *)0)
#endif

#define MEM_FREE 0x01
#define MEM_USED 0x02

#define MEM_TAIL 0x10
#define MEM_END 0x20

struct memory_header;
struct memory_header {
	uint32_t checksum; //HEADER_GOOD
	uint8_t status;
	uint32_t size;
	struct memory_header *prev;
	struct memory_header *next;
} __attribute__((packed));

#define HEADER_SIZE (sizeof(struct memory_header))
#define HEADER_GOOD (0x44474259UL)

extern void free(void *ptr);
extern void *malloc(uint32_t size);
extern void *calloc(uint32_t nobj, uint32_t size);
extern void *realloc(void *p, uint32_t size);
extern void memory_add(uint32_t base, uint32_t size);
extern void memory_walk(void);
extern void memory_init(void);

#endif
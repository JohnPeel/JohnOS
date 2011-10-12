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

#include <memory.h>
#include <console.h>
#include <math.h>
#include <string.h>

inline struct memory_header *get_header(void *ptr);
inline void *get_mem(struct memory_header *header);
inline struct memory_header *get_next_header(struct memory_header *ptr);
inline void clear_header(struct memory_header *header);
inline struct memory_header *create_header(void *ptr, uint32_t size);
inline int is_tail(struct memory_header *header);
inline int is_end(struct memory_header *header);
inline int is_free(struct memory_header *header);
inline int is_used(struct memory_header *header);
inline int is_header(struct memory_header *header);

inline struct memory_header *get_header(void *ptr)
{
	return (struct memory_header *)((uint32_t)ptr - HEADER_SIZE);
}

inline void *get_mem(struct memory_header *header)
{
	return (void *)((uint32_t)header + HEADER_SIZE);
}

inline struct memory_header *get_next_header(struct memory_header *ptr)
{
	return (struct memory_header *)((uint32_t)get_mem(ptr) + (uint32_t)ptr->size);
}

inline void clear_header(struct memory_header *header)
{
	memset(header, 0, HEADER_SIZE);
}

inline struct memory_header *create_header(void *ptr, uint32_t size)
{
	struct memory_header *header = (struct memory_header *)ptr;
	clear_header(header);
	header->checksum = HEADER_GOOD;
	header->status = MEM_FREE;
	header->size = size - HEADER_SIZE;
	return header;
}

inline int is_tail(struct memory_header *header)
{
	return ((header->status & MEM_TAIL) == MEM_TAIL);
}

inline int is_end(struct memory_header *header)
{
	return ((header->status & MEM_END) == MEM_END);
}

inline int is_header(struct memory_header *header)
{
	return (header->checksum == HEADER_GOOD);
}

inline int is_free(struct memory_header *header)
{
	return ((header->status & MEM_FREE) == MEM_FREE);
}

inline int is_used(struct memory_header *header)
{
	return ((header->status & MEM_USED) == MEM_USED);
}

struct memory_header *top = NULL;

void free(void *ptr)
{
	struct memory_header *header = get_header(ptr);
	if (!is_header(header)) {
		console_print("Tried to free unalloc'ed memory!");
		return; //TODO: Raise Exception!
	}

	header->status &= 0xF0;
	header->status |= MEM_FREE;

	if ((!is_tail(header)) && (!is_end(header))) {
		struct memory_header *next = header->next;
		while ((next != NULL) && is_free(next)) {
			header->size += (size_t)HEADER_SIZE + next->size;
			header->status = (uint8_t)(header->status | (next->status & 0xF0));
			struct memory_header *temp = next;
			next = next->next;
			clear_header(temp);

			if (is_end(header) || is_tail(header))
				break;
		}
		header->next = next;

		if (!is_end(header))
			header->next->prev = header;
	}

	if ((header->prev != NULL) && is_header(header->prev)) {
		struct memory_header *prev = header->prev;
		while ((prev != NULL) && is_free(prev)) {
			if (is_tail(prev))
				break;
			prev->size += (size_t)HEADER_SIZE + header->size;
			prev->status = (uint8_t)(prev->status | (header->status & 0xF0));
			prev->next = header->next;
			header->next->prev = prev;
			clear_header(header);
			header = prev;
			prev = prev->prev;
		}
	}

	return;
}

void *malloc(uint32_t size)
{
	struct memory_header *header = top;
	while ((header != NULL) && (is_used(header) || (header->size < size))) {
		if (is_end(header))
			return NULL;
		header = header->next;
	}

	if (header == NULL)
		return NULL;

	header->status &= 0xF0;
	header->status |= MEM_USED;

	if (header->size > (size + HEADER_SIZE)) {
		struct memory_header *new_header = create_header((void *)((uint32_t)get_mem(header) + size), header->size - size);
		new_header->next = header->next;
		header->next->prev = new_header;
		new_header->prev = header;
		header->next = new_header;

		header->size = size;
		if (is_tail(header)) {
			new_header->status |= MEM_TAIL;
			header->status &= 0x2F;
		}

		if (is_end(header)) {
			new_header->status |= MEM_END;
			header->status &= 0x1F;
		}
	}

	return get_mem(header);
}

void *calloc(uint32_t nobj, uint32_t size)
{
	void *temp = malloc(nobj * size);
	if (temp != NULL)
		memset(temp, 0, (size_t)(nobj * size));
	return temp;
}

void *realloc(void *p, uint32_t size) 
{
	void *new = malloc(size);
	if (new == NULL)
		return NULL;
	memcpy(new, p, (size_t)MIN(get_header(p)->size, size));
	free(p);
	return new;
}

void memory_add(uint32_t base, uint32_t size)
{
	if (base == 0) {
		base++; //FIXME: Hacky fix... mmap reports 0->0x9f800 is free, 0 == NULL
		size--;
	}

	struct memory_header *new_header = create_header((void *)base, size);
	new_header->status |= MEM_TAIL;
	if (top == NULL) {
		top = new_header;
		top->status |= MEM_END;
		return;
	}

	struct memory_header *header = top;
	while ((header != NULL) && ((uint32_t)header < base)) {
		if (is_end(header))
			break;
		header = header->next;
	}

	if (is_end(header)) {
		header->next = new_header;
		new_header->prev = header;
		new_header->status |= MEM_END;
		header->status &= 0x1F;
		return;
	}

	new_header->prev = header->prev;
	header->prev = new_header;
	new_header->next = header;
	new_header->prev->next = new_header;
}

void memory_walk(void)
{
	console_print("Memory Walk <----------------------------------->");
	console_print("Address: Status, Size, Previous, Next");
	struct memory_header *header = top;
	while (header != NULL) {
		char str[CONSOLE_LINE_LENGTH] = {0, };
		char num[NOTA_MAX] = {0, };
		strcpy(str, ntoa(num, (uint32_t)header, 16));
		strcat(str, ": ");
		strcat(str, ntoa(num, header->status, 16));
		strcat(str, ", ");
		strcat(str, ntoa(num, header->size, 16));
		strcat(str, ", ");
		strcat(str, ntoa(num, (uint32_t)header->prev, 16));
		strcat(str, ", ");
		strcat(str, ntoa(num, (uint32_t)header->next, 16));
		console_print(str);
		header = header->next;
	}
	console_print("<----------------------------------------------->");
}

void memory_init(void)
{
	console_print("Memory Manager Initiated.");
}
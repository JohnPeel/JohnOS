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

void free(void *ptr)
{
	//TODO: free();
	return;
}

void *malloc(size_t size)
{
	//TODO: malloc();
	return NULL;
}

void *calloc(size_t nobj, size_t size)
{
	void *temp = malloc(nobj * size);
	if (temp != NULL)
		memset(temp, 0, nobj * size);
	return temp;
}

void *realloc(void *p, size_t size) 
{
	void *new = malloc(size);
	if (new == NULL)
		return NULL;
	//FIXME: realloc, memcpy(new, p, memory_sizeof(p));
	free(p);
	return new;
}

void memory_init(void)
{
	//TODO: memory_init, Add free mem from multiboot_info?
	console_print("Memory Manager Initiated. (Unstarted)");
}
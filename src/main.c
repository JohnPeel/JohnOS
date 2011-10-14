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

#include <main.h>
#include <system.h>
#include <memory.h>
#include <screen.h>
#include <console.h>
#include <gdt.h>
#include <idt.h>
#include <isrs.h>
#include <irq.h>
#include <timer.h>
#include <string.h>
#include <keyboard.h>
#include <math.h>

const char *version = "v0.1a";

void main(const struct kernel_info *ki, const struct multiboot_info *mbi, uint32_t magic)
{
	init_video();
	console_setup();

	if (magic != MULTIBOOT_VALID) {
		console_print("Problem with magicboot info! Halting System.");
		for(;;);
	}

	if ((mbi->flags & MB_INFO_MEM_MAP) == MB_INFO_MEM_MAP) {
		struct multiboot_memory_map *mmap = (struct multiboot_memory_map *)mbi->mmap_addr;
		while((uint32_t)mmap < mbi->mmap_addr + mbi->mmap_length) {
			if (mmap->type == MB_ARD_MEMORY) {
				if (mmap->base_addr_high > 0)
					break;

				if (mmap->length_high > 0) {
					memory_add(mmap->base_addr_low, 0xFFFFFFFF - mmap->base_addr_low);
					break;
				}

				if ((ki->start > mmap->base_addr_low) && (ki->end < (mmap->base_addr_low + mmap->length_low))) {
					memory_add(mmap->base_addr_low, ki->start - mmap->base_addr_low);
					memory_add(ki->end, mmap->length_low - (ki->end - mmap->base_addr_low));
					mmap = (struct multiboot_memory_map *)((uint32_t)mmap + mmap->size + sizeof(uint32_t));
					continue;
				} else if (ki->start == mmap->base_addr_low) {
					mmap->base_addr_low += ki->end - ki->start;
				} else if (ki->end == (mmap->base_addr_low + mmap->length_low)) {
					mmap->length_low -= ki->end - ki->start;
				}

				memory_add(mmap->base_addr_low, mmap->length_low);
			}
			mmap = (struct multiboot_memory_map *)((uint32_t)mmap + mmap->size + sizeof(uint32_t));
		}
		memory_init();
	} else {
		//TODO: Add code to find free memory, without using mbi
		console_print("Required magicboot info missing! Halting System.");
		for (;;);
	}

	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
	keyboard_install();

	asm("sti");

	//TODO: Launch shell program? (Ring 0 or 3?)
	//0 for debugging would me nice
	//3 for a working userspace, multiple shells? like 1->7 on linux 

	for (;;);
}

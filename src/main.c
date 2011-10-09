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

const char *version = "v0.1a";

void main(const struct multiboot_info *mbi, uint32_t magic)
{
	init_video();
	console_setup();

	if (magic != MULTIBOOT_VALID)
	{
		console_print("Problem with magicboot info! Halting System.");
		for(;;);
	}

	memory_init();
	/*
	if ((mbi->flags & MB_INFO_MEM_MAP) == MB_INFO_MEM_MAP) {
		struct AddrRangeDesc *mmap = (struct AddrRangeDesc *)mbi->mmap_addr;
		while ((unsigned int)mmap < mbi->mmap_addr + mbi->mmap_length) {
			if ((mmap->Type & MB_ARD_MEMORY) == MB_ARD_MEMORY) {
				...
			}
			mmap = (struct AddrRangeDesc *)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
		}
	}
	*/

	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
	keyboard_install();

	asm("sti");

	//TODO: The Rest?

	for (;;);
}

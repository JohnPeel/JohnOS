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

#include <gdt.h>
#include <string.h>
#include <console.h>

gdt_entry gdt[5];
struct gdt_ptr gp;

void gdt_set_gate(uint32_t index, uint32_t base, uint32_t limit, uint16_t flag)
{
	gdt[index] = (limit & 0x000F0000);
	gdt[index] |= ((flag << 8) & 0x00F0FF00);
	gdt[index] |= ((base >> 16) & 0xFF0000FF);
	gdt[index] <<= 32;
	gdt[index] |= (base << 16);
	gdt[index] |= (limit & 0x0000FFFF);
}

void gdt_install(void)
{
	memset(gdt, 0, sizeof(gdt));

	gp.limit = (uint16_t)(sizeof(gdt) - 1);
	gp.base = (uint32_t)gdt;

	gdt_set_gate(0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, GDT_CODE_PL0);
	gdt_set_gate(2, 0, 0xFFFFFFFF, GDT_DATA_PL0);
	gdt_set_gate(3, 0, 0xFFFFFFFF, GDT_CODE_PL3);
	gdt_set_gate(4, 0, 0xFFFFFFFF, GDT_DATA_PL3);

	gdt_flush();

	console_print("Global Descriptor Table (GDT) Installed.");
}
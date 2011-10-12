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

#ifndef __GDT_H_
#define __GDT_H_

#include <stdint.h>

#define SEG_TYPE(x)	((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)	((x) << 0x07) // Present
#define SEG_SAVL(x)	((x) << 0x0C) // Available for system use
#define SEG_LONG(x)	((x) << 0x0D) // Long mode
#define SEG_SIZE(x)	((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)	((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)	(((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)
 
#define SEG_DATA_RD			0x00 // Read-Only
#define SEG_DATA_RDA		0x01 // Read-Only, accessed
#define SEG_DATA_RDWR		0x02 // Read/Write
#define SEG_DATA_RDWRA		0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD		0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA	0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD	0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA	0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX			0x08 // Execute-Only
#define SEG_CODE_EXA		0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD		0x0A // Execute/Read
#define SEG_CODE_EXRDA		0x0B // Execute/Read, accessed
#define SEG_CODE_EXC		0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA		0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC		0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA		0x0F // Execute/Read, conforming, accessed
 
#define GDT_CODE_PL0	(SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(0) | SEG_CODE_EXRD)
 
#define GDT_DATA_PL0	(SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(0) | SEG_DATA_RDWR)
 
#define GDT_CODE_PL3	(SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(3) | SEG_CODE_EXRD)
 
#define GDT_DATA_PL3	(SEG_TYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(3) | SEG_DATA_RDWR)

#define GDT_TSS			(SEG_TYPE(0) | SEG_PRES(1) | SEG_SAVL(0) | \
						SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | \
						SEG_PRIV(0) | SEG_CODE_EXA)

typedef uint64_t gdt_entry;
struct gdt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

extern void gdt_set_gate(uint32_t index, uint32_t base, uint32_t limit, uint16_t flag);
extern void gdt_flush(void);
extern void gdt_install(void);

#endif
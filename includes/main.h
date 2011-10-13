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

#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdint.h>
#include <mb_info.h>

struct kernel_info {
	const uint32_t start;
	const uint32_t code;
	const uint32_t rodata;
	const uint32_t data;
	const uint32_t bss;
	const uint32_t ebss;
	const uint32_t end;
};

extern const char *version;
extern void main(const struct kernel_info *ki, const struct multiboot_info *mbi, uint32_t magic);

#endif
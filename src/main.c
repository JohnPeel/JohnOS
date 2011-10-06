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
#include <screen.h>
#include <console.h>
#include <gdt.h>
#include <idt.h>
#include <isrs.h>
#include <irq.h>
#include <timer.h>
#include <string.h>
#include <keyboard.h>

const char *version = "0.1a";

void main(void *mbd, unsigned int magic)
{
	if (magic != 0x2BADB002)
	{
		//PROBLEM! Can't use mbd....
		for (;;); //hlt
	}
	
	init_video();
	console_setup();
	
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
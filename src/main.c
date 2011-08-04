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
#include <gdt.h>
#include <idt.h>
#include <isrs.h>
#include <irq.h>
#include <screen.h>

void main(void)
{
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    
    asm("sti");
    
    init_video();
    
    puts("Hello World!\n");
    
    for (;;);
}
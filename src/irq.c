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

#include <irq.h>
#include <system.h>
#include <idt.h>

#include <screen.h>
#include <string.h>

void *irq_routines[16] = {0, };

void irq_install_handler(int irq, void (*handler)(regs *r))
{
	irq_routines[irq] = (void *)handler;
}

void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = (void *)0;
}

void irq_remap(void)
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

void irq_handler(regs *r)
{
	if (r->int_no > 33) { //Don't show irq0 (timer) or irq1 (keyboard)
		puts("irq_handler(");
		puts("\n  gs="); puti(r->gs);
		puts(", fs="); puti(r->fs);
		puts(", es="); puti(r->es);
		puts(", ds="); puti(r->ds);
		puts(",\n  edi="); puti(r->edi);
		puts(", esi="); puti(r->esi);
		puts(", ebp="); puti(r->ebp);
		puts(", esp="); puti(r->esp);
		puts(",\n  ebx="); puti(r->ebx);
		puts(", edx="); puti(r->edx);
		puts(", ecx="); puti(r->ecx);
		puts(", eax="); puti(r->eax);
		puts(",\n  int_no="); puti(r->int_no);
		puts(", err_code="); puti(r->err_code);
		puts(",\n  eip="); puti(r->eip);
		puts(", cs="); puti(r->cs);
		puts(", eflags="); puti(r->eflags);
		puts(", useresp="); puti(r->useresp);
		puts(", ss="); puti(r->ss);
		puts("\n);\n");
	}
	
	void (*handler)(regs *r);

	handler = irq_routines[r->int_no - 32];
	if (handler)
	    handler(r);

	if (r->int_no >= 40)
	    outb(0xA0, 0x20);
	    
	outb(0x20, 0x20);
}

void irq_install(void)
{
	irq_remap();
	
	idt_set_gate(32, (unsigned long)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned long)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned long)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned long)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned long)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned long)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned long)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned long)irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned long)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned long)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned long)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned long)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned long)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned long)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned long)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned long)irq15, 0x08, 0x8E);
	
	puts("IRQ Installed!\n");
}


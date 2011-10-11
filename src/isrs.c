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

#include <isrs.h>
#include <idt.h>
#include <console.h>

#include <stdint.h>
#include <string.h>
#include <math.h>

const char *exceptions[] =
{
	"Division By Zero",
	"Debug",
	"Non-Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Reserved",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Floating-Point Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Security Exception",
	"Reserved"
};

void fault_handler(regs *r)
{
	if (r->int_no < 32) {
		console_print("");
		char s[78];
		memset(s, 0, 78);
		strcpy(s, exceptions[r->int_no]);
		strcat(s, " Exception. System Halted!");
		console_print(s);

		console_print_ni("  int_no  : ", r->int_no, 10);
		console_print_ni("  err_code: ", r->err_code, 10);

		console_print_ni("  gs      : ", r->gs, 16);
		console_print_ni("  fs      : ", r->fs, 16);
		console_print_ni("  es      : ", r->es, 16);
		console_print_ni("  ds      : ", r->ds, 16);

		console_print_ni("  edi     : ", r->edi, 16);
		console_print_ni("  esi     : ", r->esi, 16);
		console_print_ni("  ebp     : ", r->ebp, 16);
		console_print_ni("  esp     : ", r->esp, 16);
		console_print_ni("  ebx     : ", r->ebx, 16);
		console_print_ni("  edx     : ", r->edx, 16);
		console_print_ni("  ecx     : ", r->ecx, 16);
		console_print_ni("  eax     : ", r->eax, 16);

		console_print_ni("  eip     : ", r->eip, 16);
		console_print_ni("  cs      : ", r->cs, 16);
		console_print_ni("  eflags  : ", r->eflags, 16);
		console_print_ni("  useresp : ", r->useresp, 16);
		console_print_ni("  ss      : ", r->ss, 16);

		for (;;);
	}
}

void isrs_install(void)
{
	idt_set_gate(0, (unsigned long)isr0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned long)isr1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned long)isr2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned long)isr3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned long)isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned long)isr5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned long)isr6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned long)isr7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned long)isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned long)isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned long)isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned long)isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned long)isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned long)isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned long)isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned long)isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned long)isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned long)isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned long)isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned long)isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned long)isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned long)isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned long)isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned long)isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned long)isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned long)isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned long)isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned long)isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned long)isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned long)isr29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned long)isr30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned long)isr31, 0x08, 0x8E);

	console_print("Interrupt Service Routine (ISR) Handlers Installed.");
}

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

#include <timer.h>
#include <irq.h>
#include <system.h>
#include <console.h>

volatile uint32_t timer_ticks = 0;

void timer_wait(uint32_t ticks)
{
	uint32_t wait_for = timer_ticks + ticks;
	while (wait_for > timer_ticks);
}

void timer_handler(regs *r)
{
	timer_ticks++;
}

void timer_install(void)
{
	irq_install_handler(0, timer_handler);
	console_print("Timer (IRQ0) Handler Installed.");
}

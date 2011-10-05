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

#include <mouse.h>
#include <irq.h>
#include <system.h>

#include <screen.h>

void mouse_handler(regs *r)
{
	//TODO: Finish mouse!!
	puts("MOUSE!\n");
}

void mouse_install(void)
{
    irq_install_handler(12, mouse_handler);
	
	puts("Mouse Handler Installed! (Unfinished!)\n");
}
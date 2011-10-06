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

#include <console.h>
#include <main.h>
#include <system.h>
#include <screen.h>
#include <string.h>

char title[80] = {0, };

void console_setup(void) {
	cls();
	title[0] = '|';
	int i;
	for (i = 1; i <= 78; i++)
		title[i] = ' ';
	title[79] = '|';
	
	int ver_l = strlen(version);
	i = 33 - (ver_l / 2);
	memcpy((void *)&title[i], (void *)"JohnOS", 6);
	memcpy((void *)&title[i + 7], (void *)version, ver_l);
	
	if (title[i + 8] == '0')
		set_line(24, "YES");

	set_line(0, "/------------------------------------------------------------------------------\\");
	set_line(1, title);
	set_line(2, "|------------------------------------------------------------------------------|");
	for (i = 3; i < 24; i++)
		set_line(i, "|                                                                              |");
	//set_line(24, "\\------------------------------------------------------------------------------/");
}
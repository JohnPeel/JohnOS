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
#include <math.h>

int8_t title[LINE_LENGTH + 1] = {0, };
int8_t buffer[CONSOLE_BUFFER_LENGTH] = {0, };

void console_clear_line(const uint8_t line) {
	memset((void *)&buffer[line * CONSOLE_LINE_LENGTH], 0x20, CONSOLE_LINE_LENGTH);
}

void console_clear(void) {
	memset((void *)buffer, 0x20, CONSOLE_BUFFER_LENGTH);
}

void console_update(void) {
	set_line(0, (const int8_t *)"/------------------------------------------------------------------------------\\");
	set_line(1, title);
	set_line(2, (const int8_t *)"|------------------------------------------------------------------------------|");

	uint8_t i;
	for (i = 3; i < 24; i++) {
		int8_t line[LINE_LENGTH + 1] = {0, };
		line[0] = '|';
		memcpy((void *)&line[1], (void *)&buffer[(i - 3) * CONSOLE_LINE_LENGTH], CONSOLE_LINE_LENGTH);
		line[79] = '|';
		set_line(i, line);
	}

	set_line(24, (const int8_t *)"\\------------------------------------------------------------------------------/");
}

void console_set_line(const uint8_t line, const int8_t *s)
{
	console_clear_line(line);
	memcpy((void *)&buffer[line * CONSOLE_LINE_LENGTH], (void *)s, strlen(s) - 1);
}

void console_print(const char *s) /* Using char instead of int8_t to avoid warnings... */
{
	memmove((void *)buffer, (void *)&buffer[CONSOLE_LINE_LENGTH], CONSOLE_BUFFER_LENGTH - CONSOLE_LINE_LENGTH);
	console_set_line(20, (const int8_t *)s);
	console_update();
}

void console_print_ni(const char *str, uint32_t n, uint8_t base)
{
	uint32_t len = (uint32_t)(strlen(str) + 33);
	char result[len];
	memset(result, 0, (size_t)len);
	strcpy(result, str);
	char num[33];
	strcat(result, ntoa(num, n, base));
	console_print(result);
}

void console_setup(void)
{
	cls();
	console_clear();

	memset((void *)title, 0x20, 80);
	title[0] = '|';

	size_t ver_l = strlen(version);
	int32_t i = 34 - ((ver_l - 1) / 2);
	memcpy(&title[i], "JohnOS", 5);
	memcpy(&title[i + 7], version, ver_l - 1);

	title[79] = '|';

	console_update();
	console_print("Console Setup.");
}
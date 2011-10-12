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

#include <math.h>
#include <memory.h>
#include <string.h>

/*
 * char *ntoa(uint32_t n, uint32_t base)
 *   Convert n to a string.
 *  base: 2 - Bin, 8 - Oct, 10 - Dec, 16 - Hex
 */
char ntoa_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', 
					'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char *ntoa(char *dest, uint32_t src, uint8_t base)
{
	char s[NOTA_MAX] = {0, };
	if (dest == NULL)
		dest = malloc(NOTA_MAX);
	memset(dest, 0, NOTA_MAX);

	uint32_t p = 1;
	for (p = 0; src > 0; p++) {
		s[p] = ntoa_table[src % base];
		src /= base;
	}

	if (p == 0)
		s[0] = '0';
	uint32_t len = p > 0 ? p : 1;

	for (p = 0; p < len; p++)
		dest[p] = s[len - (p + 1)];

	switch (base) {
		case 8:
			memmove(&dest[1], dest, (size_t)len);
			dest[0] = '0';
			break;
		case 10:
			break;
		case 2:
		case 16:
			memmove(&dest[2], dest, (size_t)len);
			dest[0] = '0';
			dest[1] = 'x';
			break;
	}

	return dest;
}
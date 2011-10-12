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

#include <string.h>
#include <math.h>

/*
 * memcpy copies from ct[0] to ct[n-1] to dest
 * memmove will ether do ct[n-1] to ct[0] or
 *   use memcpy depending on orientation.
 */

void *memcpy(void *s, const void *ct, size_t n)
{
	uint8_t *dest = s;
	const uint8_t *src = ct;

	uint32_t p;
	for (p = 0; p < n; p++)
		dest[p] = src[p];

	return dest;
}

void *memmove(void *s, const void *ct, size_t n)
{
	uint8_t *dest = s;
	const uint8_t *src = ct;

	if ((uint32_t)src < (uint32_t)dest) {
		uint32_t p;
		for (p = 1; p <= n; p++)
			dest[n - p] = src[n - p];
	} else if ((uint32_t)src > (uint32_t)dest)
		return memcpy(s, ct, n);
	/* else dest == src, just return dest */

	return s;
}

int memcmp(const void *cs, const void *ct, size_t n)
{
	const uint8_t *s = cs, *t = ct;

	int tmp = 0;
	uint32_t p;
	for (p = 0; p < n; p++)
		tmp += (s[p] > t[p] ? 1 : (s[p] < t[p] ? -1 : 0));
	return tmp;
}

void *memchr(const void *cs, int c, size_t n)
{
	const uint8_t *src = cs;

	uint32_t p;
	for (p = 0; p < n; p++)
		if (src[p] == (uint8_t)c)
			return (void *)&src[p]; /* void *, suppresses warning */

	return NULL;
}

void *memset(void *s, int c, size_t n)
{
	uint8_t *dest = s;

	uint32_t p;
	for (p = 0; p < n; p++)
		dest[p] = (uint8_t)c;

	return s;
}

void *memsetw(void *s, int c, size_t n)
{
	uint16_t *dest = s;

	uint32_t p;
	for (p = 0; p < n; p++)
		dest[p] = (uint16_t)c;

	return s;
}

char *strcpy(void *s, const void *ct) {
	return (char *)memcpy(s, ct, strlen(ct));
}


char *strncpy(void *s, const void *ct, size_t n)
{
	char *dest = s;
	const char *src = ct;
	size_t len = strlen(src);

	uint32_t p;
	for (p = 0; p < n; p++)
		dest[p] = (char)(p <= len ? src[p] : 0);

	return dest;
}

char *strcat(void *s, const void *ct)
{
	return strncat(s, ct, strlen((char *)ct));
}

char *strncat(void *s, const void *ct, size_t n)
{
	char *dest = s;
	dest = &dest[strlen(dest)];
	const char *src = ct;
	size_t len = MIN(strlen(src), n);

	dest[len] = 0;

	uint32_t p;
	for (p = 0; p < len; p++)
		dest[p] = src[p];

	return s;
}

int strcmp(const void *cs, const void *ct)
{
	const char *s = cs, *t = ct;
	uint32_t n = MIN(strlen(s), strlen(t));

	int32_t tmp = 0;
	uint32_t p;
	for (p = 0; p < n; p++)
		tmp += (s[p] > t[p] ? 1 : (s[p] < t[p] ? -1 : 0));
	return tmp;
}

int strncmp(const void *cs, const void *ct, size_t n)
{
	const char *s = cs, *t = ct;
	size_t len = MIN(MIN(strlen(s), strlen(t)), n);

	int32_t tmp = 0;
	uint32_t p;
	for (p = 0; p < len; p++)
		tmp += (s[p] > t[p] ? 1 : (s[p] < t[p] ? -1 : 0));
	return tmp;
}

size_t strlen(const void *cs)
{
	const char *str = cs;

	size_t tmp;
	for (tmp = 0; str[tmp] != '\0'; tmp++);
	return tmp;
}

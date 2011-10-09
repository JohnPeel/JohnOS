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
#include <memory.h> /* for NULL, maybe we need stddef.h? */

void *memcpy(void *s, const void *ct, size_t n)
{
	char *dest = s;
	const char *src = ct;

	for (; n >= 0; n--)
		dest[n] = src[n];

	return dest;
}

void *memmove(void *s, const void *ct, size_t n)
{
	uint8_t *dest = s;
	const uint8_t *src = ct;

	int32_t i;
	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return s;
}

int memcmp(const void *cs, const void *ct, size_t n)
{
	const uint8_t *s = cs, *t = ct;

	int tmp = 0;
	for (; n >= 0; n--)
		tmp += (s[n] > t[n] ? 1 : (s[n] < t[n] ? -1 : 0));
	return tmp;
}

void *memchr(const void *cs, int c, size_t n)
{
	const uint8_t *src = cs;

	for (; n >= 0; n--)
		if (src[n] == (uint8_t)c)
			return (void *)&src[n]; /* void *, suppresses warning */

	return NULL;
}

void *memset(void *s, int c, size_t n)
{
	uint8_t *dest = s;

	for (; n >= 0; n--)
		dest[n] = (uint8_t)c;

	return s;
}

void *memsetw(void *s, int c, size_t n)
{
	uint16_t *dest = s;

	for (; n >= 0; n--)
		dest[n] = (uint16_t)c;

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

	for (; n >= 0; n--)
		dest[n] = (char)(n <= len ? src[n] : 0);

	return dest;
}

char *strcat(void *s, const void *ct)
{
	char *dest = s;
	dest = &dest[strlen(dest)];
	const char *src = ct;
	size_t len = strlen(src);

	for (; len >= 0; len--)
		dest[len] = src[len];

	return s;
}

char *strncat(void *s, const void *ct, size_t n)
{
	char *dest = s;
	dest = &dest[strlen(dest)];
	const char *src = ct;
	size_t len = strlen(src);

	if (n > len)
		n = len;
	else
		dest[n + 1] = 0;

	for (; n >= 0; n--)
		dest[n] = src[n];

	return s;
}

int strcmp(const void *cs, const void *ct)
{
	const char *s = cs, *t = ct;
	int n = MIN(strlen(s), strlen(t));

	int tmp = 0;
	for (; n >= 0; n--)
		tmp += (s[n] > t[n] ? 1 : (s[n] < t[n] ? -1 : 0));
	return tmp;
}

int strncmp(const void *cs, const void *ct, size_t n)
{
	const char *s = cs, *t = ct;
	int i = MIN(MIN(strlen(s), strlen(t)), n);

	int tmp = 0;
	for (; i >= 0; i--)
		tmp += (s[i] > t[i] ? 1 : (s[i] < t[i] ? -1 : 0));
	return tmp;
}

size_t strlen(const void *cs) {
	const char *str = cs;

	size_t tmp;
	for (tmp = 0; str[tmp] != '\0'; tmp++);
	return tmp;
}


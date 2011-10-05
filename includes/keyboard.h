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

#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include <idt.h>

#define MOD_NONE 0
#define MOD_ALT 1
#define MOD_CTRL 2
#define MOD_LSHIFT 4
#define MOD_RSHIFT 8

#define MOD_CAPSL 16
#define MOD_NUML 32
#define MOD_E0 64
#define MOD_ALL 127

#define LED_NONE 0
#define LED_SCROLL 1
#define LED_NUM_LOCK 2
#define LED_CAPS_LOCK 4
#define LED_ALL 7

extern unsigned char keyboard_mods;
extern unsigned char keyboard_leds;
extern void keyboard_updateleds(void);
extern void keyboard_toggleled(unsigned char led);
extern void keyboard_togglemod(unsigned char mod);
extern void keyboard_handler(regs *r);
extern void keyboard_install(void);

#endif
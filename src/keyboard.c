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

#include <keyboard.h>
#include <irq.h>
#include <system.h>

#include <screen.h>
#include <string.h>

unsigned char keyboard_mods = MOD_NONE;
unsigned char keyboard_leds = LED_NONE;

void keyboard_updateleds(void) {
	while ((inb(0x64) & 2) != 0);
	outb(0x60, 0xED);
	while ((inb(0x64) & 2) != 0);
	outb(0x60, keyboard_leds);
}

void keyboard_toggleled(unsigned char led) {
	if ((keyboard_leds & led) == led) {
		keyboard_leds &= LED_ALL - led;
	} else {
		keyboard_leds |= led;
	}
	
	keyboard_updateleds();
}

void keyboard_togglemod(unsigned char mod) {
	if ((keyboard_mods & mod) == mod) {
		keyboard_mods &= MOD_ALL - mod;
	} else {
		keyboard_mods |= mod;
	}
}

void keyboard_handler(regs *r)
{
    unsigned char scancode = inb(0x60);
	
	switch (scancode) {
		case 0x01: //Escape
			//outb(0x64, 0xFE); //CPU Reset
		case 129:
			break;
		
		case 0xba: //Caps Lock
			keyboard_togglemod(MOD_CAPSL);
			keyboard_toggleled(LED_CAPS_LOCK);
		case 0x3a: //p
			break;
		
		case 0xc5: //Num lock
			keyboard_togglemod(MOD_NUML);
			keyboard_toggleled(LED_NUM_LOCK);
		case 0x45: //p
			break;
		
		case 0xb8: //CTRL
			//MOD_E0 = Right
			keyboard_mods &= MOD_ALL - MOD_CTRL;
		case 29:
			break;
		
		case 0xaa://Left Shift
			keyboard_mods &= MOD_ALL - MOD_LSHIFT;
		case 42:
			break;
		
		case 0xb6://Right Shift
			keyboard_mods &= MOD_ALL - MOD_RSHIFT;
		case 54:
			break;
		
		case 0x9d: //ALT
			//MOD_E0 = Right
			keyboard_mods &= MOD_ALL - MOD_ALT;
		case 56:
			break;
		
		case 0xe0: //Special
			if ((keyboard_mods & MOD_E0) != MOD_E0)
				keyboard_togglemod(MOD_E0);
				puts("Special Pressed! E0\n");
		case 0xfa:	
			break;
		
		case 14: //Backspace
		case 142:
		case 15: //Tab
		case 143:
		case 28: //Enter
		case 156:
		case 57: //Space
		case 185:
			break;
		
		case 72: //Up
		case 200:
		case 75: //Left
		case 203:
		case 77: //Right
		case 205:
		case 80: //Down
		case 208:
			break;
		
		case 0x02: //1
		case 130:
		case 0x03: //2
		case 131:
		case 0x04: //3
		case 132:
		case 0x05: //4
		case 133:
		case 0x06: //5
		case 134:
		case 0x07: //6
		case 135:
		case 0x08: //7
		case 136:
		case 0x09: //8
		case 137:
		case 0x0a: //9
		case 138:
		case 0x0b: //0
		case 139:
			break;
		
		case 12: //-
		case 140:
		case 13: //=
		case 141:
		case 26: //[
		case 154:
		case 27: //]
		case 155:
		case 39: //;
		case 167:
		case 40: //'
		case 168:
		case 41: //`
		case 169:
		case 43: //\
		case 0xab:
		case 51: //,
		case 179:
		case 52: //.
		case 180:
		case 53: ///
		case 181:
		case 55: //*
		case 183:
			break;
		
		case 30: //a
		case 158:
		case 48: //b
		case 176:
		case 46: //c
		case 174:
		case 32: //d
		case 160:
		case 18: //e
		case 146:
		case 33: //f
		case 161:
		case 34: //g
		case 162:
		case 35: //h
		case 163:
		case 23: //i
		case 151:
		case 36: //j
		case 164:
		case 37: //k
		case 165:
		case 38: //l
		case 166:
		case 50: //m
		case 178:
		case 49: //n
		case 177:
		case 24: //o
		case 152:
		case 25: //p
		case 153:
		case 16: //q
		case 144:
		case 19: //r
		case 147:
		case 31: //s
		case 159:
		case 20: //t
		case 148:
		case 22: //u
		case 150:
		case 47: //v
		case 175:
		case 17: //w
		case 145:
		case 45: //x
		case 173:
		case 21: //y
		case 149:
		case 44: //z
		case 172:
			break;
		
		case 91: //Left Windows Key
		case 219:
		case 92: //Right Windows Key
		case 220:
		case 93: //??? key between win and ctrl
		case 221:
			break;
			
		case 59: //F1
		case 187:
		case 60: //F2
		case 188:
		case 61: //F3
		case 189:
		case 62: //F4
		case 190:
		case 63: //F5
		case 191:
		case 64: //F6
		case 192:
		case 65: //F7
		case 193:
		case 66: //F8
		case 194:
		case 67: //F9
		case 195:
		case 68: //F10
		case 196:
		case 87: //F11
		case 215:
		case 88: //F12
		case 216:
			break;
		
		default:
			puts("Unknown ");
			break;
	}
	
	puts("Scancode: ");
	puti(scancode);
	putc('\n');
	
	if (((keyboard_mods & MOD_E0) == MOD_E0) && (scancode != 0xe0))
		keyboard_togglemod(MOD_E0);
}

void keyboard_install(void)
{
    irq_install_handler(1, keyboard_handler);
	
	puts("Keyboard Handler Installed! (Unfinished!)\n");
}
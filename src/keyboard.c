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
		keyboard_leds &= (unsigned char)(LED_ALL - led);
	} else {
		keyboard_leds |= led;
	}
	
	keyboard_updateleds();
}

void keyboard_togglemod(unsigned char mod) {
	if ((keyboard_mods & mod) == mod) {
		keyboard_mods &= (unsigned char)(MOD_ALL - mod);
	} else {
		keyboard_mods |= mod;
	}
}

int keyboard_uppercase(void) {
	char i = 0;
	
	if ((keyboard_mods & MOD_CAPSL) == MOD_CAPSL)
		i++;
		
	if ((keyboard_mods & MOD_LSHIFT) == MOD_LSHIFT)
		i++;
		
	if ((keyboard_mods & MOD_RSHIFT) == MOD_RSHIFT)
		i++;
		
	return i > 0 ? 0 : 1;
}

void keyboard_handler(regs *r)
{
	/* unsigned char scancode = inb(0x60);
	
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
			break;
		case 42:
			keyboard_mods |= MOD_LSHIFT;
			break;
		
		case 0xb6://Right Shift
			keyboard_mods &= MOD_ALL - MOD_RSHIFT;
			break;
		case 54:
			keyboard_mods |= MOD_RSHIFT;
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
			putc(0x08);
		case 142:
			break;
			
		case 15: //Tab
			putc('\t');
		case 143:
			break;
			
		case 28: //Enter
			putc('\n');
		case 156:
			break;
			
		case 57: //Space
			putc(' ');
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
			putc('1');
		case 130:
			break;
		
		case 0x03: //2
			putc('2');
		case 131:
			break;
		
		case 0x04: //3
			putc('3');
		case 132:
			break;
		
		case 0x05: //4
			putc('4');
		case 133:
			break;
		
		case 0x06: //5
			putc('5');
		case 134:
			break;
		
		case 0x07: //6
			putc('6');
		case 135:
			break;
		
		case 0x08: //7
			putc('7');
		case 136:
			break;
		
		case 0x09: //8
			putc('8');
		case 137:
			break;
		
		case 0x0a: //9
			putc('9');
		case 138:
			break;
			
		case 0x0b: //0
			putc('0');
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
		case 43: //Backslash
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
			if (keyboard_uppercase() == 0)
				putc('A');
			else
				putc('a');
		case 158:
			break;
		case 48: //b
			if (keyboard_uppercase() == 0)
				putc('B');
			else
				putc('b');
		case 176:
			break;
		case 46: //c
			if (keyboard_uppercase() == 0)
				putc('C');
			else
				putc('c');
		case 174:
			break;
		case 32: //d
			if (keyboard_uppercase() == 0)
				putc('D');
			else
				putc('d');
		case 160:
			break;
		case 18: //e
			if (keyboard_uppercase() == 0)
				putc('E');
			else
				putc('e');
		case 146:
			break;
		case 33: //f
			if (keyboard_uppercase() == 0)
				putc('F');
			else
				putc('f');
		case 161:
			break;
		case 34: //g
			if (keyboard_uppercase() == 0)
				putc('G');
			else
				putc('g');
		case 162:
			break;
		case 35: //h
			if (keyboard_uppercase() == 0)
				putc('H');
			else
				putc('h');
		case 163:
			break;
		case 23: //i
			if (keyboard_uppercase() == 0)
				putc('I');
			else
				putc('i');
		case 151:
			break;
		case 36: //j
			if (keyboard_uppercase() == 0)
				putc('J');
			else
				putc('j');
		case 164:
			break;
		case 37: //k
			if (keyboard_uppercase() == 0)
				putc('K');
			else
				putc('k');
		case 165:
			break;
		case 38: //l
			if (keyboard_uppercase() == 0)
				putc('L');
			else
				putc('l');
		case 166:
			break;
		case 50: //m
			if (keyboard_uppercase() == 0)
				putc('M');
			else
				putc('m');
		case 178:
			break;
		case 49: //n
			if (keyboard_uppercase() == 0)
				putc('N');
			else
				putc('n');
		case 177:
			break;
		case 24: //o
			if (keyboard_uppercase() == 0)
				putc('O');
			else
				putc('o');
		case 152:
			break;
		case 25: //p
			if (keyboard_uppercase() == 0)
				putc('P');
			else
				putc('p');
		case 153:
			break;
		case 16: //q
			if (keyboard_uppercase() == 0)
				putc('Q');
			else
				putc('q');
		case 144:
			break;
		case 19: //r
			if (keyboard_uppercase() == 0)
				putc('R');
			else
				putc('r');
		case 147:
			break;
		case 31: //s
			if (keyboard_uppercase() == 0)
				putc('S');
			else
				putc('s');
		case 159:
			break;
		case 20: //t
			if (keyboard_uppercase() == 0)
				putc('T');
			else
				putc('t');
		case 148:
			break;
		case 22: //u
			if (keyboard_uppercase() == 0)
				putc('U');
			else
				putc('u');
		case 150:
			break;
		case 47: //v
			if (keyboard_uppercase() == 0)
				putc('V');
			else
				putc('v');
		case 175:
			break;
		case 17: //w
			if (keyboard_uppercase() == 0)
				putc('W');
			else
				putc('w');
		case 145:
			break;
		case 45: //x
			if (keyboard_uppercase() == 0)
				putc('X');
			else
				putc('x');
		case 173:
			break;
		case 21: //y
			if (keyboard_uppercase() == 0)
				putc('Y');
			else
				putc('y');
		case 149:
			break;
		case 44: //z
			if (keyboard_uppercase() == 0)
				putc('Z');
			else
				putc('z');
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
			break;
	}
	
	if (((keyboard_mods & MOD_E0) == MOD_E0) && (scancode != 0xe0))
		keyboard_togglemod(MOD_E0); */
}

void keyboard_install(void)
{
	irq_install_handler(1, keyboard_handler);
	
	keyboard_updateleds();
}
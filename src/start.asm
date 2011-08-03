;   This file is part of JohnOS.
;
;   JohnOS is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.
;
;   JohnOS is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with JohnOS.  If not, see <http://www.gnu.org/licenses/>.

[BITS 32]
global start
extern main

ALIGN 4
mboot:
    MULTIBOOT_PAGE_ALIGN equ 1<<0
    MULTIBOOT_MEMORY_INFO equ 1<<1
    MULTIBOOT_AOUT_KLUDGE equ 1<<16
    MULTIBOOT_HEADER_MAGIC equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end

    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    dd mboot
    dd code
    dd bss
    dd end
    dd start
    
start:
    mov esp, _sys_stack
    call main
    cli
    
hang:
    hlt
    jmp hang
    
SECTION .bss
    resb 8192
_sys_stack:

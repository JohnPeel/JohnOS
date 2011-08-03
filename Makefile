#   This file is part of JohnOS.
#
#   JohnOS is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   JohnOS is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with JohnOS.  If not, see <http://www.gnu.org/licenses/>.

.PHONY: all clean dist todolist test

NASM=nasm
CC=i586-elf-gcc
LD=i586-elf-ld

AUXFILES := Makefile README COPYING
PROJDIRS := src includes
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")
OBJFILES := $(patsubst src/%.c,build/%.o,$(SRCFILES))
DEPFILES := $(patsubst src/%.c,build/%.d,$(SRCFILES))
SRCFILES := src/start.asm $(SRCFILES)
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS := -g -std=c99 -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -Iincludes -MMD -MP -c $(WARNINGS)


all: kernel.bin
	
kernel.bin: build/start.o $(OBJFILES)
	@$(LD) -T src/link.ld -o kernel.bin build/start.o $(OBJFILES)
	
%/.ph: 
	@mkdir -p $(@D)
	@touch $@
	
build/start.o: build/.ph
	@$(NASM) -f elf -o build/start.o src/start.asm
	
build/%.o: src/%.c build/.ph
	@$(CC) $(CFLAGS) $< -o $@

clean:
	-@$(RM) -r $(wildcard $(OBJFILES) build/start.o $(DEPFILES) build/ kernel.bin kernel.tar.gz )
	
dist:
	@tar czf kernel.tar.gz $(ALLFILES)
	
todolist:
	-@for file in $(SRCFILES); do fgrep -H -e TODO -e FIXME $$file; done; true
	-@for file in $(HDRFILES); do fgrep -H -e TODO -e FIXME $$file; done; true
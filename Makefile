#	This file is part of JohnOS.
#
#	JohnOS is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	JohnOS is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with JohnOS.  If not, see <http://www.gnu.org/licenses/>.

.PHONY: all clean dist todolist fixmelist createbuild

NASM=nasm
CC=i586-elf-gcc
LD=i586-elf-ld

AUXFILES := Makefile README COPYING
PROJDIRS := src includes
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")
SRCDIRS := $(shell find $(PROJDIRS) -type d)
DESTDIRS := $(patsubst src/%,build/%,$(SRCDIRS))
OBJFILES := $(patsubst src/%.c,build/%.o,$(SRCFILES))
DEPFILES := $(patsubst src/%.c,build/%.d,$(SRCFILES))
SRCFILES := src/start.s src/link.ld $(SRCFILES)
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

WARNINGS := -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS := -g -std=c99 -O2 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin \
          -I./includes -I./includes/fs -ffreestanding -nostartfiles -nodefaultlibs -MMD -MP -c $(WARNINGS)
LFLAGS := 

ifndef DEBUG
	CFLAGS := $(CFLAGS) -DNDEBUG
	LFLAGS := $(LFLAGS) --strip-all
endif

all: kernel.bin
	

kernel.bin: createbuild build/start.o src/link.ld $(OBJFILES)
	@$(LD) $(LFLAGS) -T src/link.ld $(OBJFILES)

-include $(DEPFILES)

build/start.o: src/start.s
	@$(NASM) -o build/start.o -f elf -Ox -Xgnu src/start.s

build/%.o: src/%.c
	@$(CC) $(CFLAGS) $< -o $@

clean:
	-@$(RM) -r $(wildcard build/ kernel.bin JohnOS.tar.gz)

createbuild:
	-@for dir in $(DESTDIRS); do mkdir -p $$dir; done; true

dist:
	@tar czf JohnOS.tar.gz $(ALLFILES)

fixmelist:
	-@for file in $(SRCFILES); do fgrep -Hn -e FIXME $$file; done; true
	-@for file in $(HDRFILES); do fgrep -Hn -e FIXME $$file; done; true

todolist:
	-@for file in $(SRCFILES); do fgrep -Hn -e NOTE -e TODO $$file; done; true
	-@for file in $(HDRFILES); do fgrep -Hn -e NOTE -e TODO $$file; done; true

src/start.asm:
	

src/link.ld:
	
OUTPUT_FORMAT("elf32-i386")
ENTRY(loader)
STARTUP(build\start.o)
OUTPUT(kernel.bin)

SECTIONS {
	. = 0x00100000;

	kernel_start = .;

	.text ALIGN(4096) : {
		kernel_code = .;
		*(.text)
	}

	.rodata ALIGN(4096) : {
		kernel_rodata = .;
		*(.rodata)
	}

	.data ALIGN(4096) : {
		kernel_data = .;
		*(.data)
	}

	.bss ALIGN(4096) : {
		kernel_bss = .;
		*(COMMON)
		*(.bss)
		. = ALIGN(4096);
		kernel_ebss = .;
	}

	kernel_end = .;

	/DISCARD/ :
	{
		*(.comment)
	}
}
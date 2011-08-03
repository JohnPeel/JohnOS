OUTPUT_FORMAT("binary")
ENTRY (start)
SECTIONS {
    . = 0x00100000;

    .text : {
        code = .;
        *(.text)
        *(.rodata)
    }

    .data ALIGN (0x1000) : {
        data = .;
        *(.data)
    }

    .bss : {
        bss = .;
        *(COMMON)
        *(.bss)
    }
    end = .;
}
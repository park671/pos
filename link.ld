ENTRY(_start)
SECTIONS
{
    . = 0x40080000;
    .startup . : {*/_start.o(.text)}
    . = ALIGN(8);
    .text :{*(.text)}
    . = ALIGN(8);
    .data :{*(.data)}
    . = ALIGN(8);
    .rodata :{*(.rodata)}
    . = ALIGN(8);
    bss_start = .;
    .bss :{*(.bss)}
    . = ALIGN(8);
    bss_end = .;
    . = . + 0x4000;
    . = ALIGN(16);
    stack_top = .;
}

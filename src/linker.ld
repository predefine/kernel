
OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS
{
	. = 2M;
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	} : text
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	} : rodata
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	} : data
	.bss BLOCK(4K) : ALIGN(4K)
	{

		*(.bss)
		*(COMMON)
	}  : bss
}

PHDRS {
    text PT_LOAD FLAGS(5);
    rodata PT_LOAD FLAGS(4);
    data PT_LOAD FLAGS(6);
    bss PT_LOAD FLAGS(6);
}

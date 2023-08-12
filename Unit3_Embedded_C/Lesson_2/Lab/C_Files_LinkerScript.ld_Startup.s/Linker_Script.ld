ENTRY(reset)

MEMORY
{
	mem (rwx) : o = 0x00000000 , l = 64M
}

SECTIONS
{
	. = 0x10000;
	.reset . :
	{
		Startup.o(.text)
	}> mem
	.text :
	{
		*(.text)
	}> mem
	.data :
	{
		*(.data)
	}> mem
	.bss :
	{
		*(.bss) *(COMMON)
	}> mem
	. = . + 0x1000;
	Stack_Top = . ;
}
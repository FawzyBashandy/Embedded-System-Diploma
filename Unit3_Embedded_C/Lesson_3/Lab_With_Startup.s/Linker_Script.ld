/*Prepared by Fawzy Mohamed*/
MEMORY
{
	Flash(RX)  : o = 0x08000000 , l = 128K
	Sram(RWX)  : o = 0x20000000 , l = 20K 
}

SECTIONS
{
	.text : 
	{
		*(._Vectors)
		*(.text*)
	} > Flash
	.data :
	{
		*(.data)
		. = ALIGN(4);
	} > Sram AT> Flash
	.bss :
	{
		*(.bss)
		. = ALIGN(4);
	} >Sram
	. = . + 0x1000;
	Stack_Top = .;
}
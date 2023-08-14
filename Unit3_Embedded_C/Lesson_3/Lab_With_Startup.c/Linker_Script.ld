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
		*(.text)
		_E_Text = . ;
	} > Flash
	.data :
	{
		_S_Data = .;
		*(.data)
		. = ALIGN(4);
		_E_Data = .;
	} > Sram AT> Flash
	.bss :
	{
		_S_Bss = .;
		*(.bss)
		. = ALIGN(4);	
		_E_Bss = .;
		. = . + 0x1000 ;
		Stack_Top = . ;
	} > Sram
}
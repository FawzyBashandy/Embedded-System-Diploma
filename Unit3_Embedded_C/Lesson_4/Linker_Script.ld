/*Prepared by Fawzy Mohamed*/
MEMORY
{
	Flash(RX)  : o = 0x00000000 , l = 512M
	Sram(RWX)  : o = 0x20000000 , l = 512M 
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
		_E_Bss = .;
	} > Sram
}


MEMORY
{
	Flash(rx) : ORIGIN = 0x08000000 , LENGTH = 128K
	Sram(rwx) : ORIGIN = 0x20000000 , LENGTH = 20K
}

SECTIONS
{
	.vectors :
	{
		*(_Vectors)
	}>Flash

	.text :
	{
		*(.text)
	}>Flash

	.rodata :
	{
		*(.rodata)
		_E_RODATA = . ;
	}>Flash

	.data :
	{
		_S_DATA = .;
		*(.data)
		_E_DATA = .;
	}>Sram AT> Flash
	
	.bss :
	{
		_S_BSS = .;
		*(.bss) *(COMMON)
		_E_BSS = .;
	}>Sram

	Stack_Top = . + 0x1000;
}
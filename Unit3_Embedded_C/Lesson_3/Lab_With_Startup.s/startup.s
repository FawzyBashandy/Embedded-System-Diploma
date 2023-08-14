// Prepared by Fawzy Mohamed 
.section ._Vectors

.word Stack_Top
.word _Reset_Handler
.word _Default_Handler //NMI
.word _Default_Handler //Bus_Fault_Handler
.word _Default_Handler //.._Handler
.word _Default_Handler //.._Handler
.word _Default_Handler //.._Handler
.word _Default_Handler //.._Handler

.section .text
_Reset_Handler:
	bl main
	b .
.thumb_func
_Default_Handler:
	b _Reset_Handler
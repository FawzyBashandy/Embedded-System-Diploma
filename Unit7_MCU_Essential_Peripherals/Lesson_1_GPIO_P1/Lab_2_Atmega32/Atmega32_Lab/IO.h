/*
 * IO.h
 *
 * Created: 23/02/2024 02:52:41 م
 *  Author: Fawzy Bashandy
 */ 


#ifndef IO_H_
#define IO_H_

#define IO_BASE 0x20
#define SFIOR       *((volatile unsigned char *)(IO_BASE + 0x30))

/************************************************************************/
/*	                     PORTA Registers                                */
/************************************************************************/
#define PORTA       *((volatile unsigned char *)(IO_BASE + 0x1B))
#define DDRA        *((volatile unsigned char *)(IO_BASE + 0x1A))
#define PINA        *((volatile unsigned char *)(IO_BASE + 0x19))

#define PORTC		*((volatile unsigned char *)(IO_BASE + 0x15))
#define DDRC        *((volatile unsigned char *)(IO_BASE + 0x14))
#define PINC		*((volatile unsigned char *)(IO_BASE + 0x13))

#define PORTD       *((volatile unsigned char *)(IO_BASE + 0x12))
#define DDRD        *((volatile unsigned char *)(IO_BASE + 0x11))
#define PIND        *((volatile unsigned char *)(IO_BASE + 0x10))



#endif /* IO_H_ */
/*
 * Bit_Math.h
 *
 * Created: 23/02/2024 02:42:50 م
 *  Author: Fawzy Bashandy
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define setBit(reg , bitNum)			(reg |= (1 << bitNum))
#define setBits(reg , bitNum , val)	(reg |= (val << bitNum))
#define clearBit(reg , bitNum)			(reg &= ~(1 << bitNum))
#define toggleBit(reg , bitNum)			(reg ^= (1 << bitNum))
#define readBit(reg , bitNum)			((reg >> bitNum)&1)


#endif /* BIT_MATH_H_ */
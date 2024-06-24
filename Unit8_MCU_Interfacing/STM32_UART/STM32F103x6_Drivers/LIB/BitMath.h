/*
 * BitMath.h
 *
 *  Created on: ٢٨‏/٠٢‏/٢٠٢٤
 *      Author: Fawzy Bashandy
 */

#ifndef BITMATH_H_
#define BITMATH_H_


#define SET_BIT(reg, bitNum)            (reg |= (1 << bitNum))
#define SET_BITS(reg, bitNum, value)    (reg |= (value << bitNum))
#define CLEAR_BIT(reg, bitNum)          (reg &= ~(1 << bitNum))
#define CLEAR_BITS(reg, bitNum, value)  (reg &= ~(value << bitNum))
#define TOGGLE_BIT(reg, bitNum)         (reg ^= (1 << bitNum))
#define READ_BIT(reg, bitNum)           ((reg & (1 << bitNum)) >> bitNum)

#endif /* BIT_MATH_H_ */


//*Platform types for STMicroelectronics ST30 realtive to ANSI C types
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#define CPU_TYPE        CPU_TYPE_32
#define CPU_BIT_ORDER   MSB_FIRST
#define CPU_BYTE_ORDER  HIGH_BYTE_FIRST

typedef unsigned char                 boolean;
typedef signed char                   sint8;
typedef signed short                  sint16;
typedef signed long                   sint32;
typedef signed long long              sint64;


typedef unsigned char                 uint8;
typedef unsigned short                uint16;
typedef unsigned long                 uint32;
typedef unsigned long long            uint64;


typedef volatile signed char          vsint8;
typedef volatile signed short         vsint16;
typedef volatile signed long          vsint32;
typedef volatile signed long long     vsint64;


typedef volatile unsigned char        vuint8;
typedef volatile unsigned short       vuint16;
typedef volatile unsigned long        vuint32;
typedef volatile unsigned long long   vuint64;


typedef float                         float32;
typedef double                        float64;
#endif
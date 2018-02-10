#pragma once

typedef _Bool bool;
#define true 1
#define false 0

typedef signed char i8;
typedef unsigned char u8;
typedef signed short i16;
typedef unsigned short u16;
typedef signed int i32;
typedef unsigned int u32;
typedef signed long long i64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#define var __auto_type
#define let __auto_type const

#define care __attribute__( ( warn_unused_result ) )
#define unused __attribute__( ( unused ) )
#define unreachable __builtin_unreachable()

#define export __attribute__( ( visibility( "default" ) ) )
#ifdef DEBUG
#define assume( x ) assert( x )
#else
#define assume( x ) __builtin_assume( x )
#endif

#ifndef _TDEF_H_
#define _TDEF_H_

#include <inttypes.h>

/* typedef bool as an enum */
/**
 * @brief bool is an enum boolean with 2 possible values, FALSE = 0, TRUE = 1
 */
typedef enum { true, false } bool;

/* typedef signed integers */

/**
 * @brief 8-Bit sized signed integer, typically a char
 */
typedef int8_t int8;

/**
 * @brief 16-Bit sized signed integer, typically a short
 */
typedef int16_t int16;

/**
 * @brief 32-Bit sized signed integer, typically an int
 */
typedef int32_t int32;

/**
 * @brief 64-bit sized signed integer, typically a long
 */
typedef int64_t int64;


/* typedef unsigned integers */

/**
 * @brief 8-Bit sized unsigend integer, typically an unsigned char
 */
typedef uint8_t byte, uint8;

/**
 * @brief 16-Bit sized unsigned integer, typically an unsigned short
 */
typedef uint16_t uint16;

/**
 * @brief 32-Bit sized unsigned integer, typically an unsigned int
 */
typedef uint32_t uint32;

/**
 * @brief 64-Bit sized unsigned integer, typically an unsigned long
 */
typedef uint64_t uint64;

/* typedef string literals */

/**
 * @brief Const string literal as char pointer
 */
typedef const char * cstring;

/**
 * @brief Non-const string literal as char pointer
 */
typedef char * string;

/**
 * @brief array of Non-const string literals.
 */
typedef char * string_array[];

#endif
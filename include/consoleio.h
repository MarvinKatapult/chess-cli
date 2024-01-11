#ifndef _CONSOLEIO_H_
#define _CONSOLEIO_H_

#include "tdef.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * @brief Clears the console buffer.
 */
void c_clear( void );

/**
 * @brief Writes the C string pointed by format to the standart output (stdout).
 * 
 * @param format C string that contains the text to be written to stdout.
 * @param ... Additional arguments to format the string. Any more arguments than specifiers get ignored.
 */
void c_print( cstring format, ... );

/**
 * @brief Writes the C string pointed by format to the error output (stderr).
 * 
 * @param format C string that contains the text to be written to stderr.
 * @param ... Additional arguments to format the string. Anymore arguments than specifiers get ignored.
 */
void c_print_err( cstring format, ... );

/**
 * @brief Writes the C string pointed by format to the stream.
 * 
 * @param stream Pointer to a FILE object that identifies an output stream.
 * @param format C string that contains the text to be written to the stream.
 * @param ... Additional arguments to format the string. Any more arguments than specifiers get ignored.
 */
void c_fprint( FILE * stream, cstring format, ... );

#endif // _CONSOLEIO_H_

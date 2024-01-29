#ifndef _CONSOLEIO_H_
#define _CONSOLEIO_H_

#include "tdef.h"

#include <stdio.h>
#include <stdarg.h>
/**
 * @brief Default max size of the string input
 */
#define IN_STRING_SIZE 80

/**
 * @brief Sets the cursor position to (y|x) where x=column, y=row
 * 
 * @param x Target column for the cursor
 * @param y Target row for the cursor
 */
void c_set_cursor( uint32 x, uint32 y );

/**
 * @brief Sets the cursor position to (y|x) where x=column, y=row
 * 
 * @param x Target column for the cursor
 * @param y Target row for the cursor
 */
void c_set_cursor( uint32 x, uint32 y );

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
 * @brief Writes the C string pointed by format to the error output (stderr) as a error (red)
 * 
 * @param format C string that contains the text to be written to stderr.
 * @param ... Additional arguments to format the string. Anymore arguments than specifiers get ignored.
 */
void c_print_err( cstring format, ... );

/**
 * @brief Writes the C string pointed by format to the error output (stderr) as a warning (yellow).
 * 
 * @param format C string that contains the text to be written to stderr.
 * @param ... Additional arguments to format the string. Anymore arguments than specifiers get ignored.
 */
void c_print_w( cstring format, ... );

/**
 * @brief Writes the C string pointed by format to the stream.
 * 
 * @param stream Pointer to a FILE object that identifies an output stream.
 * @param format C string that contains the text to be written to the stream.
 * @param ... Additional arguments to format the string. Any more arguments than specifiers get ignored.
 */
void c_fprint( FILE * stream, cstring format, ... );

/**
 * @brief Reads data from stdin and stores them according to the parameter format into the locations pointed 
 * 
 * @param format  C string that contains a sequence of characters that control how characters extracted from the stream are treated.
 * @param ... Additional arguments to store the imput
 * @return * int On Success, the function returns the number of items of the argument list successfully filled.
 */
int32 c_scan( cstring format, ... );

/**
 * @brief Reads data from stdin and returns the input as a const string with max size of IN_STRING_SIZE
 * 
 * @return cstring C string read from stdin. Needs to be freed manually
 */
string c_scan_string( void );

/**
 * @brief Reads data from stdin and returns the input as a const string with max size of intput_size
 * 
 * @param input_size Max size of the string input
 * @return cstring C string read from stdin. Needs to be freed manually
 */
string c_scan_string_size( uint32 input_size );
#endif // _CONSOLEIO_H_

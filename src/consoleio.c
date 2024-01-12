#include "consoleio.h"

#define ANSI_CONTROL_CLEAR "\033[2J"
#define ANSI_CONTROL_CPOS "\033[%d;%dH"

/**
 * @brief Sets the cursor position to (y|x) where x=column, y=row
 * 
 * @param x Target column for the cursor
 * @param y Target row for the cursor
 */
void c_set_cursor( uint32 p_x, uint32 p_y ) {
    c_print( ANSI_CONTROL_CPOS, p_y, p_x );
}

/**
 * @brief Clears the console buffer.
 */
void c_clear( void ) {
    c_print( ANSI_CONTROL_CLEAR );
    c_set_cursor( 0, 0 );
}

/**
 * @brief Writes the C string pointed by format to the standart output (stdout).
 * 
 * @param format C string that contains the text to be written to stdout.
 * @param ... Additional arguments to format the string. Any more arguments than specifiers get ignored.
 */
void c_print( cstring p_format, ... ) {
    va_list args;
    va_start(args, p_format);
    vfprintf( stdout, p_format, args);
    va_end(args);
}

/**
 * @brief Writes the C string pointed by format to the error output (stderr).
 * 
 * @param format C string that contains the text to be written to stderr.
 * @param ... Additional arguments to format the string. Anymore arguments than specifiers get ignored.
 */
void c_print_err( cstring p_format, ... ) {
    va_list args;
    va_start(args, p_format);
    vfprintf( stdout, p_format, args);
    va_end(args);
}

/**
 * @brief Writes the C string pointed by format to the stream.
 * 
 * @param stream Pointer to a FILE object that identifies an output stream.
 * @param format C string that contains the text to be written to the stream.
 * @param ... Additional arguments to format the string. Any more arguments than specifiers get ignored.
 */
void c_fprint( FILE * p_file, cstring p_format, ... ) {
    va_list args;
    va_start(args, p_format);
    vfprintf( p_file, p_format, args);
    va_end(args);
}

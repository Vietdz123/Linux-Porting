#include "gpio.h"


///////////////////////////////////////////////////////////////////////////////
// Function Definations
///////////////////////////////////////////////////////////////////////////////

/// Export GPIO pin 
uint32_t GPIOUnexport( uint32_t pin_ )
{
        char buffer[BUFFER_MAX];
        ssize_t bytes_written;
        uint32_t fd;
        fd = open( "/sys/class/gpio/export", O_WRONLY );
        if ( -1 == fd )
        {
                fprintf( stderr, "Failed to open export for writing!\n" );
                return( -1 );
        }

        bytes_written = snprintf( buffer, BUFFER_MAX, "%d", pin_ );
        write( fd, buffer, bytes_written );
        close( fd );
        return( 0 );
}

uint32_t GPIOExport( uint32_t pin_ )
{
        char buffer[BUFFER_MAX];
        ssize_t bytes_written;
        uint32_t fd;
        fd = open( "/sys/class/gpio/export", O_WRONLY );
        if ( -1 == fd )
        {
                fprintf( stderr, "Failed to open export for writing!\n" );
                return( -1 );
        }

        bytes_written = snprintf( buffer, BUFFER_MAX, "%d", pin_ );
        write( fd, buffer, bytes_written );
        close( fd );
        return( 0 );
}

/// Set GPIO direction
uint32_t GPIODirection( uint32_t pin_, uint32_t dir_ )
{
        static const char s_directions_str[]  = "in\0out";

        char path[DIRECTION_MAX];
        uint32_t fd;
        snprintf( path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin_ );
        fd = open( path, O_WRONLY );
        if ( -1 == fd )
        {
                fprintf( stderr, "Failed to open gpio direction for writing!\n" );
                return( -1 );
        }

        if ( -1 == write( fd, &s_directions_str[IN == dir_ ? 0 : 3], IN == dir_ ? 2 : 3 ) )
        {
                fprintf( stderr, "Failed to set direction!\n" );
                return( -1 );
        }

        close( fd );
        return( 0 );
}

/// Write value on GPIO pin
uint32_t GPIOWrite( uint32_t pin_, uint32_t value_ )
{
        static const char s_values_str[] = "01";

        char path[VALUE_MAX];
        uint32_t fd;
        snprintf( path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin_ );
        fd = open( path, O_WRONLY );
        if ( -1 == fd )
        {
                fprintf( stderr, "Failed to open gpio value for writing!\n" );
                return( -1 );
        }

        if ( 1 != write( fd, &s_values_str[LOW == value_ ? 0 : 1], 1 ) )
        {
                fprintf( stderr, "Failed to write value!\n" );
                return( -1 );
        }

        close( fd );
        return( 0 );
}
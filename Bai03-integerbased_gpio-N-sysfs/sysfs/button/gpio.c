#include "gpio.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

uint32_t GPIOUnexport( uint32_t pin_ )
{
        char buffer[BUFFER_MAX];
        ssize_t bytes_written;
        uint32_t fd;
        fd = open( "/sys/class/gpio/unexport", O_WRONLY );
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
        int count = 0;
        char gpio[100] = {0};
        FILE *file_connected_pipe;
        char buffer_pipe[100] = {0};
        char buffer[BUFFER_MAX] = {0};
        ssize_t bytes_written;
        uint32_t fd;

	char buffer1[10] = "export";

	file_connected_pipe = popen("ls /sys/class/gpio/", "r");
	sprintf(gpio, "gpio%d", pin_);
        //printf("GPIO: %s\n", gpio);
	if (file_connected_pipe == NULL) {
		printf("failed to open file pipe\n");
		return 0;
	}	

	//sprintf(gpio, "gpio%d", 31);
	char* check = buffer1;
	while (check != NULL) {
		memset(buffer_pipe, 0, sizeof(buffer_pipe));
		check = fgets(buffer_pipe, 1024, file_connected_pipe);
		if (count == 0) {
			printf("Data recieve from command through pipe is:\n%s", buffer_pipe);
			count++;
		} else {
			buffer_pipe[strlen(buffer_pipe) - 1] = 0;
			printf("Hello: %s\n", buffer_pipe);

			if (strcmp(gpio, buffer_pipe) == 0) {
				printf("GPIO %d exist\n", pin_);
                                return -1;
                                //GPIOUnexport(pin_);
			}
		}
	}

        wait(NULL);
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
uint32_t GPIOButton( uint32_t pinout_, uint32_t pinin__ )
{
        static const char s_values_str[] = "01";

        char path_input[VALUE_MAX] = {0};
        char path_output[VALUE_MAX] = {0};
        uint32_t fd_out, fd_in;
        char value_input[2] = {0};
        char value_output[2] = {0};
        char character_O[] = "0";

        sprintf( path_input, "/sys/class/gpio/gpio%d/value", pinin__);
        sprintf( path_output, "/sys/class/gpio/gpio%d/value", pinout_);
        fd_in = open( path_input, O_RDWR );
        fd_out = open( path_output, O_RDWR);
        if (-1 == fd_in || -1 == fd_out )
        {
                fprintf( stderr, "Failed to open gpio value for writing!\n" );
                return( -1 );
        }

        read(fd_in, value_input, 1);
        read(fd_out, value_output, 1);
        printf("character 0 = %s and value_input = %s, value_output = %s\n", character_O ,value_input ,value_output);
        if (strcmp(value_input, character_O) == 0) {
                if (value_output[0] == 48) {
                        if ( 1 != write( fd_out, &s_values_str[1], 1 ) ) {
                                fprintf( stderr, "Failed to write value HIGH!\n" );
                                return( -1 );
                        } else {
                                printf("Stated led On\n");
                        }
                } else if (value_output[0] == 49) {
                        if ( 1 != write( fd_out, &s_values_str[0], 1 ) ) {
                                fprintf( stderr, "Failed to write value HIGH!\n" );
                                return( -1 );
                        } else {
                                printf("stated led off\n");  
                        }                  
                }
        } else {
                printf("Hello ae wibu\n");
        }

        close( fd_in );
        close( fd_out );
        return( 0 );
}
#include "serial.h"

// Constants
int uart0_fd;

// Internal functions
void ctrl_c (int signal) {
    serial_close();
    exit(1);
}

// External functions
int serial_init (void) {
    // Close process safely
    signal(SIGINT, ctrl_c);

    // Open serial port
    uart0_fd = serialOpen(TTY, 9600);

    // Return -1 if serialOpen fails
    if(uart0_fd == -1)
        return -1;

    // Clear serial buffer
    serialFlush(uart0_fd);

    // ???
    if(serialDataAvail(uart0_fd))
        return -1;

    // Return success
    return 0;
}
void serial_close (void) {
    serialClose(uart0_fd);
}
void serial_write (char *data, int size) {
    for(int i = 0; i < size; i++)
        serialPutchar(uart0_fd, *(data + i));
}
void serial_read () {
    return serialGetchar(uart0_fd);
}	

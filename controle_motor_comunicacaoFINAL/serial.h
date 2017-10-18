#ifndef SERIAL_H
#define SERIAL_H

// Libraries
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>

// Definitions
#define TTY "/dev/ttyAMA0"

// Prototypes
int serial_init(void);
void serial_close(void);
void serial_write(char *data, int size);

#endif // SERIAL_H

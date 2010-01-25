/*Interface for the monitor*/

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"
#define VIDEO 0xb8000

/*Write a single character to screen*/
void monitor_put(char c);

/*Clears the screen*/
void monitor_clear();

/*Write a null-terminated ASCII string to the screen*/
void monitor_write(char *c);

/*Write a decimal*/
void monitor_write_dec(u32int n);

/* Write a hex values */
void monitor_write_hex(u32int n);
#endif //MONITOR_H

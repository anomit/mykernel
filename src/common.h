/*some common typedefs*/

#ifndef COMMON_H
#define COMMON_H

/*typedefs to standardize datatypes */

typedef unsigned int u32int;
typedef 	 int s32int;
typedef unsigned short u16int;
typedef 	 short s16int;
typedef unsigned char u8int;
typedef 	 char s8int;
#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

void *memset(void* s, int c, u32int size);

#endif //COMMON_H

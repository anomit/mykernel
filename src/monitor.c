#include "monitor.h"

u8int cursor_x = 0;
u8int cursor_y = 0;

u16int *video_memory = (u16int *)VIDEO;

/*Blinking cursor(?)*/
static void move_cursor()
{
	u16int cursor_location = cursor_y*80 + cursor_x;

	/*command to VGA board: setting the high cursor byte*/
	outb(0x3D4, 14);

	/*Send the high cursor byte*/
	outb(0x3D5, cursor_location>>8);

	/*setting the low cursor byte*/
	outb(0x3D4, 15);

	/*Send the low cursor byte*/
	outb(0x3D5, cursor_location);
}

/*Scrolls by a single line*/
static void scroll()
{
	/*Space character*/
	u8int attribute_byte = (0 /*black*/ << 4) | (10 /*not white*/ & 0x0F);
	u16int blank = 0x20 | (attribute_byte << 8);

	/*Screen area is 80x25*/
	if (cursor_y >= 25)
	{
		/*Move the chunk of text that makes up the screen back in the buffer by a line*/
		int i;
		for (i = 0; i<24*80; i++)
			video_memory[i] = video_memory[i+80];

		/*Write 80 spaces to the last line*/
		for (i=24*80; i<25*80; i++)
			video_memory[i] = blank;

		cursor_y = 24;
	}
}

void monitor_put(char c)
{
	u8int back_color = 0; //black
	u8int fore_color = 10; //not white

	u8int attribute_byte = (back_color << 4) || (fore_color &0x0F);
	u16int attribute = attribute_byte << 8;

	u16int *location;

	/*Backspace*/
	if (c == 0x08 && cursor_x)
		cursor_x--;
	/*Tab*/
	else if (c == 0x09)
		cursor_x = (cursor_x + 8) & ~(8-1); //divisible by 8
	/*Carriage return*/
	else if (c == '\r')
		cursor_x = 0;
	/*Newline*/
	else if (c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	/*any other character*/
	else if (c >= ' ')
	{
		location = video_memory + (cursor_y*80 + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	/*check if end of screen reached*/
	if (cursor_x >= 80)
	{
		cursor_x = 0;
		cursor_y++;
	}

	scroll();
	move_cursor();
}

/*clear the screen*/
void monitor_clear()
{
	u8int attrib_byte = (0 << 4) | (15  & 0x0F);
	u16int blank = 0x20 | (attrib_byte << 8);

	int i;
	for (i=0; i < 80*25; i++)
		video_memory[i] = blank;

	/*Move cursor back to start*/
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

/*Write the null-terminated string to screen*/
void monitor_write(char *c)
{
	int i=0;
	while(c[i])
		monitor_put(c[i++]);
}

void monitor_write_dec(u32int n)
{
if (n == 0)
    {
        monitor_put('0');
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    monitor_write(c2);
}

void monitor_write_hex(u32int n)
{
    s32int tmp;

    monitor_write("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            monitor_put (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            monitor_put( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        monitor_put (tmp-0xA+'a');
    }
    else
    {
        monitor_put (tmp+'0');
    }

}

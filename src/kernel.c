#include "monitor.h"
#include "descriptor_tables.h"
#include "paging.h"

int main( struct multiboot *mboot_ptr )
{    
    monitor_clear();
    //monitor_write("Hello world!");

    init_descriptor_tables();
    //init_paging();
    return 0xDEADB33F;
}

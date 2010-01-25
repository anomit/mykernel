SOURCES=loader.o kernel.o monitor.o common.o descriptor_tables.o isr.o \
		interrupt.o gdt.o paging.o kernel_mem.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tlinker.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel.bin

link:
	ld $(LDFLAGS) -o kernel.bin $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

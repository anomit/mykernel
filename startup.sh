cd src
make all && cd .. && ./createiso.sh && qemu -boot d -cdrom bootable.iso 

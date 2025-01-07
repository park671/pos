rm -f *.o *.elf *.bin
aarch64-none-elf-gcc -I -include -c uart.c -o uart.o
aarch64-none-elf-gcc -I -include -c main.c -o main.o
aarch64-none-elf-as -c start.s -o start.o
aarch64-none-elf-ld -Tlink.ld main.o uart.o start.o -o hello.elf
aarch64-none-elf-objcopy -O binary hello.elf hello.bin
qemu-system-aarch64 -M virt -cpu cortex-a710 -monitor none -kernel hello.bin

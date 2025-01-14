rm -f *.o *.elf *.bin
aarch64-none-elf-gcc -falign-functions=16 -I -include -g -fno-stack-protector -O0 -c uart.c -o uart.o
aarch64-none-elf-gcc -falign-functions=8 -I -include -g -fno-stack-protector -O0 -c main.c -o main.o
aarch64-none-elf-as -g -c start.s -o start.o
aarch64-none-elf-ld -g -O0 -Tlink.ld main.o uart.o start.o -o hello.elf
aarch64-none-elf-objcopy -O binary hello.elf hello.bin
qemu-system-aarch64 -M virt -m 512M -cpu cortex-a710,sve=on -nographic -serial stdio -monitor none -kernel hello.bin
#qemu-system-aarch64 -s -S -M virt -m 512M -cpu cortex-a710,sve=on -nographic -serial stdio -monitor none -kernel hello.bin

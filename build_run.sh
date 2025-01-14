#!/bin/bash
echo "init env..."

function clean() {
  echo "clean..."
  rm -rf ./build
}

function build() {
  echo "compiling..."

  c_flag="-falign-functions=8 -I -include -g -fno-stack-protector -O0"

  start_src="start"
  boot_src="boot"
  uart_src="uart"

  build_dir="build"
  mkdir -p ${build_dir}

  mkdir -p "${build_dir}/${start_src}"
  aarch64-none-elf-as -g -c ${start_src}/start.s -o "${build_dir}/${start_src}/_start.o"

  for src_file in ${boot_src}/*.c; do
    dirpath=$(dirname "$src_file")
    mkdir -p "${build_dir}/${dirpath}"
    aarch64-none-elf-gcc ${c_flag} -c "$src_file" -o "${build_dir}/${src_file%.c}.o"
  done

  for src_file in ${uart_src}/*.c; do
    dirpath=$(dirname "$src_file")
    mkdir -p "${build_dir}/${dirpath}"
    aarch64-none-elf-gcc ${c_flag} -c "$src_file" -o "${build_dir}/${src_file%.c}.o"
  done

  echo "linking..."
  aarch64-none-elf-ld -g -O0 -Tlink.ld $(find ${build_dir} -type f -name "*.o") -o "${build_dir}/punix.elf"

  echo "copy binary..."
  aarch64-none-elf-objcopy -O binary "${build_dir}/punix.elf" "${build_dir}/punix.img"
}

function start() {
  echo "start qemu..."
  qemu_args="-M virt -m 512M -cpu cortex-a710,sve=on -nographic -serial stdio -monitor none"
  if [ $1 == "run" ]; then
    qemu-system-aarch64 ${qemu_args} -kernel "${build_dir}/punix.img"
  else
    qemu-system-aarch64 -s -S ${qemu_args} -kernel "${build_dir}/punix.img"
  fi
}

if [ "$1" == "run" ]; then
    clean
    build
    start run
elif [ "$1" == "debug" ]; then
    clean
    build
    start debug
elif [ "$1" == "build" ]; then
    clean
    build
elif [ "$1" == "clean" ]; then
    clean
else
    echo "Usage: demo.sh {run|debug|clean|build}"
fi

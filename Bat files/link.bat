@ echo off
set /p compiler_path=<Paths/compiler.txt
set /p cygwin_path=<Paths/cygwin.txt
set current_path=%cd:\=/%
%cygwin_path%/bin/bash --login -c "%compiler_path%/i686-elf-gcc -T '%current_path%/../linker.ld' -o '%current_path%/../Build/moe.bin' -ffreestanding -O2 -nostdlib '%current_path%/../Build/boot.o' '%current_path%/../Build/kernel.o' -lgcc"
pause
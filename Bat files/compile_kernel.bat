@ echo off
set /p compiler_path=<Paths/compiler.txt
set /p cygwin_path=<Paths/cygwin.txt
set current_path=%cd:\=/%
%cygwin_path%/bin/bash --login -c "%compiler_path%/i686-elf-g++ -c '%current_path%/../kernel.c++' -o '%current_path%/../Build/kernel.o' '-ffreestanding' -O2 -Wall -Wextra -fno-exceptions -fno-rtti"
pause
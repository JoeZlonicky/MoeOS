@ echo off
set /p compiler_path=<Paths/compiler.txt
set /p cygwin_path=<Paths/cygwin.txt
set current_path=%cd:\=/%
%cygwin_path%/bin/bash --login -c "%compiler_path%/i686-elf-as '%current_path%/../boot.s' -o '%current_path%/../Build/boot.o'"
pause
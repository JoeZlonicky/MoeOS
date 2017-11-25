@ echo off
set /p qemu_path=<Paths/qemu.txt
"%qemu_path%/qemu-system-i386" -kernel ../Build/moe.bin
pause

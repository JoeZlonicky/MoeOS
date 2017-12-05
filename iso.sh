set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/moe.kernel isodir/boot/moe.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "moe" {
  multiboot /boot/moe.kernel
}
EOF
grub-mkrescue -o moe.iso isodir

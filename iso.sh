#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/fobos isodir/boot/fobos
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "fobos" {
	multiboot /boot/fobos
}
EOF
grub-mkrescue -o fobos.iso isodir

#!/bin/sh
set -e
# . ./iso.sh
. ./build.sh

# qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom fobos.iso
qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel ./sysroot/boot/fobos

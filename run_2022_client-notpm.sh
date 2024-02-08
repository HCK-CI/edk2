../qemu-build/bin/qemu-system-x86_64 --machine q35 --smp 2 --enable-kvm -m 4096 -vga std server2022.qcow2 -bios Build/OvmfX64/RELEASE_GCC5/FV/OVMF.fd -usbdevice tablet -name "Server 2022 HLK Studio Client"  -device e1000,netdev=net0,mac=DE:AD:BE:EF:01:1A -netdev tap,id=net0  -serial file:serial.log


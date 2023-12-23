# x86_kernel
First attempt at making a kernel. Developed for the x86 platform and only supports basic features :

- Global Descriptor Table
- Hardware and Software Interrupts
- Bitmap-based Physical Memory Manager
 
## Dependencies and building the kernel
These tools are required to build and run the kernel.
- Docker
- QEMU

I used Docker to easily create an x86 Ubuntu image with all required tools. Since the project runs on x86, it would be time-consuming to build `binutils` and `gcc` for example. Be sure to be at the root of the project before running these commands.

```bash
[m1nds@arch x86_kernel]$ sudo docker build -t os-toolchain .
```

```bash
[m1nds@arch x86_kernel]$ sudo docker run -ti -v ${PWD}:/root/os-toolchain os-toolchain /bin/bash
```


```bash
root@ef9c6936ff70:~/os-toolchain# make
```

## How to run the kernel ?

You can use QEMU to run the project using this command :

```bash
qemu-system-i386 -cdrom lkd.iso
```

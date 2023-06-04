FROM i386/debian

RUN apt-get upgrade -y
RUN apt-get update && apt-get install -y build-essential binutils gcc nasm grub-pc-bin grub-common xorriso mtools

WORKDIR /root/os-toolchain
VOLUME /root/os-toolchain


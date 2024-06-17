# BakaOS
A simply x86 operating system written in C++.
includes its own [modular kernel](Kernel) with SMP and networking, [window server/compositor](System/LemonWM) and [userspace applications](Applications) as well as [a collection of software ports](Ports).

## [Building OS](Documentation/Build/Building-Lemon-OS.md)

**Before running**
See [System Requirements](#system-requirements)

## Features
- Modular Kernel
- Symmetric Multiprocessing (SMP)
- UNIX/BSD Sockets
- Network Stack (UDP, TCP, DHCP)
- A small HTTP client/downloader called [steal](Applications/Steal)
- Window Manager/Server [LemonWM](System/LemonWM)
- [Terminal Emulator](Applications/Terminal)
- Writable Ext2 Filesystem
- IDE, AHCI and NVMe Driver
- Dynamic Linking
- [mlibc](https://github.com/managarm/mlibc) C Library Port
- [LLVM/Clang Port](https://github.com/LemonOSProject/llvm-project)
- [DOOM Port](https://github.com/LemonOSProject/LemonDOOM)
- [Audio Player (using ffmpeg)](Applications/AudioPlayer)

## System requirements
- 256 MB RAM (512 is more optimal)
- x86_64 Processor supporting [x86_64-v2 instructions](https://en.wikipedia.org/wiki/X86-64#Microarchitecture_levels) including SSE4.2
    - For QEMU/KVM use `-cpu host` or at least `-cpu Nehalem` see [this page](https://qemu-project.gitlab.io/qemu/system/target-i386.html)
- 2 or more CPU cores recommended
- I/O APIC
- ATA, NVMe or AHCI disk (AHCI *strongly* recommended)

For QEMU run with: \
```qemu-system-x86_64 Lemon.img --enable-kvm -cpu host -M q35 -smp 2 -m 1G -netdev user,id=net0 -device e1000,netdev=net0 -device ac97``` \
**KVM is strongly recommended**

## Repo Structure

| Directory          | Description                              |
| ------------------ | ---------------------------------------- |
| Applications/      | Userspace Applications/应用程序          |
| Base/              | Config, etc. Files copied to disk/       |
| Documentation/     | OS Documentation/OS描述(尚不完整)        |
| Extra/             | (Currently) vector icons                 |
| InterfaceCompiler/ | Compiler for interface definition files  |
| Kernel/            | OS Kernel/操作系统内核                   |
| LibGUI/            | LibGUI (Windowing and widgets)           |
| LibLemon/          | LibLemon (Lemon API)                     |
| Toolchain/         | Toolchain build scripts and patches      |
| Ports/             | Build scripts and patches for ports      |
| Resources/         | Images, fonts, etc.                      |
| Scripts/           | Build Scripts                            |
| Services/          | Interface definition files               |
| System/            | Core system programs and services        |

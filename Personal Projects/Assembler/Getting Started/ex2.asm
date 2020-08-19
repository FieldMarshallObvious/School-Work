global start

section .data
    msg db "Hello, world!", 0x0a
    len equ $ - msg ; determine length of string by subtracting end of message from start

section .text
start:
    mov rax, 0x2000004 ; sys_write system call
    mov rdi, 1 ; stdout file descriptor
    mov rsi, msg ; bytes to write
    mov rdx, len ; number of bytes to write

    syscall ; Invoke the kernel

    mov rax, 0x2000001 ; system exit call
    mov rdi, 0 ; exit status is 0

    syscall ; Invoke the kernel
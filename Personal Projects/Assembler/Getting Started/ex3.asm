global start

section .text

start:
    mov rax, 0x2000001 ; exit status system call
    mov rdi, 1 ; sys_exit system call set to 1


    jmp skip ; jump to "skip label"

    mov rax, 0x2000001 ; exit status system call
    mov rdi, 0 ; sys_exit system call set to 0
    syscall ; Invoke the kernel


skip:
    syscall ; Invoke the kernel


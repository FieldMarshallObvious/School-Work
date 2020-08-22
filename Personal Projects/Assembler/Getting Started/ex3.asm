global start

section .text

start:
    mov rax, 0x2000001 ; exit status is 4
    mov rdi, 1 ; sys_exit system call


    jmp skip ; jump to "skip label"

    mov rax, 0x2000001 ; exit status is 1
    mov rdi, 0 ; sys_exit system call
    syscall ; Invoke the kernel


skip:
    syscall ; Invoke the kernel


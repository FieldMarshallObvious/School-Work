global _factorial

section .text

_factorial:
    cmp rdi, 1 ; n < = 1
    jnbe L1 ; if not go follow recursive call
    mov rax, 1 ; else return 1
    ret

L1:
    push rdi ; save n on stack (also aligsn %rsp register)
    dec rdi ; n-1
    call _factorial ; factorial(n-1), resulte goes in %rax
    pop rdi ; restore n
    imul rax, rdi ; n * factorial(n-1), stored in %rax
    ret
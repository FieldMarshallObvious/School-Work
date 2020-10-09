global _start
extern _puts
default rel

section .text

_start:
    push rdi ; save registers that puts uses
    push rsi ; align stack before call
    sub rsp, 8 ; align stack before call

    lea rdi, [rsi] ; the argument string to display
    call _puts ; prints string

    add rsp, 8 ; restore %rso ti pre-aligned value
    pop rsi ; resotre registers puts used
    pop rdi

    add rsi, 8 ; point to next argument
    dec rdi ; count down
    jnz _start ; if not done counting keep going
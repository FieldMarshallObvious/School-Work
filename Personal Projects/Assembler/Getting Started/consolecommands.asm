global _start
extern puts
section .text

_start: 
    push rdi ; save registers that puts uses
    push rsi ; align stack before call
    sub rsp, 8 ; align stack before call

    mov rdi, [rsi] ; the argument string to display
    push rdi;
    call puts ; prints string
    pop rdi;

    add rsp, 8 ; restore %rso ti pre-aligned value
    pop rsi ; resotre registers puts used
    pop rdi

    add rsi, 8 ; point to next argument
    dec rdi ; count down
    jnz _start ; if not done counting keep going

    ret
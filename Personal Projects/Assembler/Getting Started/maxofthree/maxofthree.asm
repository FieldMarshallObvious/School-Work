; 64 bit assembly function that returns the maximum value of 
; the three integer arguements. The function has a signature:
; int64_t maxofthree(int64_t x, int64_t y, int64_t z)

global _maxofthree
section .text

_maxofthree:
    mov rax, rdi ; result initially holds x (rax)
    cmp rax, rsi ; is x less than y?
    cmovl rax, rsi ; if the previous conditional returns true assign to y (rsi)
    cmp rax, rdx ; is greater value less than z?
    cmovl rax, rdx ; if the the greater value is lass than z set result to z
    
    ret ; transfer control to the return address 
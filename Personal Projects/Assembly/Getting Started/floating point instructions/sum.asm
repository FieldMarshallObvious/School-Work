global _sum
section .text

_sum:
    xorpd xmm0, xmm0
    cmp rsi, 0
    je _done
_next:
    addsd xmm0, [rdi]
    add rdi, 8
    dec rsi
    jnz _next 

_done:
    ret
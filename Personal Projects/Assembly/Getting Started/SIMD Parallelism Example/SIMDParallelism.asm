global _Parallelism
section .text

_Parallelism:
    movdqa xmm0, [rdi] ; all four values of x
    movdqa xmm1, [rsi] ; all four values of y
    addps xmm0, xmm1 ; add all numbers with one command
    ret
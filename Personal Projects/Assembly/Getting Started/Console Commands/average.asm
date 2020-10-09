global _main
extern _atoi
extern _printf
default rel 

section  .text
_main: 
    push rbx ; align stack 

    dec rdi ; don't count the programp name
    jz nothingToAverage
    mov [count], rdi ; save number of real arguments

accumulate:
    push rdi ; save registers across call to atoi
    push rsi 
    mov rdi, [rsi+rdi*8] ; argv[rdi]

    call _atoi ; call atoi not that rax has int value of arg
    pop rsi ; restore registers after atoi call
    pop rdi 

    add [sum], rax ; accumulate sum as iterate
    dec rdi ; count down each increment
    jnz accumulate ; check for more arguments

average:
    cvtsi2sd xmm0, [sum]
    cvtsi2sd xmm1, [count]
    divsd xmm0, xmm1 ; set xmm0 to sum/count

    lea rdi, [format] ;1st arg of printf
    mov rax, 1 ; printf is varargs, there is 1 non-int argument
    call _printf ; print(format, sum/count)
    jmp done

nothingToAverage:
    lea rdi, [error]
    xor rax, rax 
    call _printf

done:
    pop rbx ; undoes beginning push
    ret

section  .data
count: dq 0
sum: dq 0
format: db  "%g", 10, 0
error: db "There are no command line arguments to average", 10, 0
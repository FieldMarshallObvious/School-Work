global start 

section .text

; ----------------------------------------------------------------------------------------
; This is an OSX console program that writes a little triangle of asterisks to standard
; output. Runs on macOS only.
; ----------------------------------------------------------------------------------------

global start

section .text

start:
    mov rdx, output ; rdx holds address of next byte to write
    mov r8, 1 ; initial line length
    mov r9, 0 ; number of stars written on line so far 

line:
    mov byte [rdx], '*' ; write single star
    inc rdx ; advance pointer to next cell to write
    inc r9 ; counter number so far on line
    cmp r9, r8 ; determine if we have reached the max number of chars for the line
    jne line ; if there is still more space keep writing

lineDone:
    mov byte [rdx], 10 ; write a new line 
    inc rdx ; move pointer to the next char location
    inc r8 ; increase the length of the next line
    mov r9, 0 ; reset count of star for new line
    cmp r8, maxlines ; check if the max number of lines has been passed 
    jng line ; if the max number of lines has not been passed go back to line

done:
    mov rax, 0x02000004 ; system call to write
    mov rdi, 1 ; set exit status to 1 
    mov rsi, output ; set register to address of string for output
    mov rdx, dataSize ; number of bytes
    syscall
    mov rax, 0x02000001 ; system call for exit
    xor rdi, rdi ; exit code 0
    syscall

section .bss
maxlines equ 8 ; set max number of lines
dataSize equ 44 ; set max number of bytes
output: resb dataSize ; function to get address of string
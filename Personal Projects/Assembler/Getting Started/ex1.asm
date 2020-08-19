global start
start:
    mov ebx, 123 ; ebx = 123
    mov edx, 3 ; edx = 3
    mov eax, ebx ; eax = ebx
    add ebx, ecx ; ebx += ecx
    sub ebx, edx ; ebx -= edx
    mul ebx ; eax *= ebx
    div edx ; eax /= edx  
    int 0x80
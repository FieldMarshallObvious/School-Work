#prog 001.asm
		.data
name:		.space 11	
howdy: 		.asciiz  "Howdy!"
eyaPrompt: 	.asciiz  "Enter age: "
yaiLabel: 	.asciiz  "Your age is  "
eynPrompt: 	.asciiz  "Enter your name:  " 
yniLab:	 	.asciiz  "Your name is  " 
####

		.text
		.globl main
		
main: 
		li $v0, 4
		la $a0, howdy
		syscall
		
		#enter age
		li $v0, 11
		li $a0, '\n'
		syscall
		
		li $v0, 4
		la $a0, eyaPrompt
		syscall	
		
		li $v0, 5
		syscall
		move $t0, $v0
		
		li $v0, 11
		li $a0, '\n'
		syscall
		
		li $v0, 4
		la $a0, yaiLabel
		syscall	
		
		li $v0, 1
		move $a0, $t0
		syscall	
		
		#enter name
		
		li $v0, 11
		li $a0, '\n'
		syscall
		
		li $v0, 4
		la $a0, eynPrompt
		syscall			
		
		li $v0, 8
		la $a0, name
		li $a1, 11
		syscall
		
		li $v0, 4
		la $a0, yniLab
		syscall
		
		li $v0, 4
		la $a0, name
		syscall
		
		
		li $v0, 10
		syscall
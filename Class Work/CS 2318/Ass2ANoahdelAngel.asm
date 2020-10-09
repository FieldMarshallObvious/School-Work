#Ass2ANoahdelAngel.asm
		.data
intInputPrmpt: 	.asciiz "Enter a integer: "
intInputLabel:	.asciiz "The integer is "
strngInputPrmpt:.asciiz "Enter a string: "
strngInputLabel:.asciiz "The string is "  
strngInput: 	.space 50


		.text
		.globl main
		
main:
	#Print int prompt
	li $v0, 4
	la $a0, intInputPrmpt
	syscall
	
	#Get input
	li $v0, 5
	syscall
	move $t0, $v0
	
	#Print a new line
	li $v0, 11
	li $a0, '\n'
	syscall
		
	#Print int message
	li $v0, 4
	la $a0, intInputLabel
	syscall
	
	#Print int input
	li $v0, 1
	move $a0, $t0
	syscall
	
		
	#Print a new line
	li $v0, 11
	li $a0, '\n'
	syscall
	
	
	#Print string prompt
	li $v0, 4
	la $a0, strngInputPrmpt
	syscall
	
	#Get input
	li $v0, 8
	la $a0, strngInput
	li $a1, 50
	syscall

	
	#Print a new line
	li $v0, 11
	li $a0, '\n'
	syscall
		
	#Print string prompt
	li $v0, 4
	la $a0, strngInputLabel
	syscall
	
	#Print string input
	li $v0, 4
	la $a0, strngInput
	syscall
	
	
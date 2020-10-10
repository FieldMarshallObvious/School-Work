#Ass2ANoahdelAngel.asm
		.data
intIPrmpt: 	.asciiz "Enter a integer: "
intILabel:	.asciiz "The integer is "
strngIPrmpt:	.asciiz "Enter a string: "
strngILabel:	.asciiz "The string is "  
strngI: 	.space 51


		.text
		.globl main
		
main:
	#Print int prompt
	li $v0, 4
	la $a0, intIPrmpt
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
	la $a0, intILabel
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
	la $a0, strngIPrmpt
	syscall
	
	#Get input
	li $v0, 8
	la $a0, strngI
	li $a1, 50
	syscall

	
	#Print a new line
	li $v0, 11
	li $a0, '\n'
	syscall
		
	#Print string prompt
	li $v0, 4
	la $a0, strngILabel
	syscall
	
	#Print string input
	li $v0, 4
	la $a0, strngI
	syscall
	
	

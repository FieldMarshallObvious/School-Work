#Ass2ANoahdelAngel.asm
		.data
intIPrmpt: 	.asciiz "Enter a integer: "
intILabel:	.asciiz "The integer is "
strngIPrmpt:	.asciiz "Enter a string: "
strngILabel:	.asciiz "The string is "  
strngI: 	.space 51
charIPrmpt: 	.asciiz "Please enter a character: "
charILabel: 	.asciiz "The character is: "


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
			
	#Print string label
	li $v0, 4
	la $a0, strngILabel
	syscall
	
	#Print string input
	li $v0, 4
	la $a0, strngI
	syscall


	#Print a new line
	li $v0, 11
	li $a0, '\n'
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall


	#Print char prompt
	li $v0, 4
	la $a0, charIPrmpt
	syscall
	
	#Get input
	li $v0, 12
	syscall
	move $t0, $v0
	
	#Print a new line
	li $v0, 11
	li $a0, '\n'
	syscall
		
	#Print char label
	li $v0, 4
	la $a0, charILabel
	syscall
	
	#Print char input
	li $v0, 11
	move $a0, $t0
	syscall
	

	

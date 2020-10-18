# Noah del Angel, CS 2318-002, Assignment 2 Part 1 Program C
			.data
intArr:			.word 8, 1, 3, 2
initialCons:		.asciiz "Initial Conditions for the array: "
resultCons:		.asciiz "Conditions after changing the array: "

			.text
			.globl main
 main:
 	#Load array into $a0
 	la $t0, intArr
 	
 	#Load data to print
	lw $t1, 0($t0)
 	lw $t2, 4($t0)
 	lw $t3, 8($t0)
 	lw $t4, 12($t0)
 	
 	#print array
 	li $v0, 4
 	la $a0, initialCons
 	syscall
 	
 	li $v0, 1
 	move $a0, $t1
 	syscall
 	
 	move $a0, $t2
 	syscall
 	
 	move $a0, $t3
 	syscall
 	
 	move $a0, $t4
 	syscall
 	
 	#print a new line
 	li $v0, 11
	li $a0, '\n'
	syscall
 	
 	#swap 8 and 2
 	lw $t1, 0($t0)
 	lw $t2, 12($t0)
 	
 	
 	sw $t1, 12($t0)
 	sw $t2, 0($t0)
 	
 	#Reload array into $a0
 	la $a0, intArr
 	
 	#swap 3 and 1
 	lw $t1, 4($t0)
 	lw $t2, 8($t0)
 	
 	sw $t1, 8($t0)
 	sw $t2, 4($t0)
 	
 	#Reload array into $a0
 	la $a0, intArr
 	
  	#Load data to print
	lw $t1, 0($t0)
 	lw $t2, 4($t0)
 	lw $t3, 8($t0)
 	lw $t4, 12($t0)
 	
 	#print array
  	li $v0, 4
 	la $a0, resultCons
 	syscall
 	
 	li $v0, 1
 	move $a0, $t1
 	syscall
 	
 	move $a0, $t2
 	syscall
 	
 	move $a0, $t3
 	syscall
 	
 	move $a0, $t4
 	syscall
 	
 	
 	
 	
###############################################################################
# Title: Assign02P3                   Author: Noah del Angel
# Class: CS 2318-00?, Fall 2020       Submitted: <date>
###############################################################################
# Program: MIPS tranlation of a given C++ program
###############################################################################
# Pseudocode description: supplied a2p2_SampSoln.cpp
###############################################################################
		.data
a1:		.space 48
a2:		.space 48
a3:		.space 48
einStr: 	.asciiz "Enter integer #"
moStr: 		.asciiz "Max of "
ieStr:		.asciiz " ints entered..."
emiStr:		.asciiz "Enter more ints? (n or N = no, others = yes) "
begA1St:	.asciiz "beginning a1: "
nn09A1Str:	.asciiz "a1 (noneg09): "
procA1Str:	.asciiz "processed a1: "
procA2Str:	.asciiz "          a2: "
procA3Str: 	.asciiz "          a3: "
dacStr:		.asciiz "Do another case? (n or N = no, others = yes) "
dlStr:		.asciiz "================================"
byeStr:		.asciiz "bye.."

		.text 
		.globl main
main:
	
	li $t8, 'y' 		# $t8 has reply
	#While 1 Test
	WTest1: 
	li $a0, 'n' 		# $a0 has n
	beq $a0, $t8, xitW1 	# check if $t8 == n
	
	li $a0, 'N' 		# $a0 has N
	bne  $a0, $t8, begW1 	#  check if $t8 != N
	
	begW1:
		li $t1, 0 	# $t1 has used1
		la $t4, a1 	# $t4 has hopPtr1
		
		W2Test:
		li $a0, 'n'
		beq $a0, $t8, xitW1 # check if $t8 == n
		
		li $a0, 'N'  
		bne $a0, $t8, begW2 # check if $t8 != N
		
		begW2:
			# cout einStr
			li $v0, 4
			la $a0, einStr
			syscall
			
			# cout used1 + 1
			addi $t1, $t1, 1 # $t1 has used + 1
			
			li $v0, 1 
			move $a0, $t0 
			syscall
			
			# cout ':' and ' '
			li $v0, 11
			li $a0, ':'
			syscall
			
			li $v0, 11
			li $a0, ' '
			syscall
			
			#cin *hopPtr1
			li $v0, 5
			syscall
			
			move $v0, $t4
			
			sll $t4, $t4, 4 # hopPtr1++
			addi $t1, $t1, 1 # used1++
			
			# if used1 >= 12
			li $v0, 12
			slt $v1, $v0, $t1 # $v1 has used1 > 12 
			
			li $v0, 1
			
			beq $v1, $v0, else1 # if used 1 > 12
			beq $v0, $t1, else1 # if used 1 == 12
				
				 # cout emiStr
				 li $v0, 4
				 la $a0, emiStr
				 syscall
				 
				 # cin reply
				 li $v0, 8
				 li $a1, 10
				 syscall
				 
				 move $v0, $t1 #$t1 has reply
			
			else1:
				# cout moStr and 12 and ieStr
				li $v0, 4
				la $a0, moStr
				syscall
				
				li $v0, 1
				li $a0, 12
				syscall
				
				li $v0, 4
				la $a0, ieStr
				syscall
				
				li $v0, 11
				li $a0, '\n'
				syscall
			endI1:
			
			
			
		j W2Test
		
		xitW2:
	j WTest1
	
	xitW1:
	li $v0, 4
	la $a0, dlStr
	syscall 
	
	la $a0, byeStr
	syscall
	
	la $a0, dlStr 
	syscall
	
	#Graceful exit
 	li $v0, 10
	syscall
	
	

	
	
	
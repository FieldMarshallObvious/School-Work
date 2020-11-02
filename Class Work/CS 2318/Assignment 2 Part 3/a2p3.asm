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
begA1Str:	.asciiz "beginning a1: "
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
	beq $a0, $t8, begW1 	# check if $t8 == n
	
	li $a0, 'N' 		# $a0 has N
	bne  $a0, $t8, begW1 	#  check if $t8 != N
	
	begW1:
		li $t1, 0 	# $t1 has used1
		la $t4, a1 	# $t4 has hopPtr1
		
		j W2Test
		
		begW2:
			# cout einStr
			li $v0, 4
			la $a0, einStr
			syscall
			
			# cout used1 + 1
			addi $v1, $t1, 1 # $t1 has used + 1
			
			li $v0, 1 
			move $a0, $v1 
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
			
			addi $t4, $t4, 1 # *hopPtr1++
			addi $t1, $t1, 1 # used1++
			
			# if used1 < 12
			li $v0, 12

			bge $t1, $v0, else1 # if used 1 > 12
			beq $v0, $t1, else1 # if used 1 == 12
				
				 # cout emiStr
				 li $v0, 4
				 la $a0, emiStr
				 syscall
				 
				 # cin reply
				 li $v0, 8
				 li $a1, 10
				 syscall
				 
				 move $t8, $v0 #$t8 has reply
				 
				 j endI1
			
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
				
				li $t8, 'n'
			endI1:
			
		W2Test:
		li $a0, 'n'
		beq $a0, $t8, xitW2 # check if $t8 == n
		
		li $a0, 'N'  
		bne $a0, $t8, begW2 # check if $t8 != N
		xitW2:
			
			#cout begA1sStr
			li $v0, 4
			la $a0, begA1Str
			syscall
			
			# if used > 0
			slt $v1, $t1, $s0 # $v1 has used 1 < 0
			
			li $v0, 1
			blt $t1, $v0, endI2 # if used 1 < 0
			beq $t1, $s0, endI2  # if used 1 == 0
				move $t4, $t1 # hopPtr1 = a1
				
				la $v0, a1
				
				# endPtr1 = a1 + used1
				sll $v1,$1, 2
				add $a1, $v0, $v1
				
				begDW1:
					# Cout *hopPtr1 and ' ' and ' '
					li $v0, 1
					lw $a0, 0($t4)
					syscall
				endDW1:
				DWTest1:
				blt $t4, $a1, begDW1
			
			endI2:
			
			li $v0, 11
			li $a0, '\n'
			syscall
			
			# if used 1 < = 0
			bltz $t1, endI3 # if used < 0
			beq $t1, $s0, endI3 # if used == 0
				move $t4, $a1 # hopPtr1 = a1
				
				j FTest1
				begF1:
					
					lw $t0, 0($t4)  # target = *hopPtr1
					
					# if target >= 0 && target <= 9
					bgez $t0, endI4
					beq $t0, $s0, endI4
					
					li $v0, 9
					
					blt $t0, $v0, endI4
					beq $t0, $v0, endI4
						
					# hopPtr11 = hopPtr1 + 1
					la $v0, a1
					move $t4, $v0
					
						j FTest2
						begF2:
							#  *(hopPtr11 - 1) = *hopPtr11
							lw $v0, 0($t6)
							sw $t6, -4($t6)
							
							#  ++hopPtr11
							addi $t4, $t4, 4
						FTest2: 
						blt $t6, $a1, begF2 # if hopPtr11 < endPtr1 
						endF2:
						
						addi $t1, $t1, -1 # used 1 --
						addi $a1, $a1, -4 # endPtr1 --
						addi $t4, $t4, -4 # hopPtr 1 -- 
					endI4:
					addi $t4, $t4, 4 # hopPtr 1 ++
				FTest1:	
				blt $t4, $a1, begF1 # if hopPtr1 < endPtr1
				endF1:
				
				# cout nn09A1Str
				li $v0, 4
				la $a0, nn09A1Str
				syscall
				
				# if used1 <= 0
				bltz $t1, endI5 # if used1 < 0
				beq $t1, $s0, endI5 # if used1 == 0
					
					la $t1, a1 # hopPtr1 = a1
					
					# endPtr1 = a1 + used1
					la $v0, a1
					add $v1, $v0, $t1
					move $a1, $v1
					
					begDW2:
						# cout *hopPtr ' ' ' '
						li $v0, 1
						lw $a0, 0($t4)
						syscall
						
						
						li $v0, 11
						li $a0, ' '
						syscall
						
						li $a0, ' '
						syscall
						
						# ++hopPtr1
						addi $t4, $t4, 4
					endDW2:
					DWTest2:
						blt $t4, $a1, begDW2 # if hopPtr1 < endPtr1
				endI5:
				
				li $a0, '\n'
				syscall
				
				li $t2, 0 # used2 = 0
				li $t3, 0 # used3 = 0
				
				la $t4, a1 # hopPtr1 = a1
				la $t5, a2 # hopPtr2 = a2
				la $t7, a3 # hopPtr3 = a3
				
				 # endPtr1 = a1 + used1
				 la $v0, a1 
				 add $v1, $v0, $t1
				 move $a1, $v1
				 
				 
				j WTest3
				begW3:
				
				WTest3:
			endI3:
		
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
	
	

	
	
	

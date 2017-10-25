 # prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by <<linchen CHEN>>, August 2017

	.data
	.align 2
main_ret_save: .space 4

str1:
	.asciiz "# Iterations: "

str2:
	.asciiz "=== After iteration "
	
str3:	
	.asciiz " ==="
	
eol:
	.asciiz "\n"	
	
point:
	.asciiz	"."

number:
	.asciiz	"#"

	
	.text
	.globl main
main:
	sw   $ra, main_ret_save

# ---------------------------------------------------------------
	la	$a0,str1
	li	$v0,4
	syscall				#printf("# Iterations: ");
	li	$v0,5
	syscall				#scanf("%d",v0)
	move $s0,$v0		#$s0 = maxiters
	
	li	$s1,1			#$s1 = n, n = 1
loop1:
	lw	$t0,N			#load $t0 = N 
	bgt	$s1,$s0,end_main	#if n > maxiters, finish loop
	
	li	$s2,0		#i = 0($s2 = i)
loop2:
	bge	$s2,$t0,end_loop2	#if i >= N, finish loop

	li	$s3,0		#$s3 = j, j =0
loop3:	
	bge	$s3,$t0,end_loop3	#if j >= N, finish loop	
#----jump to neighbours function
	move	$a0,$s2		#a0 = i
	move	$a1,$s3		#a1 = j	
	
	jal	neighbours
	move $t1,$v0	#t1 = nn

#---------IF things	
	lw	$t0,N	#assign N=t0 again after jump back from neighbours	
	mul	$t2,$s2,$t0	#t2 = board[i]
	add	$t3,$t2,$s3	#t3 = board[i][j]
	lb	$t4,board($t3)	#t4 = *board[i][j]
	li	$t5,1	#$t5 =1 forever
	li	$t6,2
	li	$t7,3
	li	$t8,0
if:	
	bne $t4,$t5,elif	# *board[i][j] != 1 jump to else if
inside_if:
	bge	$t1,$t6,inside_elif #check????????????????????
	li  $t8, 0
	sb	$t8,newBoard($t3)	#newBoard[i][j] = 0
	j	endif
inside_elif:	
	bne	$t1,$t6,OR	#nn !=2 jump to inside else
	li  $t5, 1
	sb	$t5,newBoard($t3)	#newBoard[i][j] = 1
	j	endif
OR:	
	bne	$t1,$t7,inside_else	#nn !=3 jump to inside else
	li  $t5, 1
	sb	$t5,newBoard($t3)	#newBoard[i][j] = 1
	j	endif
inside_else:
	li  $t8, 0
	sb	$t8,newBoard($t3)	#newBoard[i][j] = 0
	j	endif
elif:		
	bne	$t1,$t7,else		# *nn != 3 jump to else
	li  $t5, 1
	sb	$t5,newBoard($t3)	#newBoard[i][j] = 1	
	j	endif
else:
	li  $t8, 0
	sb	$t8,newBoard($t3)	#newBoard[i][j] = 0
	j	endif
endif:	
#---------
	
	add	$s3,$s3,1		#j++;
	j loop3
end_loop3:	
	add	$s2,$s2,1		#i++;
	j	loop2			
end_loop2:	
	
	#---following is in loop1
	
	la	$a0,str2
	li	$v0,4
	syscall				#printf("=== After iteration ");
		
	move	$a0,$s1
	li	$v0,1
	syscall				#printf("%d",s1 = n)
	
	la	$a0,str3
	li	$v0,4
	syscall				#printf(" ===");
		
	la	$a0,eol	
	li	$v0,4
	syscall				#printf("\n")

##------------------------------------------copyBackAndShow function	
#print matrix
#new i and j for copyBackAndShow void function
#forget the $s2,$s3
	li	$t5,0	#t5 = i = 0
print_for1:
	bge	$t5,$t0,end_print_for1	#i>=N go to end_function
	li	$t6,0	#t6 = 0 = j
print_for2:
	bge	$t6,$t0,end_print_for2	#j>=N go to end_second loop
	mul	$t2,$t5,$t0		#[i] N*i
	add	$t3,$t2,$t6		#[i][j]	N*i+j
	lb	$t4,newBoard($t3)	#t4 = *newBoard[i][j]  ##??????
	sb	$t4,board($t3)		#board[i][j] = *t4;
print_if:
	bnez	$t4,print_else	#$t4 == 0
	la	$a0,point
	li	$v0,4
	syscall		#print(".")
	
	j print_end_if
print_else:
		
	la	$a0,number
	li	$v0,4
	syscall		#print("#")
	
	j print_end_if
print_end_if:	
	addi	$t6,$t6,1	#j++
	j	print_for2

end_print_for2:
	la	$a0,eol
	li	$v0,4
	syscall		#print('\n')
	
	addi	$t5,$t5,1	#x++
	j	print_for1
end_print_for1:	
#-------------------------------------------end copyBackAndShow function	
	addi	$s1,$s1,1		#n++;
	j loop1

# ---------------------------------------------------
end_main:
	lw   $ra, main_ret_save
	jr   $ra


# The other functions go here

neighbours:
	#prologue
	addi	$sp,$sp,-12
	sw	$fp,8($sp)
	la	$fp,8($sp)
	sw	$ra,4($sp)
	sw	$s4,0($sp)		#take $s2=nn as a return value at the end

	li		$s4,0		#nn = 0
	
	li	$t1,-1			#t1 = x = -1
	li	$t2,1			#t2 = 1 unchange as a conditioner
nei_loop1:	
	bgt	$t1,$t2,end_nei_loop1
	li	$t3,-1			#t5 = y = -1
	
nei_loop2:
	bgt	$t3,$t2,end_nei_loop2

	#if (i+x < 0 || i+x > N-1) continue	
	add	$t4,$t1,$a0	#t4 = i+x 
	bltz	$t4,end_continue
	lw	$t5,N
	addi $t5,$t5,-1	#t5 = N-1
	bgt	$t4,$t5,end_continue	
			
	#if (j+y < 0 || j+y > N-1) continue;	
	add	$t6,$t3,$a1		#t6 = y+j
	bltz	$t6,end_continue
	bgt	$t6,$t5,end_continue
	
	#if (x == 0 && y == 0) continue;
	beqz	$t1,next_if
	j	end_next_if
next_if:	
	beqz	$t3,end_continue
end_next_if:	
	#if (board[i+x][j+y] == 1) nn++;
	lw	$t0,N		#t0 = N
	mul	$t7,$t4,$t0	#t7 = board[i+x]
	add	$t8,$t6,$t7	#board[i+x][j+y]
	lb	$t8,board($t8)	#*board[i+x][j+y] = t8
	bne	$t8,$t2,end_continue	#*board[i+x][j+y] != 1
	addi	$s4,$s4,1	#nn++
	
end_continue:	
	addi	$t3,$t3,1	#y++
	j	nei_loop2
end_nei_loop2:	
	addi	$t1,$t1,1	#x++;
	j	nei_loop1	
end_nei_loop1:	

	#end of neighbours function
	move $v0,$s4
	lw	$s4,0($sp)
	lw	$ra,4($sp)
	lw	$fp,8($sp)
	la	$fp,8($sp)
	addi $sp,$sp,12
	jr $ra

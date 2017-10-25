# COMP1521 Lab 04 ... Simple MIPS assembler
# why happen?  when use $t0 instead of $t1
#linchen chen 25/08/2017

### Global data

   .data
msg1:
   .asciiz "n: "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

### main() function
	.data
n:	.space 4

   .data
   .align 2
main_ret_save:
   .word 4

   .text
   .globl main

main:
	sw   $ra, main_ret_save
	
	#  ... your code for main() goes here
	la	$a0,msg1
	li	$v0,4
	syscall				#printf("n: ",msg1)
	li	$v0,5			
	syscall				#scanf("%d",$reg[v0])
	sw	$v0,n			# n = $reg[v0]
	
	la	$a0,msg2		
	li	$v0,4	
	syscall				#printf("n! = ")

	lw	$s0,n
	move	$a0,$s0
	jal fac	
	move	$a0,$v0
	li	$v0,1
	syscall										
			
	la	$a0,eol		
	li	$v0,4
	syscall				#printf("\n")

	lw   $ra, main_ret_save
	jr   $ra           # return

### fac() function

   .data
   .align 2
fac_ret_save:
   .space 4

   .text

fac:
   sw   $ra, fac_ret_save

#  ... your code for fac() goes here
	li	$t1,1		#i = 1
	li	$t2,1		#f = 1
while:
	move	$t3,$a0
	bgt	$t1,$t3,end_while
	mul	$t2,$t2,$t1
	addi	$t1,$t1,1	#i++;	
	j	while	
end_while:
	move	$v0,$t2
	lw	$ra, fac_ret_save
	jr  $ra            # return ($v0)


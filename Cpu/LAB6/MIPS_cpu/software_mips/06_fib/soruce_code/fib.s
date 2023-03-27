	.file	1 "fib.c"
gcc2_compiled.:
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
main:
	.frame	$sp,32,$ra		# vars= 0, regs= 4/0, args= 16, extra= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,32
	sw	$ra,28($sp)
	sw	$s2,24($sp)
	sw	$s1,20($sp)
	sw	$s0,16($sp)
	li	$s2,-2147483648			# 0x80000000
	li	$s1,47			# 0x2f
	move	$s0,$zero
.L6:
	.set	noreorder
	.set	nomacro
	jal	fib
	move	$a0,$s0
	.set	macro
	.set	reorder

	sll	$v1,$s0,2
	addu	$v1,$v1,$s2
	#.set	volatile
	sw	$v0,0($v1)
	#.set	novolatile
	addu	$s0,$s0,1
	slt	$v0,$s0,$s1
	.set	noreorder
	.set	nomacro
	bne	$v0,$zero,.L6
	move	$v0,$zero
	.set	macro
	.set	reorder

	lw	$ra,28($sp)
	lw	$s2,24($sp)
	lw	$s1,20($sp)
	lw	$s0,16($sp)
	.set	noreorder
	.set	nomacro
	j	$ra
	addu	$sp,$sp,32
	.set	macro
	.set	reorder

	.end	main
	.size	main,.-main
	.align	2
	.globl	fib
	.set	nomips16
	.ent	fib
fib:
	.frame	$sp,0,$ra		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	slt	$v1,$a0,2
	.set	noreorder
	.set	nomacro
	bne	$v1,$zero,.L16
	move	$v0,$a0
	.set	macro
	.set	reorder

	move	$a3,$zero
	li	$v1,1			# 0x1
	slt	$v0,$a0,2
	.set	noreorder
	.set	nomacro
	bne	$v0,$zero,.L12
	li	$a1,2			# 0x2
	.set	macro
	.set	reorder

.L14:
	addu	$a2,$v1,$a3
	move	$a3,$v1
	addu	$a1,$a1,1
	slt	$v0,$a0,$a1
	.set	noreorder
	.set	nomacro
	beq	$v0,$zero,.L14
	move	$v1,$a2
	.set	macro
	.set	reorder

.L12:
	move	$v0,$a2
.L16:
	j	$31
	.end	fib
	.size	fib,.-fib

	.extern	fib
	.type	 fib,@function
	.ident	"GCC: (GNU) 2.96-mipssde-031117"

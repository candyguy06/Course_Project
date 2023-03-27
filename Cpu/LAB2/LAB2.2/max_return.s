	.file	1 "max_return.c"
	.section .mdebug.abi32
	.previous
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
main:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	sw	$31,16($sp)
	li	$4,44			# 0x2c
	li	$5,87			# 0x57
	jal	sum
	li	$6,2			# 0x2

	li	$3,536870912			# 0x20000000
	sw	$2,0($3)
	move	$2,$0
	lw	$31,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.align	2
	.globl	sum
	.set	nomips16
	.ent	sum
sum:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addu	$2,$4,$5
	j	$31
	addu	$2,$2,$6

	.set	macro
	.set	reorder
	.end	sum
	.size	sum, .-sum
	.ident	"GCC: (GNU) 3.4.4 mipssde-6.06.01-20070420"

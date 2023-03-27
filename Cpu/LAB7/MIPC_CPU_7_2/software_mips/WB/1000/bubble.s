	.file	1 "bubble.c"
	.section .mdebug.abi32
	.previous
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
main:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	li	$7,268435456			# 0x10000000
	li	$6,273678336			# 0x10500000
	li	$5,1200			# 0x4b0
	move	$4,$0
.L5:
	sll	$2,$4,2
	addu	$3,$2,$6
	addu	$2,$2,$7
	lw	$2,0($2)
	addiu	$2,$2,1
	sw	$2,0($3)
	addiu	$4,$4,1
	slt	$2,$4,$5
	bne	$2,$0,.L5
	move	$2,$0

	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.4.4 mipssde-6.06.01-20070420"

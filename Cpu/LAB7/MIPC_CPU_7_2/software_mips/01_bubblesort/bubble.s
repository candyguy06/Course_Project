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
	
	li	$9,268435456			# 0x10000000
	li	$10,100			# 0x64
	move	$8,$0
	addiu	$11,$10,-1
.L10:
	subu	$2,$10,$8
	addiu	$2,$2,-1
	blez	$2,.L14
	move	$6,$0

	subu	$2,$10,$8
	addiu	$7,$2,-1
	sll	$2,$6,2
.L15:
	addu	$3,$2,$9
	lw	$4,4($3)
	lw	$5,0($3)
	slt	$2,$4,$5
	beq	$2,$0,.L7
	nop

	sw	$4,0($3)
	sw	$5,4($3)
.L7:
	addiu	$6,$6,1
	slt	$2,$6,$7
	bne	$2,$0,.L15
	sll	$2,$6,2

.L14:
	addiu	$8,$8,1
	slt	$2,$8,$11
	bne	$2,$0,.L10
	move	$2,$0

	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.ident	"GCC: (GNU) 3.4.4 mipssde-6.02.02-20050602"

	.file	1 "quicksort.c"
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
	li	$4,268435456			# 0x10000000
	move	$5,$0
	jal	quicksort
	li	$6,99			# 0x63

	move	$2,$0
	lw	$31,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	main
	.align	2
	.globl	quicksort
	.set	nomips16
	.ent	quicksort
quicksort:
	.frame	$sp,48,$31		# vars= 0, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-48
	sw	$31,40($sp)
	sw	$21,36($sp)
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	move	$19,$4
	move	$20,$5
	slt	$2,$5,$6
	beq	$2,$0,.L2
	move	$21,$6

	move	$17,$5
	addiu	$16,$6,1
	sll	$2,$5,2
	addu	$2,$2,$4
	lw	$18,0($2)
.L17:
	addiu	$17,$17,1
.L19:
	sll	$2,$17,2
	addu	$2,$2,$19
	lw	$2,0($2)
	slt	$2,$2,$18
	bne	$2,$0,.L17
	nop

.L10:
	addiu	$16,$16,-1
	sll	$2,$16,2
	addu	$2,$2,$19
	lw	$2,0($2)
	slt	$2,$18,$2
	bne	$2,$0,.L10
	slt	$2,$17,$16

	beq	$2,$0,.L18
	move	$4,$19

	move	$5,$17
	jal	swap
	move	$6,$16

	slt	$2,$17,$16
.L18:
	bne	$2,$0,.L19
	addiu	$17,$17,1

	move	$4,$19
	move	$5,$20
	jal	swap
	move	$6,$16

	move	$4,$19
	move	$5,$20
	jal	quicksort
	addiu	$6,$16,-1

	move	$4,$19
	addiu	$5,$16,1
	jal	quicksort
	move	$6,$21

.L2:
	lw	$31,40($sp)
	lw	$21,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
	.end	quicksort
	.align	2
	.globl	swap
	.set	nomips16
	.ent	swap
swap:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	sll	$5,$5,2
	addu	$5,$5,$4
	lw	$3,0($5)
	sll	$6,$6,2
	addu	$6,$6,$4
	lw	$2,0($6)
	sw	$2,0($5)
	j	$31
	sw	$3,0($6)

	.set	macro
	.set	reorder
	.end	swap
	.ident	"GCC: (GNU) 3.4.4 mipssde-6.02.02-20050602"

	.file	1 "heapsort.c"
gcc2_compiled.:
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
main:
	.frame	$sp,24,$ra		# vars= 0, regs= 1/0, args= 16, extra= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,24
	sw	$ra,16($sp)
	li	$a0,2147418112			# 0x7fff0000
	ori	$a0,$a0,0xfffc
	.set	noreorder
	.set	nomacro
	jal	heapsort
	li	$a1,100			# 0x64
	.set	macro
	.set	reorder

	move	$v0,$zero
	lw	$ra,16($sp)
	.set	noreorder
	.set	nomacro
	j	$ra
	addu	$sp,$sp,24
	.set	macro
	.set	reorder

	.end	main
	.size	main,.-main
	.align	2
	.globl	heapsort
	.set	nomips16
	.ent	heapsort
heapsort:
	.frame	$sp,32,$ra		# vars= 0, regs= 4/0, args= 16, extra= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,32
	sw	$ra,28($sp)
	sw	$s2,24($sp)
	sw	$s1,20($sp)
	sw	$s0,16($sp)
	move	$s1,$a1
	srl	$v0,$s1,31
	addu	$v0,$s1,$v0
	sra	$s0,$v0,1
	.set	noreorder
	.set	nomacro
	blez	$s0,.L5
	move	$s2,$a0
	.set	macro
	.set	reorder

	move	$a0,$s2
.L14:
	move	$a1,$s0
	.set	noreorder
	.set	nomacro
	jal	adjust
	move	$a2,$s1
	.set	macro
	.set	reorder

	addu	$s0,$s0,-1
	.set	noreorder
	.set	nomacro
	bgtz	$s0,.L14
	move	$a0,$s2
	.set	macro
	.set	reorder

.L5:
	addu	$s0,$s1,-1
	.set	noreorder
	.set	nomacro
	blez	$s0,.L15
	lw	$ra,28($sp)
	.set	macro
	.set	reorder

	move	$a0,$s2
.L16:
	li	$a1,1			# 0x1
	.set	noreorder
	.set	nomacro
	jal	swap
	addu	$a2,$s0,1
	.set	macro
	.set	reorder

	move	$a0,$s2
	li	$a1,1			# 0x1
	.set	noreorder
	.set	nomacro
	jal	adjust
	move	$a2,$s0
	.set	macro
	.set	reorder

	addu	$s0,$s0,-1
	.set	noreorder
	.set	nomacro
	bgtz	$s0,.L16
	move	$a0,$s2
	.set	macro
	.set	reorder

	lw	$ra,28($sp)
.L15:
	lw	$s2,24($sp)
	lw	$s1,20($sp)
	lw	$s0,16($sp)
	.set	noreorder
	.set	nomacro
	j	$ra
	addu	$sp,$sp,32
	.set	macro
	.set	reorder

	.end	heapsort
	.size	heapsort,.-heapsort
	.align	2
	.globl	adjust
	.set	nomips16
	.ent	adjust
adjust:
	.frame	$sp,0,$ra		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	sll	$v0,$a1,2
	addu	$v0,$v0,$a0
	lw	$a3,0($v0)
	.set	noreorder
	.set	nomacro
	b	.L18
	sll	$a1,$a1,1
	.set	macro
	.set	reorder

.L22:
	addu	$v0,$a1,$v0
	sra	$v0,$v0,1
	sll	$v0,$v0,2
	addu	$v0,$v0,$a0
	sll	$v1,$a1,2
	addu	$v1,$v1,$a0
	lw	$v1,0($v1)
	sw	$v1,0($v0)
	sll	$a1,$a1,1
.L18:
	slt	$v0,$a2,$a1
	.set	noreorder
	.set	nomacro
	bne	$v0,$zero,.L25
	srl	$v0,$a1,31
	.set	macro
	.set	reorder

	slt	$v0,$a1,$a2
	.set	noreorder
	.set	nomacro
	beq	$v0,$zero,.L26
	sll	$v0,$a1,2
	.set	macro
	.set	reorder

	addu	$v0,$v0,$a0
	lw	$v1,0($v0)
	lw	$v0,4($v0)
	slt	$v1,$v1,$v0
	addu	$a1,$a1,$v1
	sll	$v0,$a1,2
.L26:
	addu	$v0,$v0,$a0
	lw	$v0,0($v0)
	slt	$v0,$v0,$a3
	.set	noreorder
	.set	nomacro
	beq	$v0,$zero,.L22
	srl	$v0,$a1,31
	.set	macro
	.set	reorder

.L25:
	addu	$v0,$a1,$v0
	sra	$v0,$v0,1
	sll	$v0,$v0,2
	addu	$v0,$v0,$a0
	.set	noreorder
	.set	nomacro
	j	$31
	sw	$a3,0($v0)
	.set	macro
	.set	reorder

	.end	adjust
	.size	adjust,.-adjust
	.align	2
	.globl	swap
	.set	nomips16
	.ent	swap
swap:
	.frame	$sp,0,$ra		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	sll	$a1,$a1,2
	addu	$a1,$a1,$a0
	lw	$v1,0($a1)
	sll	$a2,$a2,2
	addu	$a2,$a2,$a0
	lw	$v0,0($a2)
	sw	$v0,0($a1)
	.set	noreorder
	.set	nomacro
	j	$31
	sw	$v1,0($a2)
	.set	macro
	.set	reorder

	.end	swap
	.size	swap,.-swap

	.extern	swap
	.type	 swap,@function
	.extern	adjust
	.type	 adjust,@function
	.extern	heapsort
	.type	 heapsort,@function
	.ident	"GCC: (GNU) 2.96-mipssde-031117"

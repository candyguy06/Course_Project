	.file	1 "data_struct.c"
	.section .mdebug.abi32
	.previous
	.rdata
	.align	2
.LC0:
	.word	60
	.word	70
	.word	70
	.align	2
.LC1:
	.word	70
	.word	50
	.word	80
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
main:
	.frame	$sp,32,$31		# vars= 32, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-32
	li	$4,536870912			# 0x20000000
	ori	$6,$4,0x20
	lui	$2,%hi(.LC0)
	lw	$9,%lo(.LC0)($2)
	addiu	$2,$2,%lo(.LC0)
	lw	$7,4($2)
	lw	$8,8($2)
	lui	$2,%hi(.LC1)
	lw	$5,%lo(.LC1)($2)
	addiu	$2,$2,%lo(.LC1)
	lw	$3,4($2)
	lw	$2,8($2)
	sw	$5,16($sp)
	sw	$3,20($sp)
	sw	$2,24($sp)
	sw	$9,0($4)
	sw	$7,4($4)
	sw	$8,8($4)
	lw	$3,20($sp)
	lw	$4,24($sp)
	lw	$2,16($sp)
	sw	$2,0($6)
	sw	$3,4($6)
	sw	$4,8($6)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.4.4 mipssde-6.06.01-20070420"

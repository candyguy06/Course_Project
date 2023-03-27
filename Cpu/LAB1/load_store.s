	.file	1 "load_store.c"
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


	
	li	$3,536870912			# 0x20000000
	li	$2,1
	sw	$2,0($3)
	li	$2,2
	sw	$2,4($3)
	lw	$8,3
	sw	$8,8($3)

	j	$31
	move	$2,$0

	
	
	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.4.4 mipssde-6.06.01-20070420"

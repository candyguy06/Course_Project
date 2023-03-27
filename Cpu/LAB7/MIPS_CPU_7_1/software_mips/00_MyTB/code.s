	.text
	.globl	main
	.globl	flush_r8_r23
	.globl	show_new
	.globl	show_result
	.globl	show_pass
	.globl	show_error
	.globl	show_init
	.globl	show_case01
	.globl	show_case02
	.globl	show_case03
	.globl	show_case04
	.globl	show_case05
	.globl	show_case06
	.globl	show_case07
	.globl	show_case08
	.globl	show_case09
	.globl	show_case10
	.globl	show_case11
	.globl	show_case12
	.extern load_check
	.extern	shift_check
	.extern	mul_check
	.extern	arithm_check
	.extern	move_check
	
	

main:	SUBU	$sp, $sp, 4		
	SW	$ra, 0($sp)
	
	LW	$t0, USER_str
	LUI	$t1, 0x8000
	SW	$t0, 0($t1)

	JAL	load_check
	JAL	shift_check
	JAL	mul_check
	JAL	arithm_check	
	JAL	move_check

	#---------------------------------------------
	#	Return to system code
	#---------------------------------------------	
	LW	$ra, 0($sp)
	ADDU	$sp, $sp, 4
	JR	$ra	

#----------------------------------------------------------------------
#	Show "NEW" @ 0x80000008
#----------------------------------------------------------------------		
show_new:

	LW	$t0, NEW_str
	LUI	$t1, 0x8000
	SW	$t0, 8($t1)
	JR	$ra
		
#----------------------------------------------------------------------
#	Show Result
#----------------------------------------------------------------------		
show_result:

	LW	$t0, ALL_str
	LW	$t1, OK_str
	LUI	$t2, 0x8000
	SW	$t0, 4($t2)
	SW	$t1, 8($t2)
	JR	$ra

#----------------------------------------------------------------------
#	Show "PASS" @ 0x80000008
#----------------------------------------------------------------------		
show_pass:

	LW	$t0, PASS_str
	LUI	$t1, 0x8000
	SW	$t0, 8($t1)
	JR	$ra
	
#----------------------------------------------------------------------
#	Show "ERRO" @ 0x80000008
#----------------------------------------------------------------------		
show_error:

	LW	$t0, ERRO_str
	LUI	$t1, 0x8000
	SW	$t0, 8($t1)
	JR	$ra
	
#----------------------------------------------------------------------
#	Show "----" @ 0x80000008
#----------------------------------------------------------------------		
show_init:

	LW	$t0, INIT_str
	LUI	$t1, 0x8000
	SW	$t0, 8($t1)
	JR	$ra
		
#----------------------------------------------------------------------
#	Show "C=#" @ 0x80000004
#----------------------------------------------------------------------		
show_case01:
	LW	$t0, C01_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case02:
	LW	$t0, C02_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case03:
	LW	$t0, C03_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case04:
	LW	$t0, C04_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case05:
	LW	$t0, C05_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case06:
	LW	$t0, C06_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case07:
	LW	$t0, C07_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case08:
	LW	$t0, C08_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case09:
	LW	$t0, C09_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra

show_case10:
	LW	$t0, C10_str
	LUI	$t1, 0x8000
	SW	$t0, 4($t1)
	JR	$ra
		
#----------------------------------------------------------------------
#	Flush $8 ~ $23
#----------------------------------------------------------------------		
flush_r8_r23:

	ADD	$8, $0, $0
	ADD	$9, $0, $0
	ADD	$10, $0, $0
	ADD	$11, $0, $0
	ADD	$12, $0, $0
	ADD	$13, $0, $0
	ADD	$14, $0, $0
	ADD	$15, $0, $0
	ADD	$16, $0, $0
	ADD	$17, $0, $0
	ADD	$18, $0, $0
	ADD	$19, $0, $0
	ADD	$20, $0, $0
	ADD	$21, $0, $0
	ADD	$22, $0, $0
	ADD	$23, $0, $0
	JR	$ra
	
	
USER_str: 	.ascii	"USER"
NEW_str: 	.ascii	"NEW "
ALL_str:	.ascii	"ALL "
OK_str:		.ascii	"OK  "
PASS_str:	.ascii	"PASS"
ERRO_str:	.ascii	"ERRO"
INIT_str:	.ascii	"----"
C01_str:	.ascii	"C=01"
C02_str:	.ascii	"C=02"
C03_str:	.ascii	"C=03"
C04_str:	.ascii	"C=04"
C05_str:	.ascii	"C=05"
C06_str:	.ascii	"C=06"
C07_str:	.ascii	"C=07"
C08_str:	.ascii	"C=08"
C09_str:	.ascii	"C=09"
C10_str:	.ascii	"C=10"	
C11_str:	.ascii	"C=11"	
C12_str:	.ascii	"C=12"	

		
	.text
	.globl	move_check
	.extern flush_r8_r23
	.extern	show_new
	.extern	show_init
	.extern	show_pass
	.extern	show_error
	.extern	show_result
	.extern	show_case01
	.extern	show_case02
	#.extern	show_case03
	#.extern	show_case04
	#.extern	show_case05
	#.extern	show_case06
	#.extern	show_case07

move_check:

	SUBU	$sp, $sp, 4		
	SW	$ra, 0($sp)
	
	LW	$t0, MOVE_str
	LUI	$t1, 0x8000
	SW	$t0, 0($t1)
	
	JAL	show_new	
	
	#---------------------------------------------
	# Case=01	MOVZ instruction	
	#---------------------------------------------
	JAL	show_case01
	JAL	show_init

	JAL	flush_r8_r23
	LW	$8, data1
	
	ADDI	$9, $0, -1
	ADDI	$10, $0, 0
	ADDI	$11, $0, 1
	ADDI	$12, $0, 2
	
	MOVZ	$13, $8, $9
	MOVZ	$14, $8, $10
	MOVZ	$15, $8, $11
	MOVZ	$16, $8, $12
	
	SUB	$14, $14, $8
	
	OR	$13, $13, $14
	OR	$13, $13, $15
	OR	$13, $13, $16
	BNE	$13, $0, error

	JAL	show_pass

	#---------------------------------------------
	# Case=02	MOVN instruction	
	#---------------------------------------------
	JAL	show_case02
	JAL	show_init

	JAL	flush_r8_r23
	LW	$8, data1
	
	ADDI	$9, $0, -1
	ADDI	$10, $0, 0
	ADDI	$11, $0, 1
	ADDI	$12, $0, 2
	
	MOVN	$13, $8, $9
	MOVN	$14, $8, $10
	MOVN	$15, $8, $11
	MOVN	$16, $8, $12
	
	SUB	$13, $13, $8
	SUB	$15, $15, $8
	SUB	$16, $16, $8
			
	OR	$13, $13, $14
	OR	$13, $13, $15
	OR	$13, $13, $16
	BNE	$13, $0, error

	JAL	show_pass
	

	#---------------------------------------------
	#	Return to main code
	#---------------------------------------------	
	JAL	show_result
	B	end
	
error:	JAL	show_error

end:	LW	$ra, 0($sp)
	ADDU	$sp, $sp, 4
	JR	$ra
		
	
MOVE_str:
	.ascii	"MOVE"
	
data1:
	.word	0x12345678

	
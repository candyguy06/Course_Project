	.text
	.globl	load_check
	.extern flush_r8_r23
	.extern	show_new
	.extern	show_init
	.extern	show_pass
	.extern	show_error
	.extern	show_result
	.extern	show_case01
	.extern	show_case02
	.extern	show_case03
	.extern	show_case04
	.extern	show_case05
	.extern	show_case06
	.extern	show_case07
	.extern	show_case08

load_check:

	SUBU	$sp, $sp, 4		
	SW	$ra, 0($sp)
	
	LW	$t0, LOAD_str
	LUI	$t1, 0x8000
	SW	$t0, 0($t1)
	
	JAL	show_new	
	
	#---------------------------------------------
	# Case=01	LB instruction	
	#---------------------------------------------
	JAL	show_case01
	JAL	show_init

	LA	$2, ds_load 
	LA	$3, result_lb

	JAL	flush_r8_r23
			
	LB	$8, 0($2)
	LB	$9, 1($2)
	LB	$10, 2($2)
	LB	$11, 3($2)
	LB	$12, 4($2)
	LB	$13, 5($2)
	LB	$14, 6($2)
	LB	$15, 7($2)
        
        LW 	$16, 0($3)
        LW 	$17, 4($3)
        LW 	$18, 8($3)
        LW 	$19, 12($3)
        LW 	$20, 16($3)
        LW 	$21, 20($3)
        LW 	$22, 24($3)
        LW 	$23, 28($3)
	
        SUB 	$8,  $8 , $16
        SUB 	$9,  $9 , $17
        SUB 	$10, $10, $18
        SUB 	$11, $11, $19
        SUB 	$12, $12, $20
        SUB 	$13, $13, $21
        SUB 	$14, $14, $22
        SUB 	$15, $15, $23	

	OR	$8, $8, $9
	OR	$8, $8, $10
	OR	$8, $8, $11
	OR	$8, $8, $12
	OR	$8, $8, $13
	OR	$8, $8, $14
	OR	$8, $8, $15
	BNE	$8, $0, error
	
	JAL	show_pass

	#---------------------------------------------
	# Case=02	LBU instruction	
	#---------------------------------------------
	JAL	show_case02
	JAL	show_init

	LA	$2, ds_load 
	LA	$3, result_lbu

	JAL	flush_r8_r23
			
	LBU	$8, 0($2)
	LBU	$9, 1($2)
	LBU	$10, 2($2)
	LBU	$11, 3($2)
	LBU	$12, 4($2)
	LBU	$13, 5($2)
	LBU	$14, 6($2)
	LBU	$15, 7($2)
        
        LW 	$16, 0($3)
        LW 	$17, 4($3)
        LW 	$18, 8($3)
        LW 	$19, 12($3)
        LW 	$20, 16($3)
        LW 	$21, 20($3)
        LW 	$22, 24($3)
        LW 	$23, 28($3)
	
        SUB 	$8,  $8 , $16
        SUB 	$9,  $9 , $17
        SUB 	$10, $10, $18
        SUB 	$11, $11, $19
        SUB 	$12, $12, $20
        SUB 	$13, $13, $21
        SUB 	$14, $14, $22
        SUB 	$15, $15, $23	

	OR	$8, $8, $9
	OR	$8, $8, $10
	OR	$8, $8, $11
	OR	$8, $8, $12
	OR	$8, $8, $13
	OR	$8, $8, $14
	OR	$8, $8, $15
	BNE	$8, $0, error
	
	JAL	show_pass

	#---------------------------------------------
	# Case=03	LH instruction	
	#---------------------------------------------
	JAL	show_case03
	JAL	show_init

	LA	$2, ds_load 
	LA	$3, result_lh

	JAL	flush_r8_r23
			
	LH	$8, 0($2)
	LH	$9, 1($2)
	LH	$10, 2($2)
	LH	$11, 3($2)
	LH	$12, 4($2)
	LH	$13, 5($2)
	LH	$14, 6($2)
	LH	$15, 7($2)
        
        LW 	$16, 0($3)
        LW 	$17, 4($3)
        LW 	$18, 8($3)
        LW 	$19, 12($3)
        LW 	$20, 16($3)
        LW 	$21, 20($3)
        LW 	$22, 24($3)
        LW 	$23, 28($3)
	
        SUB 	$8,  $8 , $16
        SUB 	$9,  $9 , $17
        SUB 	$10, $10, $18
        SUB 	$11, $11, $19
        SUB 	$12, $12, $20
        SUB 	$13, $13, $21
        SUB 	$14, $14, $22
        SUB 	$15, $15, $23	

	OR	$8, $8, $9
	OR	$8, $8, $10
	OR	$8, $8, $11
	OR	$8, $8, $12
	OR	$8, $8, $13
	OR	$8, $8, $14
	OR	$8, $8, $15
	BNE	$8, $0, error
	
	JAL	show_pass

	#---------------------------------------------
	# Case=04	LHU instruction	
	#---------------------------------------------
	JAL	show_case04
	JAL	show_init

	LA	$2, ds_load 
	LA	$3, result_lhu

	JAL	flush_r8_r23
			
	LHU	$8, 0($2)
	LHU	$9, 1($2)
	LHU	$10, 2($2)
	LHU	$11, 3($2)
	LHU	$12, 4($2)
	LHU	$13, 5($2)
	LHU	$14, 6($2)
	LHU	$15, 7($2)
        
        LW 	$16, 0($3)
        LW 	$17, 4($3)
        LW 	$18, 8($3)
        LW 	$19, 12($3)
        LW 	$20, 16($3)
        LW 	$21, 20($3)
        LW 	$22, 24($3)
        LW 	$23, 28($3)
	
        SUB 	$8,  $8 , $16
        SUB 	$9,  $9 , $17
        SUB 	$10, $10, $18
        SUB 	$11, $11, $19
        SUB 	$12, $12, $20
        SUB 	$13, $13, $21
        SUB 	$14, $14, $22
        SUB 	$15, $15, $23	

	OR	$8, $8, $9
	OR	$8, $8, $10
	OR	$8, $8, $11
	OR	$8, $8, $12
	OR	$8, $8, $13
	OR	$8, $8, $14
	OR	$8, $8, $15
	BNE	$8, $0, error
	
	JAL	show_pass

	#---------------------------------------------
	# Case=05	LW instruction	
	#---------------------------------------------
	JAL	show_case05
	JAL	show_init

	LA	$2, ds_load 
	LA	$3, result_lw

	JAL	flush_r8_r23
			
	LW	$8, 0($2)
	LW	$9, 1($2)
	LW	$10, 2($2)
	LW	$11, 3($2)
	LW	$12, 4($2)
	LW	$13, 5($2)
	LW	$14, 6($2)
	LW	$15, 7($2)
        
        LW 	$16, 0($3)
        LW 	$17, 4($3)
        LW 	$18, 8($3)
        LW 	$19, 12($3)
        LW 	$20, 16($3)
        LW 	$21, 20($3)
        LW 	$22, 24($3)
        LW 	$23, 28($3)
	
        SUB 	$8,  $8 , $16
        SUB 	$9,  $9 , $17
        SUB 	$10, $10, $18
        SUB 	$11, $11, $19
        SUB 	$12, $12, $20
        SUB 	$13, $13, $21
        SUB 	$14, $14, $22
        SUB 	$15, $15, $23	

	OR	$8, $8, $9
	OR	$8, $8, $10
	OR	$8, $8, $11
	OR	$8, $8, $12
	OR	$8, $8, $13
	OR	$8, $8, $14
	OR	$8, $8, $15
	BNE	$8, $0, error
	
	JAL	show_pass

	#---------------------------------------------
	# Case=05	LW instruction	
	#---------------------------------------------
	JAL	show_case05
	JAL	show_init

	LA	$2, ds_load 
	LA	$3, result_lw

	JAL	flush_r8_r23
			
	LW	$8, 0($2)
	LW	$9, 1($2)
	LW	$10, 2($2)
	LW	$11, 3($2)
	LW	$12, 4($2)
	LW	$13, 5($2)
	LW	$14, 6($2)
	LW	$15, 7($2)
        
        LW 	$16, 0($3)
        LW 	$17, 4($3)
        LW 	$18, 8($3)
        LW 	$19, 12($3)
        LW 	$20, 16($3)
        LW 	$21, 20($3)
        LW 	$22, 24($3)
        LW 	$23, 28($3)
	
        SUB 	$8,  $8 , $16
        SUB 	$9,  $9 , $17
        SUB 	$10, $10, $18
        SUB 	$11, $11, $19
        SUB 	$12, $12, $20
        SUB 	$13, $13, $21
        SUB 	$14, $14, $22
        SUB 	$15, $15, $23	

	OR	$8, $8, $9
	OR	$8, $8, $10
	OR	$8, $8, $11
	OR	$8, $8, $12
	OR	$8, $8, $13
	OR	$8, $8, $14
	OR	$8, $8, $15
	BNE	$8, $0, error
	
	JAL	show_pass

	#---------------------------------------------
	# Case=06	LWL instruction	
	#---------------------------------------------
	JAL	show_case06
	JAL	show_init

	LA	$2, ds_load 
	LA	$3, result_lwl

	JAL	flush_r8_r23
			
	LW	$8, 8($2)	# $8 = 0x11223344
	LW	$9, 12($2)	# $9 = 0xAABBCCDD
	MOVE	$10, $8		# $10 = 0x11223344
	MOVE	$11, $8		# $11 = 0x11223344
	MOVE	$12, $8		# $12 = 0x11223344
	MOVE	$13, $8		# $13 = 0x11223344
	
	LWL	$10, 12($2)	# $10 = 0xDD223344			
	LWL	$11, 13($2)     # $11 = 0xCCDD3344
	LWL	$12, 14($2)     # $12 = 0xBBCCDD44
	LWL	$13, 15($2)     # $13 = 0xAABBCCDD
        
        LW 	$16, 0($3)
        LW 	$17, 4($3)
        LW 	$18, 8($3)
        LW 	$19, 12($3)
        LW 	$20, 16($3)
        LW 	$21, 20($3)
	
        SUB 	$8,  $8 , $16
        SUB 	$9,  $9 , $17
        SUB 	$10, $10, $18
        SUB 	$11, $11, $19
        SUB 	$12, $12, $20
        SUB 	$13, $13, $21

	OR	$8, $8, $9
	OR	$8, $8, $10
	OR	$8, $8, $11
	OR	$8, $8, $12
	OR	$8, $8, $13
	BNE	$8, $0, error
	
	JAL	show_pass
	
	#---------------------------------------------
	# Case=07	LWR instruction	
	#---------------------------------------------
	JAL	show_case07
	JAL	show_init

	LA	$2, ds_load 
	LA	$3, result_lwr

	JAL	flush_r8_r23
			
	LW	$8, 8($2)	# $8 = 0x11223344
	LW	$9, 12($2)	# $9 = 0xAABBCCDD
	MOVE	$10, $8		# $10 = 0x11223344
	MOVE	$11, $8		# $11 = 0x11223344
	MOVE	$12, $8		# $12 = 0x11223344
	MOVE	$13, $8		# $13 = 0x11223344
	
	LWR	$10, 12($2)	# $10 = 0xDD223344			
	LWR	$11, 13($2)     # $11 = 0xCCDD3344
	LWR	$12, 14($2)     # $12 = 0xBBCCDD44
	LWR	$13, 15($2)     # $13 = 0xAABBCCDD
        
        LW 	$16, 0($3)
        LW 	$17, 4($3)
        LW 	$18, 8($3)
        LW 	$19, 12($3)
        LW 	$20, 16($3)
        LW 	$21, 20($3)
	
        SUB 	$8,  $8 , $16
        SUB 	$9,  $9 , $17
        SUB 	$10, $10, $18
        SUB 	$11, $11, $19
        SUB 	$12, $12, $20
        SUB 	$13, $13, $21

	OR	$8, $8, $9
	OR	$8, $8, $10
	OR	$8, $8, $11
	OR	$8, $8, $12
	OR	$8, $8, $13
	BNE	$8, $0, error
	
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
		
	
LOAD_str:
	.ascii	"LOAD"

ds_load:
	.word	0x04030201
	.word	0x88878685
	.word	0x11223344
	.word	0xAABBCCDD

result_lb:
	.word	0x00000001
	.word	0x00000002
	.word	0x00000003
	.word	0x00000004
	.word	0xFFFFFF85
	.word	0xFFFFFF86
	.word	0xFFFFFF87
	.word	0xFFFFFF88

result_lbu:
	.word	0x00000001
	.word	0x00000002
	.word	0x00000003
	.word	0x00000004
	.word	0x00000085
	.word	0x00000086
	.word	0x00000087
	.word	0x00000088 
	
result_lh:
	.word	0x00000201
	.word	0x00000201
	.word	0x00000403
	.word	0x00000403
	.word	0xFFFF8685
	.word	0xFFFF8685
	.word	0xFFFF8887
	.word	0xFFFF8887

result_lhu:		
	.word	0x00000201
	.word	0x00000201
	.word	0x00000403
	.word	0x00000403
	.word	0x00008685
	.word	0x00008685
	.word	0x00008887
	.word	0x00008887	

result_lw:
	.word	0x04030201
	.word	0x04030201
	.word	0x04030201
	.word	0x04030201
	.word	0x88878685
	.word	0x88878685
	.word	0x88878685
	.word	0x88878685

result_lwl:
	.word	0x11223344
	.word	0xAABBCCDD
	.word	0xDD223344			
	.word	0xCCDD3344
	.word	0xBBCCDD44
	.word	0xAABBCCDD

result_lwr:
	.word	0x11223344
	.word	0xAABBCCDD
	.word	0xAABBCCDD			
	.word	0x11AABBCC
	.word	0x1122AABB
	.word	0x112233AA
		
	       
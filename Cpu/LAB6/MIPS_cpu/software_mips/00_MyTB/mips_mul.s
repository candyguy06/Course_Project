	.text
	.globl	mul_check
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

mul_check:

	SUBU	$sp, $sp, 4		
	SW	$ra, 0($sp)
	
	LW	$t0, MUL_str
	LUI	$t1, 0x8000
	SW	$t0, 0($t1)
	
	JAL	show_new	
	
	#---------------------------------------------
	# Case=01	MUL instruction	
	#---------------------------------------------
	JAL	show_case01
	JAL	show_init

	#---- Round 1 ----
	JAL	flush_r8_r23
	
	LA	$2, data_round1 
	LA	$3, result_round1

	LW	$8, 8($2)
	LW	$9, 12($2)

	MUL	$10, $8, $9
	
	LW	$11, 0($3)
	
        SUB 	$8,  $10 , $11
	BNE	$8, $0, error

	#---- Round 2 ----
	
	
	#-----------------
	JAL	show_pass

	#---------------------------------------------
	# Case=02	MULT instruction	
	#---------------------------------------------
	JAL	show_case02
	JAL	show_init

	#---- Round 1 ----
	JAL	flush_r8_r23
	MTHI	$0
	MTLO	$0
		
	LA	$2, data_round1 
	LA	$3, result_round1

	LW	$8, 8($2)
	LW	$9, 12($2)

	MULT	$8, $9
	MFHI	$10
	MFLO	$11
	
	LW	$12, 4($3)
	LW	$13, 8($3)
	
	SUB	$10, $10, $12
	SUB	$11, $11, $13
	
	OR	$10, $10, $11
	BNE	$10, $0, error

	#---- Round 2 ----
	
	
	#-----------------
	JAL	show_pass

	#---------------------------------------------
	# Case=03	MULTU instruction	
	#---------------------------------------------
	JAL	show_case03
	JAL	show_init

	#---- Round 1 ----
	JAL	flush_r8_r23
	MTHI	$0
	MTLO	$0
		
	LA	$2, data_round1 
	LA	$3, result_round1

	LW	$8, 8($2)
	LW	$9, 12($2)

	MULTU	$8, $9
	MFHI	$10
	MFLO	$11
	
	LW	$12, 12($3)
	LW	$13, 16($3)
	
	SUB	$10, $10, $12
	SUB	$11, $11, $13
	
	OR	$10, $10, $11
	BNE	$10, $0, error

	#---- Round 2 ----
	
	
	#-----------------
	JAL	show_pass
	
	#---------------------------------------------
	# Case=04	MADD instruction	
	#---------------------------------------------
	JAL	show_case04
	JAL	show_init

	#---- Round 1 ----
	JAL	flush_r8_r23
	MTHI	$0
	MTLO	$0
		
	LA	$2, data_round1 
	LA	$3, result_round1

	LW	$8, 0($2)
	LW	$9, 4($2)
	LW	$10, 8($2)
	LW	$11, 12($2)
	
	MTHI	$8
	MTLO	$9
	
	MADD	$10, $11
	
	MFHI	$12
	MFLO	$13
	
	LW	$14, 20($3)
	LW	$15, 24($3)
	
	SUB	$12, $12, $14
	SUB	$13, $13, $15
	
	OR	$12, $12, $13
	BNE	$12, $0, error

	#---- Round 2 ----
	
	
	#-----------------
	JAL	show_pass
	
	#---------------------------------------------
	# Case=05	MADDU instruction	
	#---------------------------------------------
	JAL	show_case05
	JAL	show_init

	#---- Round 1 ----
	JAL	flush_r8_r23
	MTHI	$0
	MTLO	$0
		
	LA	$2, data_round1 
	LA	$3, result_round1

	LW	$8, 0($2)
	LW	$9, 4($2)
	LW	$10, 8($2)
	LW	$11, 12($2)
	
	MTHI	$8
	MTLO	$9
	
	MADDU	$10, $11
	
	MFHI	$12
	MFLO	$13
	
	LW	$14, 28($3)
	LW	$15, 32($3)
	
	SUB	$12, $12, $14
	SUB	$13, $13, $15
	
	OR	$12, $12, $13
	BNE	$12, $0, error

	#---- Round 2 ----
	
	
	#-----------------
	JAL	show_pass

	#---------------------------------------------
	# Case=06	MSUB instruction	
	#---------------------------------------------
	JAL	show_case06
	JAL	show_init

	#---- Round 1 ----
	JAL	flush_r8_r23
	MTHI	$0
	MTLO	$0
		
	LA	$2, data_round1 
	LA	$3, result_round1

	LW	$8, 0($2)
	LW	$9, 4($2)
	LW	$10, 8($2)
	LW	$11, 12($2)
	
	MTHI	$8
	MTLO	$9
	
	MSUB	$10, $11
	
	MFHI	$12
	MFLO	$13
	
	LW	$14, 36($3)
	LW	$15, 40($3)
	
	SUB	$12, $12, $14
	SUB	$13, $13, $15
	
	OR	$12, $12, $13
	BNE	$12, $0, error

	#---- Round 2 ----
	
	
	#-----------------
	JAL	show_pass
	
	#---------------------------------------------
	# Case=07	MSUBU instruction	
	#---------------------------------------------
	JAL	show_case07
	JAL	show_init

	#---- Round 1 ----
	JAL	flush_r8_r23
	MTHI	$0
	MTLO	$0
		
	LA	$2, data_round1 
	LA	$3, result_round1

	LW	$8, 0($2)
	LW	$9, 4($2)
	LW	$10, 8($2)
	LW	$11, 12($2)
	
	MTHI	$8
	MTLO	$9
	
	MSUBU	$10, $11
	
	MFHI	$12
	MFLO	$13
	
	LW	$14, 44($3)
	LW	$15, 48($3)
	
	SUB	$12, $12, $14
	SUB	$13, $13, $15
	
	OR	$12, $12, $13
	BNE	$12, $0, error

	#---- Round 2 ----
	
	
	#-----------------
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
		
	
MUL_str:
	.ascii	"MUL "


data_round1:
	.word	0x616F4433      # 00 HI
	.word	0xC0AC9AA4      # 04 LO
	.word	0xB3596E49      # 08 rs
 	.word	0xEDB2AABB      # 12 rt
  
result_round1:  
	.word	0xA9520953 	# 00 [MUL]   rd  
	.word	0x057ADDE0 	# 04 [MULT]  HI  
	.word	0xA9520953 	# 08         LO  
	.word	0xA686F6E4 	# 12 [MULTU] HI  
	.word	0xA9520953 	# 16         LO  
	.word	0x66EA2214 	# 20 [MADD]  HI  
	.word	0x69FEA3F7 	# 24         LO  
	.word	0x07F63B18 	# 28 [MADDU] HI  
	.word	0x69FEA3F7 	# 32         LO  
	.word	0x5BF46653 	# 36 [MSUB]  HI  
	.word	0x175A9151 	# 40         LO  
	.word	0xBAE84D4F 	# 44 [MSUBU] HI  
	.word	0x175A9151 	# 48         LO  
          
        












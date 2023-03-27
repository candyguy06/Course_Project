	.text
	LUI	$2, 0x0000
	ORI	$2, $2, 0x0100
	
	#R2=0x00000100
	
	LW	$3,0($2)
	
	B	0xFFFFFFFC


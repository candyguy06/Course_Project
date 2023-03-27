move $8,$0		  	
move $9,$0 		  	
move $10,$0 		  	
addi $10,$10,10	  	

loop:
bgt $8,$10,Exit		
addi $8,$8,1
add $9,$9,$8
j loop	

Exit:


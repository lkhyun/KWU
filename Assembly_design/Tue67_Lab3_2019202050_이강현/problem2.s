	AREA ARMex, CODE, READONLY
		ENTRY	

start
	LDR r0, addr
	LDR r1, =array
	LDR r2,[r1],#36 ; access last number
	
Loop
	LDR r2,[r1],#-4 ;access backward order
	STRB r2,[r0],#1 ;access memory 1byte 
	CMP r2,#10
	BEQ endloop
	B Loop
endloop
	MOV pc,lr
	
array DCD 10,9,8,7,6,5,4,3,2,1
addr & &4000
	END
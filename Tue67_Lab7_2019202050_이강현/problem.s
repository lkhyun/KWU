	AREA ARMex,CODE,READONLY
		ENTRY
start
	ADR r0, String
	LDR r1, tempaddr	;load address
	
Loop
	LDRB r2,[r0],#1	 ;load data with binary type and r0 + 1
	CMP r2,#0
	BEQ Endline ; move endline
	STRB r2,[r1],#1 ;store r2 to r1 and r1 + 1
	BNE Loop ;move loop

Endline
	MOV pc,lr			

String DCB "apple tree",0
tempaddr DCD &40000
	END
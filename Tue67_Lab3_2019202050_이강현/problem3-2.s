	AREA ARMex, CODE, READONLY
		ENTRY
start
	LDR r0,addr
	MOV r1,#1 ;r1 = 1
	MOV r2,r1,LSL #1 ;r2 = 2
	MOV r2,r2,LSL #1 ;r2 = 4
	ADD r2,r2,#1 ;r2 = 5
	MOV r2,r2,LSL #1 ;r2 = 10
	ADD r3,r2,r2 ;r3 = 20
	MUL r4,r3,r2 ; r4 = r3*r2
	STR r4,[r0]
	MOV pc,lr
	
addr & &4000

	END
	
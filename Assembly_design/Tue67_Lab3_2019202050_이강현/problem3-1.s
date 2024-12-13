	AREA ARMex, CODE, READONLY
		ENTRY
start
	LDR r0,addr
	MOV r1,#1 ;r1 = 1
	MOV r2,r1,LSL #1 ;r2 = 2
	MOV r2,r2,LSL #1 ;r2 = 4
	ADD r2,r2,#1 ;r2 = 5
	ADD r2,r1,r2,LSL #1 ;r2 = 11
	ADD r1,r1,#1 ; r1 = 2
	MOV r4,r2 ; r4 = sum
	
loop
	ADD r3,r2,r1 
	ADD r4,r4,r3
	ADD r1,r1,#2
	CMP r3,#29 ; find last number
	BEQ endloop
	B loop
endloop
	STR r4,[r0]
	MOV pc,lr

addr & &4000

	END
	


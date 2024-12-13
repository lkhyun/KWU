	AREA ARMex, CODE, READONLY
		ENTRY

start
	LDR r0, addr ;load memory for accessing
	LDR r1, =array ;load array to r1

	LDR r2,[r1],#4 ;load the data to r3 from Array
	ADD r3,r3,r2 
	LDR r2,[r1],#4 
	ADD r3,r3,r2 
	LDR r2,[r1],#4 
	ADD r3,r3,r2 
	LDR r2,[r1],#4 
	ADD r3,r3,r2 
	LDR r2,[r1],#4 
	ADD r3,r3,r2
	LDR r2,[r1],#4 
	ADD r3,r3,r2
	LDR r2,[r1],#4 
	ADD r3,r3,r2 
	LDR r2,[r1],#4 
	ADD r3,r3,r2 
	LDR r2,[r1],#4 
	ADD r3,r3,r2 
	LDR r2,[r1],#4 
	ADD r3,r3,r2 
	STR r3,[r0]
	
	MOV pc, lr

array DCD 11,13,15,17,19,21,23,25,27,29
addr & &4000
	END
	AREA ARMex, CODE, READONLY
	ENTRY
start
	ldr r0,tempaddr
	mov r1, #10       ;r1 = 10
	mov r2, #2        ;r2 = 2
	mul r3,r2,r1      ;r3 = 10*2
	add r2,r2,#1      ;r2 = 3
	mul r4,r3,r2      ;r4 = 10*3*2
	add r2,r2,#1      ;r2 = 4
	mul r5,r4,r2      ;r5 = 10*4*3*2
	add r2,r2,#1      ;r2 = 5
	mul r6,r5,r2      ;r6 = 10*5*4*3*2
	add r2,r2,#1      ;r2 = 6
	mul r7,r6,r2      ;r7 = 10*6*5*4*3*2
	add r2,r2,#1      ;r2 = 7
	mul r8,r7,r2      ;r8 = 10*7*6*5*4*3*2
	add r2,r2,#1      ;r2 = 8
	mul r9,r8,r2      ;r9 = 10*8*7*6*5*4*3*2
	add r2,r2,#1      ;r2 = 9
	mul r10,r9,r2     ;r10 =10*9*8*7*6*5*4*3*2
	
	str r10,[r0]
	mov pc,lr
	
tempaddr & &40000
	end
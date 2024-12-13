	AREA ARMex, CODE, READONLY
	ENTRY
start
	ldr r0, tempaddr
	mov r1,#10                 ;r1 = 10
	add r2,r1,r1,lsl #3        ;r2 = 10*9
	add r3,r2,lsl #3           ;r3 = 10*9*8
	rsb r4,r3,r3,lsl #3        ;r4 = 10*9*8*7
	add r4,r4,lsl #1           ;r4 =10*9*8*7*2
	add r5,r4,lsl #1           ;r5 = 10*9*8*7*6
	add r6,r5,r5,lsl #2        ;r6 = 10*9*8*7*6*5
	add r7,r6,lsl #2           ;r7 = 10*9*8*7*6*5*4
	add r8,r7,r7,lsl #1        ;r8 = 10*9*8*7*6*5*4*3
	add r9,r8,lsl #1           ;r9 = 10*9*8*7*6*5*4*3*2
	str r9,[r0]
	
	mov pc,lr
	
tempaddr & &40000
	end
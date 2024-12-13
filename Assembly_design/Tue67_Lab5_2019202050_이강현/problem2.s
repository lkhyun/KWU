	AREA problem2,CODE,READONLY
		ENTRY
start
	LDR sp,tempaddr
	MOV r0,#0
	MOV r1,#1
	MOV r2,#2
	MOV r3,#3
	MOV r4,#4
	MOV r5,#5
	MOV r6,#6
	MOV r7,#7
	
	STR r2,[sp],#4
	STR r0,[sp],#4
	STR r3,[sp],#4
	STMIA sp!,{r5-r7} ;block data transfer
	STR r1,[sp],#4
	STR r4,[sp]
	LDMFA sp,{r0-r7} ;block data transfer
	MOV pc,#0

tempaddr DCD &40000
	END
	
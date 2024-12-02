	AREA	ARMex, CODE, READONLY
		ENTRY
start

	MOV r0,#1
	MOV r1,#2
	MOV r2,#3
	MOV r3,#4
	LDR r4,number
	;initializing
	
number & &1000 ;address setting
	
	STRB r0,[r4]
	STRB r1,[r4,#1]
	STRB r2,[r4,#2]
	STRB r3,[r4,#3]
	;1byte store with offset
	
	LDR r5,[r4] ;4byte load
	
	STRB r0,[r4,#3]
	STRB r1,[r4,#2]
	STRB r2,[r4,#1]
	STRB r3,[r4]
	
	LDR r6,[r4]
	END

	
	
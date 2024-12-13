	AREA problem1,CODE,READONLY
		ENTRY
start
	LDR sp,tempaddr ;stack pointer
	MOV r1, #1 ;mul
	MOV r2, #1 ;result
	B factorial ;move factorial function
	
factorial
	ADD r1,r1,#1 
	MUL r2,r1,r2
	CMP r1,#10 
	BEQ Endline ;if r2 == 10!
	BNE factorial ;else loop
	
Endline
	STMIA sp, {r2} ;multiple store to sp
	MOV pc,#0
	
tempaddr DCD &00040000
	
	END
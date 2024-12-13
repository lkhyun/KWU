	AREA problem3, CODE, READONLY
		ENTRY
start
	LDR sp, tempaddr1
	MOV r9, #160
	MOV r0,#10
	MOV r1,#11
	MOV r2,#12
	MOV r3,#13
	MOV r4,#14
	MOV r5,#15
	MOV r6,#16
	MOV r7,#17
	BL	doRegister ;branch with link
	B	doGCD	   ;branch
	
doRegister
	STMFA sp,{r0-r7} ;copy register data
	ADD r0,r0,#0
	ADD r1,r1,#1
	ADD r2,r2,#2
	ADD r3,r3,#3
	ADD r4,r4,#4
	ADD r5,r5,#5
	ADD r6,r6,#6
	ADD r7,r7,#7 ;register = register + index
	
	ADD r8,r8,r0
	ADD r8,r8,r1
	ADD r8,r8,r2
	ADD r8,r8,r3
	ADD r8,r8,r4
	ADD r8,r8,r5
	ADD r8,r8,r6
	ADD r8,r8,r7 ;r8: register's sum
	MOV pc,lr; end subroutine

doGCD
	CMP r8,r9
	SUBGT r8,r8,r9 ;if r8>r9,r8=r8-r9
	SUBLT r9,r9,r8 ;if r8<r9,r9=r9-r8
	
	BNE doGCD ; not equal? loop
	BEQ Endline ; equal? go endline
Endline
	LDMED sp,{r0-r7}
	ADD r8,r8,r4
	STR r8,[sp] ; save
	MOV r8,#0
	MOV pc,#0 ;program end

tempaddr1 & &40000

	END
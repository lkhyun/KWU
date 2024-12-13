	AREA ARMex, CODE, READONLY
		ENTRY	

start
	LDR r0,Address0 ;load memory Address0
	MOV r1, #10 ;same
	MOV r2, #11 ;different
	LDR r5, =arr1 ; load arr1 address into r5
	LDR r6, =arr2 ; load arr2 address into r6
	
Loop
	LDRB r3,[r5], #1 
	LDRB r4,[r6], #1
	CMP r3,r4
	BNE notequal ;arr1 != arr2, go to notequal
	BEQ equal ; arr1 == arr2, go to equal

notequal
	STR r2, [r0] ; store 11
	B Endline ;end loop

equal
	CMP r3,#0 ; checking end of word
	BEQ Endline ; and loop
	STR r1, [r0] ; store 10
	B Loop ; loop

Endline
	MOV pc,lr
	
Address0 & &4000
arr1 DCB "apple_pie",0 ;save word in arr1
arr2 DCB "apple_tree",0 ;save word in arr1

	END
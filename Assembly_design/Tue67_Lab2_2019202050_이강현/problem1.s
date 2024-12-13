	AREA	ARMex, CODE, READONLY
		ENTRY
start
		LDR 	r4, TEMPADDR1 ;address allocation
		MOV		r6, #7 			
		STRB	r6,[r4] ;1 byte store
		MOV		r7, #10
		STRB	r7,[r4,#1]
		MOV		r8, #17
		STRB	r8,[r4,#2]
		
		
TEMPADDR1 & &1000 ;address setting

		LDRB	r0, [r4] ;1 byte load
		LDRB	r1, [r4,#1] ; r4 is not change, r1= r4+1
		LDRB	r2, [r4,#2]
		CMP 	r0, #10 ;compare r0,#10
		MOVGT 	r5, #1 ;Z clear and N and V the same
		MOVMI	r5, #2 ;N set
		MOVEQ 	r5, #3 ;Z set
		
		CMP 	r1, #10
		MOVGT 	r5, #1
		MOVMI	r5, #2
		MOVEQ 	r5, #3
		
		CMP 	r2, #10
		MOVGT 	r5, #1
		MOVMI	r5, #2
		MOVEQ 	r5, #3
		
		END   			;mark end of line
	AREA problem1,CODE,READONLY
		ENTRY
start
	LDR r0, =array1 ; address load
	LDR r1, =array2 ; address load
	
	LDR r2,[r0] ; load 0x3FC00000
	LDR r3,[r1] ; load 0x40500000
	LDR r12,tempaddr
	
	MOV r4,r2,LSR #31; to store signbit
	MOV r5,r3,LSR #31
	
	MOV r6,r2,LSR #23; to store exponent
	MOV r7,r3,LSR #23
	MOV r6,r6,LSL #24 
	MOV r7,r7,LSL #24 
	MOV r6,r6,LSR #1
 	MOV r7,r7,LSR #1 ; to only store exponent not signbit
	
	MOV r8,r2,LSL #9 ; to store mantissa
	MOV r9,r3,LSL #9
	MOV r8,r8,LSR #1
	MOV r9,r9,LSR #1 ; to add 1
	
	ADD r8,r8,#0x80000000 ; add 1
	ADD r9,r9,#0x80000000
	
	CMP r6,r7; exponent compare
	
	SUBGT r10,r6,r7
	SUBLT r10,r7,r6
	MOVEQ r10,#0
	
	MOV r10,r10, LSR #23 ; r10 is shiftnum
	
	MOVGT r9,r9,LSR r10 ; exponent matching
	MOVLT r8,r8,LSR r10
	
	MOVLT r6,r7 ; large exponent is standard
	
	CMP r4,r5
	
	BEQ equal ;sign bit equal
	BNE notequal ;sign bit notequal
	
equal
	ADDS r11,r8,r9
	ADDCS r6,r6,#0x00800000 ; if carry is 1, right shift need
	MOVCS r11,r11,LSR #1
	
	MOV r11,r11,LSL #1 ; mantissa is 23bit 24th bit should be cleared
	MOV r11,r11,LSR #9 ; bit position adjustment
	
	B endline

notequal
	CMP r8,r9
	
	BEQ equalvalue
	
	SUBGT r11,r8,r9
	SUBLT r11,r9,r8
	
	MOVLT r4,r5 ; large mantissa' absolute value is standard
	B normalization
	
normalization ; bit position align
	CMP r11,#0x01000000 ; mantissa shift right
	
	ADDCS r6,r6,#0x00800000
	MOVCS r11,r11,LSR #1
	BCS normalization 
	
	CMP r11,#0x00800000 ;mantissa shift left
	
	SUBLS r6,r6,#0x00800000
	MOVLS r11,r11,LSL #1
	BLS normalization
	B endline
	
equalvalue
	MOV r11,#0
	STR r11,[r12]
	MOV pc,lr
	
endline
	MOV r4,r4,LSL #31
	ADD r11,r11,r4
	ADD r11,r11,r6
	
	STR r11, [r12]
	
	MOV pc,lr
array1 & 0x40C00000 ; 00111111 11000000 00000000 00000000 : 1.1 * 2^0
array2 & 0x40800000 ; 01000000 01010000 00000000 00000000 : 1.101 * 2^1
tempaddr & &40000

	END
.global main
main:
	PUSH {LR}
	PUSH {R4-R12}

line_1:
line_10:
line_20:
line_30:
line_40:
MOV R4, # 7
line_50:
MOV R5, # 6
line_60:
MUL R6, R4, R5
line_61:
MOV R7, # 42
line_70:
	CMP R6, R11
	BEQ line_100
	BNE line_0
line_80:
	LDR R0, =label
	BL print_string
line_81:
	MOV R0, R6
	BL print_number
line_90:
line_100:
	LDR R0, =label
	BL print_string
line_101:
	MOV R0, R6
	BL print_number
line_110:

quit:
	MOV R0, #42
	POP {R4-R12}
	POP {PC}
.data

label:  .asciz "YOUR CODE WORKED SUCCESSFULLY, 7*6 = " 
label:  .asciz "YOUR CODE IS BUGGY. YOU THINK 7*6 = " 

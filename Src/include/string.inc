%ifndef _STRING_INC_
%define _STRING_INC_


;------------------------
CMPSTR:
	PUSH AX
	PUSH CX
	PUSH DI
	PUSH SI

CMPSTR_BEGIN:
	XOR CX, CX			; CX=0

	CMPSTR_FOR:

		LODSB			; AL=[SI] INC SI
		MOV AH, [DI]
		CMP AL, AH
		JNE CMPSTR_Error	; IF AL!=[DI] ERROR

		INC CX			; CX++
		INC DI			; DI++
		CMP CX, 13
		JNE CMPSTR_FOR		; IF CX!=13 CMPSTR_BEGIN

	CMPSTR_FOREND:

	XOR CX, CX
	INC CX		; unset zero flag
	JMP CMPSTR_END

CMPSTR_Error:
	XOR CX, CX	; set zero flag

CMPSTR_END:
	POP SI
	POP DI
	POP CX
	POP AX
	RET
;------------------------


%endif

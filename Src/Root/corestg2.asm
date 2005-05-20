
ORG 0x00080A00

BEGIN:
JMP BEGIN


MSG_TEST:	DB 'Test, test',0


%define _USE_PRINT_
%define _USE_SHOWHEX_
%include	"display.inc"

%include	"globals.inc"

%include	"input.inc"
%include	"cmos.inc"

%include	"mem.inc"



StartCore:


MOV ESI, MSG_TEST
CALL PRINTLN


END:
JMP LONG END
















;-------------------
INSTALL_IPKEY:
	PUSH AX
	PUSH DX
	PUSH DS
	MOV AX, DS
	XOR DX, DX
	MOV DS, DX
	MOV DX, 0x09
		SHL DX, 1
		SHL DX, 1

	MOV SI, DX
	MOV DI, OLDINT1
	LODSW
	STOSW

	LODSW
	STOSW

	MOV AX, ES
	MOV DI, OLDINT2
	STOSW

	MOV AX, INTERPKEY
	STOSW	


	MOV DI, DX
	MOV AX, ES
	CLI
	STOSW
	MOV AX, INTERPKEY
	CLI
	STOSW
	STI
	POP DS
	POP DX
	POP AX
	RET


INTERPKEY:
	JNZ EXITIT
	CALL SHOWHEX
	MOV AL, AH
	CALL SHOWHEX
EXITIT:
	IRET
;-------------------





;-------------------
OLDINT1:	DB 0,0,0,0
OLDINT2:	DB 0,0,0,0
OLDINT3:	DB 0,0,0,0
OLDINT4:	DB 0,0,0,0
;-------------------



;-------------------
times 1024-($-$$)	DB 0

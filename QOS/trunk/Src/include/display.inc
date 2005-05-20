%ifndef _DISPLAY_INC_
%define _DISPLAY_INC_




%ifdef _USE_PRINT_

;-------------------
PRINT_BGCOLOR:		db 0xFF

PRINTLN_CRLF:		db 13,10,0
;-------------------


;-------------------
PRINTCHAR:
	PUSH AX
	PUSH BX

PRINTCHAR_BEGIN:

	MOV AH, 0x0E
	XOR BX, BX
	MOV BL, [PRINT_BGCOLOR]
	INT 0x10

PRINTCHAR_END:
	POP BX
	POP AX
	RET
;-------------------


;-------------------
PRINT:
	PUSH AX
	PUSH BX

PRINT_BEGIN:
	MOV AH, 0x0E
	XOR BX, BX
	MOV BL, [PRINT_BGCOLOR]

PRINT_FOR:
	LODSB
	OR AL, AL
	JZ PRINT_END

PRINT_CHAR:
	INT 0x10
	JMP PRINT_FOR

PRINT_END:
	POP BX
	POP AX
	RET
;-------------------


;-------------------
PRINTLN:
	PUSH SI

PRINTLN_BEGIN:
	CALL PRINT

	MOV SI,PRINTLN_CRLF
	CALL PRINT

PRINTLN_END:
	POP SI
	RET
;-------------------

;-------------------
PRINTCRLF:
	PUSH SI

PRINTCRLF_BEGIN:

	MOV SI,PRINTLN_CRLF
	CALL PRINT

PRINTCRLF_END:
	POP SI
	RET
;-------------------


;-------------------
CLS:
	PUSH AX

CLS_BEGIN:
	MOV AX, 0x0F00
	INT 0x10		; Get current videomode --> AL=MODE
	MOV AH, 0x00
	INT 0x10		; Set current videomode to AL

CLS_END:
	POP AX
	RET
;-------------------

%endif


%ifdef _USE_SHOWHEX_

;-------------------
SHOWHEX_HEXTBL:		DB '0123456789ABCDEF****'
;-------------------


;-------------------
SHOWHEX:
	PUSH AX
	PUSH BX
	PUSH DX

SHOWHEX_BEGIN:
	MOV DX, AX

SHOWHEX_HEXC1:
	XOR AX, AX
	MOV AL, DL
	AND AL, 11110000b
	SHR AX, 1
	SHR AX, 1
	SHR AX, 1
	SHR AX, 1
	MOV BX, SHOWHEX_HEXTBL
	ADD BX, AX
	MOV AL, [BX]

	MOV AH, 0x0E
	XOR BX, BX
	MOV BL, [PRINT_BGCOLOR]

	INT 0x10

SHOWHEX_HEXC2:
	XOR AX, AX
	MOV AL, DL
	AND AL, 00001111b
	MOV BX, SHOWHEX_HEXTBL
	ADD BX, AX
	MOV AL, [BX]

	MOV AH, 0x0E
	XOR BX, BX
	MOV BL, [PRINT_BGCOLOR]

	INT 0x10

SHOWHEX_END:
	POP DX
	POP BX
	POP AX
	RET
;-------------------

;-------------------
SHOWHEX_WORD:

SHOWHEX_WORD_BEGIN:

	XCHG AL, AH
	CALL SHOWHEX
	XCHG AL, AH
	CALL SHOWHEX

SHOWHEX_WORD_END:
	RET
;-------------------

%endif


%endif

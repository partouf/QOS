
%ifndef _MEM_INC_
%define _MEM_INC_
;---------------------------------


; EAX    = 32bits address
; @PM -> returns ES:ESI
;---------------------------------
MEMADDR_32BIT_TO_SRC:
	PUSH EAX
	PUSH ECX

MEMADDR_32BIT_TO_SRC_BEGIN:

	MOV ECX, CR0
	AND ECX, 1
	JZ MEMADDR_32BIT_TO_SRC_RM


MEMADDR_32BIT_TO_SRC_PM:
	JMP MEMADDR_32BIT_TO_SRC_END


MEMADDR_32BIT_TO_SRC_RM:
	CALL MEMADDR_32BIT_TO_RMSRC


MEMADDR_32BIT_TO_SRC_END:
	POP ECX
	POP EAX
	RET
;---------------------------------



; EAX    = 32bits address
; @RM -> returns ES:SI
;  or
; @PM -> returns ES:ESI
;---------------------------------
MEMADDR_32BIT_TO_DEST:
	PUSH EAX
	PUSH ECX
	PUSH ESI
	PUSH ES

MEMADDR_32BIT_TO_DEST_BEGIN:

	MOV ECX, CR0
	AND ECX, 1
	JZ MEMADDR_32BIT_TO_DEST_RM


MEMADDR_32BIT_TO_DEST_PM:
	JMP MEMADDR_32BIT_TO_DEST_END


MEMADDR_32BIT_TO_DEST_RM:
	CALL MEMADDR_32BIT_TO_RMSRC

	PUSH ESI
	POP EDI

	PUSH ES
	POP DS


MEMADDR_32BIT_TO_DEST_END:
	POP ES
	POP ESI
	POP ECX
	POP EAX
	RET
;---------------------------------



;---------------------------------
MEMADDR_32BIT_TO_RMSRC:
	PUSH EAX
	PUSH ECX

MEMADDR_32BIT_TO_RMSRC_BEGIN:

	MOV ECX, EAX
	AND EAX, 0x000F0000
	SHR EAX, 4

	MOV ES, AX

	AND ECX, 0x0000FFFF
	MOV ESI, ECX

MEMADDR_32BIT_TO_RMSRC_END:
	POP ECX
	POP EAX
	RET
;---------------------------------



;---------------------------------
%endif

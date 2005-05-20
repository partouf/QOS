
%ifndef _A20_INC_
%define _A20_INC_


;-------------------------------
SET_A20LINE:
	PUSH AX
	PUSH CX

SET_A20LINE_BEGIN:

	CLI
	XOR CX, CX


	CALL KEYB_CLEAR_BUFFER


	MOV AL, 0x00D1
	OUT 0x64, AL


	CALL KEYB_CLEAR_BUFFER


	MOV AL, 0x00DF
	OUT 0x60, AL


	CALL KEYB_WAIT


SET_A20LINE_END:
	POP CX
	POP AX

	RET
;-------------------------------



;-------------------------------
KEYB_CLEAR_BUFFER:
	PUSH AX

KEYB_CLEAR_BUFFER_BEGIN:

	IN AL, 0x64
	TEST AL, 0x02
	LOOPNZ KEYB_CLEAR_BUFFER_BEGIN

KEYB_CLEAR_BUFFER_END:
	POP AX
	RET
;-------------------------------


;-------------------------------
KEYB_WAIT:
	PUSH AX
	PUSH CX

	MOV CX, 0x14

KEYB_WAIT_BEGIN:

	OUT 0x00ED, AX
	LOOP KEYB_WAIT_BEGIN

KEYB_WAIT_END:
	POP CX
	POP AX
	RET
;-------------------------------




%endif

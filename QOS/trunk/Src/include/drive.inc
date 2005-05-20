
%ifndef _DRIVE_INC_
%define _DRIVE_INC_



;------------------------
; LOAD_SECTOR()
;
; DL = Drive
; DH = Head
; CH = Cylinder
; CL = Sector
; AL = Number of Sectors
; DS:DI = Destination buffer
;
; retries 3 times
;------------------------
ATTEMPTS:	DB 3

LOAD_SECTOR:
	PUSH AX
	PUSH CX
	PUSH DX
	PUSH BX
	PUSH ES

LOAD_SECTOR_BEGIN:

	MOV [ATTEMPTS], BYTE 3

	PUSH AX

LOAD_SECTOR_ATTEMPT:
	POP AX
	PUSH AX

	CALL RESET_DRIVE

	PUSH DS
	POP ES
	MOV BX, DI

	MOV AH, 0x02
	INT 0x13


	DEC BYTE [ATTEMPTS]
	JZ LOAD_SECTOR_END

	JC LOAD_SECTOR_ATTEMPT

LOAD_SECTOR_END:
	POP AX

	POP ES
	POP BX
	POP DX
	POP CX
	POP AX
	RET
;------------------------



;------------------------
; RESET_DRIVE()
;
; DL = Drive
;------------------------
RESET_DRIVE:
	PUSH AX

RESET_DRIVE_BEGIN:

	XOR AX, AX
	INT 0x13	; reset disk

	; AH = status
	; CF set on error

RESET_DRIVE_END:
	POP AX
	RET
;------------------------



%endif

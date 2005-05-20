

%ifndef _COREGDT_INC_
%define _COREGDT_INC_

;-------------------------------
_GDT_ENTRIES:		equ 4
_GDT_STAT_SEGM_SIZE:	equ 0xFFFF

;-------------------------------

GDT_STATIC:

GDT_SIZE:	DW (_GDT_ENTRIES * 8 - 1)
GDT_PTR:	DW 0x0C00
		DW 0x0000
;-------------------------------


;--------------------------------------------------------------
;| 0..0x0600..0x80000        | 0x80000 - 0x090000 |  rest->>
;--------------------------------------------------------------


GDT_STATIC_TABLE:

; GDT 0
	DW 0x0000
	DW 0x0000
	DB 0
	DB 0
	DB 0
	DB 0

; GDT 1
; kernel and bios space, etc
; System - 32bit call gate
	DW 0xFFFF	; limit -> bit 0..15
	DW 0x0000	; base -> bit 0..15
	DB 0		; base -> bit 16..23
	DB 10011000b	; P(1), DPL(2), S(1), Type(4)
	DB 11001111b	; G(1), D/B(1), 0(1), AVL(1), limit bit 16..19
	DB 0		; base -> bit 24..31

;	dd	0x0000ffff
;	dd	0x00cf9a00

; GDT 2
; Stack Segment (R/W Data Segment Expand down)
	DW 0xFFFF	; limit -> bit 0..15
	DW 0x0000	; base -> bit 0..15
	DB 0x09		; base -> bit 16..23
	DB 10010110b	; P(1), DPL(2), S(1), Type(4)
	DB 00000000b	; G(1), D/B(1), 0(1), AVL(1), limit bit 16..19
	DB 0		; base -> bit 24..31

; GDT 3
; Flat mem 0x90000 and beyond
	DW 0xFFFF	; limit -> bit 0..15
	DW 0x0000	; base -> bit 0..15
	DB 0x09		; base -> bit 16..23
	DB 11110000b	; P(1), DPL(2), S(1), Type(4)
	DB 11001111b	; G(1), D/B(1), 0(1), AVL(1), limit bit 16..19
	DB 0		; base -> bit 24..31



;-------------------------------
GDT_INITIALISE:
	PUSH AX
	PUSH CX
	PUSH DX
	PUSH BX
	PUSH DI
	PUSH DS

GDT_INITIALISE_BEGIN:

	MOV CX, GDT_SIZE

	MOV AX, WORD [GDT_PTR+2]
	MOV DS, AX
	MOV DI, WORD [GDT_PTR]

	MOV SI, GDT_STATIC_TABLE


	GDT_COPY_TABLE:
	LODSB
	STOSB
	
	DEC CX
	JNZ GDT_COPY_TABLE

	
GDT_INITIALISE_END:
	POP DS
	POP DI
	POP BX
	POP DX
	POP CX
	POP AX
	RET
;-------------------------------



;-------------------------------
GDT_INITIALISE2:
	PUSH AX
	PUSH CX
	PUSH DX
	PUSH BX
	PUSH DI
	PUSH DS

GDT_INITIALISE2_BEGIN:

	MOV AX, WORD [GDT_PTR]
	MOV DS, AX
	MOV DI, WORD [GDT_PTR+2]

	XOR DX, DX
	XOR BX, BX
	MOV CX, _GDT_ENTRIES

	; GDT 0
	XOR AX, AX
	STOSW
	STOSW
	STOSB
	STOSB
	STOSB
	STOSB


	GDT_INITIALISE_FOR:
		; Segment size
		MOV AX, _GDT_STAT_SEGM_SIZE
		STOSW

		; Base address byte 0 and 1
		MOV AX, DX
		STOSW

		; Base address byte 2
		MOV AL, BL
		STOSB

		; Other stuff
		MOV AL, 0x92
		STOSB

		MoV AL, 0xCF
		STOSB


		; Base address byte 3
		MOV AL, BH
		STOSB


		; end loop on 0
		DEC CX
		JZ GDT_INITIALISE_FOR_END

		; dx += size
		ADD DX, _GDT_STAT_SEGM_SIZE
		INC DX
		JO GDT_INITIALIZE_ADDBASE	; if overflow

		; loop
		JMP GDT_INITIALISE_FOR


		GDT_INITIALIZE_ADDBASE:
		TEST DX, DX		; abs(DX)
		INC BX			; BX++
		; loop
		JMP GDT_INITIALISE_FOR	

	GDT_INITIALISE_FOR_END:


	
GDT_INITIALISE2_END:
	POP DS
	POP DI
	POP BX
	POP DX
	POP CX
	POP AX
	RET
;-------------------------------




;-------------------------------


%endif

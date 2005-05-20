
ORG 0x0600

BEGIN:
JMP StartCore

;---------------------------------
KERNID:		DB 'QCore v0.1',0

CPU_HURAY:	DB 'Huray! 386 gevonden',0
CPU_ERROR:	DB 'Ey! Dit is geen 386!',0

A20MSG:		DB 'Setting A20 line...',0


%define _USE_PRINT_
%define _USE_SHOWHEX_
%include	"display.inc"

%include	"globals.inc"

%include	"cmos.inc"

%include	"coregdt.inc"

%include	"A20.inc"

%include	"mem.inc"

;---------------------------------


StartCore:


	;-------------------------------
;	CALL CLS

	MOV SI,KERNID
	CALL PRINTLN
	;-------------------------------


	;-------------------------------
	; BaseMem low order byte
	MOV AL, 0x15
	CALL CMOS_READBYTE
;	CALL SHOWHEX

	; BaseMem high order byte
	MOV AL, 0x16
	CALL CMOS_READBYTE
;	CALL SHOWHEX

;	CALL PRINTCRLF
	;-------------------------------


	;-------------------------------
	CALL DETECT_CPU
	CALL PRINTCRLF
	;-------------------------------


	;-------------------------------
	MOV SI, A20MSG
	CALL PRINTLN

	CALL SET_A20LINE
	;-------------------------------



	MOV [GDT_INSTALL_END+1], WORD 0x0A00
	MOV [GDT_INSTALL_END+3], WORD 0x0008



	CALL GDT_INITIALISE


	; Uiteraard werkt deze shit nog niet!
	; (bedoeling is GDT aanmaken en naar Protected Mode gaan)


	;-------------------------------
	GDT_INSTALL:
		CLI
	GDT_INSTALL_BEGIN:
		LGDT [GDT_STATIC]	; load general description table

		MOV AX, 8

		MOV GS, AX
		MOV DS, AX
		MOV ES, AX
		MOV FS, AX

		MOV EAX, CR0
		OR EAX, 1
		MOV CR0, EAX		; set PMode thingy


	GDT_INSTALL_END:
		JMP 0x0000:0x0000
	;-------------------------------


;-------------------
DETECT_CPU:
	PUSH EAX
	PUSH EDI
	PUSH ESI
	PUSH ES
	PUSH DS

DETECT_CPU_BEGIN:
	PUSHF

	XOR AH, AH
	PUSH AX
	POPF

	; Check for 8086/8088
	PUSHF
	POP AX
	AND AH, 0xF0
	CMP AH, 0xF0
	JE DETECT_CPU_NO386


	; Check for 286
	MOV AH, 0xF0
	PUSH AX
	POPF

	PUSHF
	POP AX
	AND AH, 0xF0
	JZ DETECT_CPU_NO386

	POPF

	MOV SI, CPU_HURAY
	CALL PRINTLN



	; 32Bit code !!!!

	MOV EAX, DWORD [ADDR_CLIPBOARD]
	CALL MEMADDR_32BIT_TO_DEST

	XOR EAX, EAX
	CPUID

	MOV [DS:EDI], EBX
	MOV [DS:EDI+4], EDX
	MOV [DS:EDI+8], ECX
	; end 32Bit code


	MOV EAX, DWORD [ADDR_CLIPBOARD]
	CALL MEMADDR_32BIT_TO_SRC
	CALL PRINT

	JMP DETECT_CPU_END

DETECT_CPU_NO386:
	MOV SI, CPU_ERROR
	CALL PRINTLN

DETECT_CPU_END:
	POP DS
	POP ES
	POP ESI
	POP EDI
	POP EAX

	RET
;-------------------



;-------------------
times 1024-($-$$)	DB 0

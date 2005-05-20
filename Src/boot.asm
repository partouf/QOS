

;------------------------
;------------------------
; BOOTSECTOR (S1)
;------------------------

ORG 0x7C00				; MemAddr for BootSectors

JMP StartBoot				; Skip the data

;------------------------
;-- Data
;------------------------
MSG_LOAD:	DB 'Loading '
OSID:		DB 'QOS v0.1',0
CHECKSYS:	DB 'QCore',0,0,0, 0,0,0,0 ,255		; QCoreFile signature 12b + 1b
BOOTDRV:	DB 0
;------------------------

MSG_NOBOOT:		DB 'QCore not found...',0
MSG_LoadingCore:	DB 'Loading QCore...',0
MSG_SECTERR:		DB 'Error Copying Sector...',0

;------------------------

%include	"globals.inc"

%define _USE_PRINT_
%include	"display.inc"

%include 	"string.inc"

%include	"drive.inc"

;------------------------
StartBoot:
	CLI			; Disable interrupts
		MOV AX, 0x9000		; Put stack at 0x90000
		MOV SS, AX		; StackSegment = 9000 and
		MOV SP, 0		; StackPointer = 0000 => Stack = 90000
	STI			; Enable interrupts

	MOV [BOOTDRV],DL	; Store bootdrive (set by bios in DL)


LoadRoot:
	MOV SI, MSG_LOAD	; Set SI to the LoadMessage
	CALL PRINTLN		; Show the Message

	MOV DX, SEGMENT_KERNEL
	MOV DS, DX
	MOV DX, OFFSET_KERNEL
	MOV DI, DX


	XOR DX, DX
	MOV DL, [BOOTDRV]

	MOV AX,1		; Sectors to read
	MOV CX,3		; Sector 3 (RootDir)


	CALL LOAD_SECTOR

	JC Error2

	JMP CHECKIT

ENDITALL:
	RET
;------------------------

;------------------------
Error:
	MOV SI, MSG_NOBOOT
	CALL PRINT
;------------------------
HANG:
	WAIT
	JMP HANG
Error2:
	MOV SI, MSG_SECTERR
	CALL PRINT
	JMP HANG

;------------------------
CHECKIT:
	MOV AX, SEGMENT_KERNEL
	MOV ES, AX
	MOV SI, OFFSET_KERNEL			; MEMAdr 0060:0000 = 0000:0600

	; Check if there are files in the root
	LODSB				; AL=[SI] INC SI
	OR AL, AL
	JZ Error			; AL=0? Error (no files)


	ADD SI, 11			; AL+=11


	MOV DI, CHECKSYS		; DI=CHECKSYS MEM Adr
	CHECKIT_FOREACHFILE:

		CALL CMPSTR
		JNZ CHECKIT_FOUND

		ADD SI, 20

		DEC AL
		JNZ CHECKIT_FOREACHFILE

	CHECKIT_ENDFOREACHFILE:

	CHECKIT_NOTFOUND:
		JMP Error

	CHECKIT_FOUND:
		JMP LOADCORE
;------------------------



;------------------------
LOADCORE:
	PUSH SI
	MOV SI, MSG_LoadingCore
	CALL PRINTLN
	POP SI

	; assume SI points to File-ID
	ADD SI, 13		; goto sector number

	LODSW			; Load Sector number at SI (word) to AX
	MOV CX, AX		; CX=AX

	LODSB			; Load Sector span at SI (byte) to AL
	MOV BL, AL

	LODSW			; Load File Begin
	MOV DX, AX


	MOV AX, SEGMENT_KERNEL
	MOV DS, AX
	MOV AX, OFFSET_KERNEL
	MOV DI, AX

	XOR DX, DX
	MOV DL, [BOOTDRV]


	MOV AL, BL
	CALL LOAD_SECTOR


	;MOV [LOADCOREJUMP+1], DX	; set jump to 0x0060:begin
LOADQCore:
	WAIT			; Wait for something to make sure everything goes ok
	MOV AX, SEGMENT_KERNEL
	MOV DS, AX		; Set DestinationSegment to 60h
	MOV ES, AX		; Set ExtraSegment to 60h

LOADCOREJUMP:
	JMP SEGMENT_KERNEL:OFFSET_KERNEL	; Jump to the sector that was written to mem segment 60h
;------------------------


times 510-($-$$)	DB 0
DW 0xAA55


%ifndef _TASKMNG_INC_
%define _TASKMNG_INC_

;-------------------------------
TASKLIST_ADDRESS:	DW 0x00000800
TASKLIST_TASKSIZE:	DB 58	; bij 32bits 58 bytes om taak in op te slaan
				; bij 16bits 40 bytes om taak in op te slaan
;-------------------------------
TASKLIST_CURRENT:	DB 0
TASKLIST_TOTAL:		DB 0
;-------------------------------


;-------------------------------
; 32Bit Task Structure:
; - Byte[1]	ID
; - Byte[12]	Name
; - Byte[1]	Priority (0:Not used, 1:Low, 255:High)

; - Byte[2]	CS
; - Byte[2]	SS
; - Byte[2]	DS
; - Byte[2]	ES

; - Byte[4]	EAX
; - Byte[4]	ECX
; - Byte[4]	EDX
; - Byte[4]	EBX

; - Byte[4]	ESP
; - Byte[4]	EBP
; - Byte[4]	ESI
; - Byte[4]	EDI

; - Byte[4]	Flags
;-------------------------------
; of 16bits kan ook...
; 16Bit Task Structure:
; - Byte[1]	ID
; - Byte[12]	Name
; - Byte[1]	Priority (0:low, 255:high)

; - Byte[2]	CS
; - Byte[2]	SS
; - Byte[2]	DS
; - Byte[2]	ES

; - Byte[2]	AX
; - Byte[2]	CX
; - Byte[2]	DX
; - Byte[2]	BX

; - Byte[2]	SP
; - Byte[2]	BP
; - Byte[2]	SI
; - Byte[2]	DI

; - Byte[2]	Flags
;-------------------------------
;-------------------------------




;-------------------------------
TASKLIST_INITIALISE:
TASKLIST_INITIALISE_BEGIN:

	; eigenlijk niets te doen (aannemend dat geheugen vrij is op [TASKLIST_ADDRESS])

TASKLIST_INITIALISE_END:
	RET
;-------------------------------



;-------------------------------
; AX = Code Segment
; CX = Code Offset
; DX = Data Segment
; BX = Data Offset
; ES:SI = Pointer naar Naam
; Prioriteit = Segment? of standaard 1? of?
;-------------------------------
TASKLIST_QUEUE_PROCESS:
	PUSH CX
	PUSH DX
	PUSH BX
	PUSH SI
TASKLIST_QUEUE_PROCESS_BEGIN:

; 1. Vind eerst een task met prioriteit 0 (0 tot [TASKLIST_TOTAL] +1)
; 2. Niet gevonden?
;    2.1. Maak nieuwe aan [TASKLIST_TOTAL] += 1
; 3. Sla op in:
;    TASKLIST_ADDRESS + TaskID * [TASKLIST_TASKSIZE]
; 4. return AX = ID

TASKLIST_QUEUE_PROCESS_END:
	POP SI
	POP DI
	POP BI
	POP CI
	RET
;-------------------------------


;-------------------------------
; ES:SI = Pointer naar Naam
; AX = ID of 0 om Naam te gebruiken om te unqueuen
;-------------------------------
TASKLIST_UNQUEUE_PROCESS:

TASKLIST_UNQUEUE_PROCESS_BEGIN:

; 1. als AX <> 0, zoek op ID
;    anders, zoek met STRCMP_LEN()
; 2. Zet prioriteit op 0
; 3. als gelijk aan [TASKLIST_CURRENT]... ehm... laat maar dan :P (boeit niet)

TASKLIST_UNQUEUE_PROCESS_END:
	RET
;-------------------------------




;-------------------------------
TASKLIST_MANAGE:

TASKLIST_MANAGE_BEGIN:

; 0. Pop Errorcode?
; 1. Pop EIP from Stack
; 2. Pop CS from Stack
; 3. Pop EFLAGS from Stack


; ??? OF ???

; 0. Pop Errorcode?	-> ?
; 1. Pop EIP		-> in EAX
; 2. Pop CS		-> in ECX
; 3. Pop EFLAGS		-> in EDX
; 4. Pop ESP		-> in EBX
; 5. Pop SS		-> in ES?


; Sla op in geheugen bij [TASKLIST_CURRENT]
; (laat ID, Naam, Prioriteit met rust)


; [TASKLIST_CURRENT] ++ (bij Total, terug naar 0)
; Laad van geheugen..

; Push benodigde dingen terug in goede volgorde:
;  1. Push EFLAGS
;  2. Push CS
;  3. Push EIP
; OF
;  1. Push SS
;  2. Push ESP
;  3. Push EFLAGS
;  4. Push CS
;  5. Push EIP


; Zet registers op goede waardes


TASKLIST_MANAGE_END:
	IRET
;-------------------------------


%endif


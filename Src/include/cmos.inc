%ifndef _CMOS_INC_
%define _CMOS_INC_

;-------------------
; Read Byte AL From CMOS position AL

CMOS_READBYTE:

CMOS_READBYTE_BEGIN:

	OUT 0x70, AL
	IN AL, 0x71

CMOS_READBYTE_END:
	RET
;-------------------


;-------------------
; Write Byte AL To CMOS position AH

CMOS_WRITEBYTE:

CMOS_WRITEBYTE_BEGIN:

	XCHG AL, AH
	OUT 0x70, AL
	XCHG AL, AH
	OUT 0x71, AL

CMOS_WRITEBYTE_END:
	RET
;-------------------



;-------------------
; Copy CMOS to Memory as DS:DI

CMOS_COPYTOMEMORY:
	PUSH AX
	PUSH CX

CMOS_COPYTOMEMORY_BEGIN:
	MOV CX, 7Fh	; loop 0 till 127

	CMOS_COPYTOMEMORY_FOR:
		; read from cmos
		MOV AL, CL
		OUT 0x70, AL
		IN AL, 0x71
		; write to mem
		sTOSB

		DEC CX
		JNZ CMOS_COPYTOMEMORY_FOR

CMOS_COPYTOMEMORY_END:
	POP CX
	POP AX
	RET
;-------------------

%endif

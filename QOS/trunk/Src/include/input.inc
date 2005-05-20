%ifndef _INPUT_INC_
%define _INPUT_INC_


;------------------------
WAIT_KEY:
	XOR AX,AX
	INT 0x16
	RET
;------------------------




;------------------------
;------------------------
REBOOT:
	DB 234,0,0,255,255	; JMP FFFF:0000
	RET
;------------------------


%endif

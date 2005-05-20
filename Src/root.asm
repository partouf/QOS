
;------------------------
;------------------------
; ROOT Directory Index Prefix (S3)
;------------------------

TOTALFILES:	DB 2
OTHER:		DB 0,0,0, 0,0,0,0, 0,0,0,0


FIL2:		DB 'LNK_BootSct_'
ATT2:		DB 255
SEC2:		DW 6
SSP2:		DB 4
BEG2:		DW 0
LEN2:		DW 2048

FIL1:		DB 'QCore',0,0,0, 0,0,0,0
ATT1:		DB 255
SEC1:		DW 6
SSP1:		DB 4
BEG1:		DW 0
LEN1:		DW 2048


times 512-($-$$)	DB 0

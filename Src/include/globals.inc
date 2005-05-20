
%ifndef _GLOBALS_INC_
%define _GLOBALS_INC_
;---------------------------------


;---------------------------------
; defines / equs
;---------------------------------

%define	SECTOR_BOOT		1
%define SECTOR_VDIR_DRIVE	2
%define	SECTOR_ROOT		3


;---------------------------------
; 16bit Realmode addresses
;---------------------------------
%define SEGMENT_KERNEL		0x0000
%define OFFSET_KERNEL		0x0600

%define SEGMENT_STACK		0x9000
%define OFFSET_STACK		0x0000

%define SEGMENT_GDT		0x0000
%define OFFSET_GDT		0x0C00

%define SEGMENT_IDT		0x0000
%define OFFSET_IDT		0x0D00


;---------------------------------
; 32bit addresses
;---------------------------------
ADDR_SCREEN:		DD 0x0000B800

ADDR_CLIPBOARD:		DD 0x00090000

ADDR_VSCREENS:		DD 0x00000E00
ADDR_MOUNTS:		DD 0x00000F00
ADDR_PROCESSES:		DD 0x00001000


;---------------------------------
; others
;---------------------------------
EMPTYSTR:	DB 0



;---------------------------------
%endif

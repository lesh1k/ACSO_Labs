; boot.asm
;
; writes an integrated boot sector out to the floppy disk in the specified drive
;
; This code is derived from sector.asm which you can also find at 
; http://www.beroset.com/
;
; Style Note:
;   There aren't any hardwired numbers in this code.  That is to say,
;   equates and macros are used to render gibberish like this:
;     mov ax,4c00h
;     int 33
;
;   into somewhat self-documenting code like this:
;     DosInt DOS_TERMINATE, 0
;
;   This is done to make the code more readable, and comprehensible, and
;   to aid in maintenance by not littering mysterious constants throughout
;   the code.  Please be kind to animals (specifically your fellow
;   programmers) and use this practice in your own code.
;
;   originally written on Sat  08-09-1997  by Edward J. Beroset
;   rewritten as boot.asm on Fri  03-05-2007 by Edward J. Beroset
;	and donated to the public domain by the author
;

extrn MBR

STACKSIZE        = 200h         ; this is how much stack we'll allocate

CMD_LINE_LEN     = 80h          ; offset of the command line length (one byte)
                                ; relative to the beginning of the PSP.

CMD_LINE         = 81h          ; the offset relative to the beginning of the
                                ; PSP that is the start of the command line
                                ; arguments.


DOS_WRITE_HANDLE = 040h         ; write to open file
DOS_TERMINATE    = 04ch         ; terminate and exit

DOS_INT         = 021h

; various named character constants
NUL     = 0
CR      = 13
LF      = 10
SPACE   = ' '

GenericInt macro function, subfunction
        ifb <subfunction>
                mov     ah,function
        else
                mov     ax,(function SHL 8) OR (subfunction AND 0ffh)
        endif
endm

DosInt  macro function, subfunction
        GenericInt <function>,<subfunction>
        int     DOS_INT
endm

BDISK_WRITE_SECTOR      = 03h

BDISK_INT       = 013h

; constants unique to this program

BOOT_DRIVE      = 0             ; we'll be writing to drive A: unless
				; otherwise specified
BOOT_HEAD       = 0             ; head 0 is the boot head
BOOT_CYLSECT    = 0001h         ; a word value with the following format
                                ; bits 15-8     low bits of cylinder
                                ; bits 7-6      high two bits of cylinder
                                ; bits 5-0      sector
NUM_SECTORS     = 1             ; number of sector to write to disk

        model small
        .386
        .stack  STACKSIZE
        .code
;**********************************************************************
; program code start
;**********************************************************************
Start:
; parse the command line args
        mov     cl,byte ptr [DGROUP:CMD_LINE_LEN]  ; read the length byte
        ; NOTE that the command line length isn't really part of the
        ; DGROUP group, but DS currently points to the PSP, and if we
        ; omit the DGROUP override, the assembler thinks we're trying
        ; to load a constant instead of the contents of the memory loc.
        ; In other words, it's ugly but it has a purpose.
        or      cl,cl                   ; check for zero
        jz      Usage                   ; no command line args
        mov     si,CMD_LINE             ;
        mov     al,' '                  ;
        repe    cmpsb                   ; burn off leading spaces
	; set up the default drive (A:)
        mov     dx,(BOOT_HEAD SHL 8) OR (BOOT_DRIVE)
	cmp	byte ptr [si],'A'	; see if it's A:
	je	writeSector		; if so, it's the default
	inc	dx			; set up for B:
	cmp	byte ptr [si],'B'	; did user say B:?
	jne	Usage			; apparently not, so exit

; now write it out to the floppy disk's boot sector
writeSector:
	mov	bx,seg MBR		; get seg:offset of MBR
	mov	es,bx			;
        mov     bx,offset MBR           ;
        mov     cx,BOOT_CYLSECT         ;
        GenericInt BDISK_WRITE_SECTOR, NUM_SECTORS
        int     BDISK_INT
	mov	si,seg DGROUP		; load correct data segment
	mov	ds,si			;
        mov     si,offset err_write     ;
        jc      ErrorExit               ;
        mov     si,offset msg_ok        ;
ErrorExit:
        mov     cx,[si]                 ;
        inc     si                      ;
        inc     si                      ;
        mov     dx,si                   ;
        mov     bx,1                    ; write to stdout
        DosInt  DOS_WRITE_HANDLE        ; write to that file
        DosInt  DOS_TERMINATE, 0

Usage:
        mov     si,seg DGROUP           ;
        mov     ds,si                   ; load correct data segment
        mov     si,offset use_msg
        jmp     ErrorExit               ;


;**********************************************************************
; program data starts
;**********************************************************************
        .data
msgstruc macro msglabel, msgstring
        local alpha
msglabel dw      (alpha - $) - 2
         db      msgstring
alpha = $
endm

msgstruc err_write ,<"ERROR: unable to write to floppy disk",CR,LF>
msgstruc msg_ok    ,<"Boot sector was successfully written to floppy",CR,LF>
msgstruc use_msg   ,<"Usage:  BOOT A|B",CR,LF>

        end Start

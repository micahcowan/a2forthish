;#resource "forthish.cfg"
;#define CFGFILE forthish.cfg

.include "forthish.inc"

.macro TestStart
    lda #$ff
    ldx #$00
:   sta $100,x
    inx
    bne :-
    
    ldx #$2
    txs

    lda #1
    clc
:   pha
    adc #1
    cmp #6
    bne :-
.endmacro

Start:
	; set up $300 for recovery by "300G" at monitor
        lda #$40
        sta $300
        
        TestStart
        ;dup_
COPY:
        copy_ 4 
ROLL:
        roll_ 4, 2
        
Self:	jmp Self

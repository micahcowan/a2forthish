.segment "STARTUP"

; v  This is the file of interest
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
        copy_ 5 
ROLL:
        roll1_ 5
        copy_ 5
ROLLB:
        rollb1_ 5 ; roll back to original
        rollb1_ 5 ; ...then one more
PICK3:
	lda #$33
        pha
        pick_ 4
PICK10:
	lda #$10
        pha
        pick_ 11
        
Self:	jmp Self

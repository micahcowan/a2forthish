;#resource "forthish.cfg"
;#resource "forthish.inc"
;#define CFGFILE forthish.cfg

;#link "forthish-setup.s"

FORTHISH_NO_IMPORT=1
.include "forthish.inc"

.export roll1, roll1A
roll1:
    ; on stack: number of items to roll
    ;		<16-bit return address>
    rotb_ ; get N past return address
    pla
roll1A:
    sta @adc+1 ; use N to adjust stack ptr in X later
    tsx
    inx ; skip return address
    inx
    stx @cpx+1 ; use to determine when we're done
    txa
    clc
@adc:
    adc #$00 ; overwritten above, to skip N bytes
    tay ; Y is at "bottom" of roll
    tax
    dex ; X is one "up" from there
@loop:
@cpx:
    cpx #$00 ; overwritten above
    beq @finish
    swapXY_
    dex
    jmp @cpx
@finish:
    rts

.export rollb1, rollb1A
rollb1:
    ; on stack: number of items to roll
    ;		<16-bit return address>
    rotb_ ; get N past return address
    pla
rollb1A:
    sta @adc+1 ; use N to adjust stack ptr in X later
    tsx
    inx ; skip return address
    inx
    txa
    inx ; X is at bottom
    clc
@adc:
    adc #$00 ; overwritten above, to skip N bytes
    sta @cpx+1 ; use to determine when we're done
    tay ; Y is at "top" of roll
@loop:
@cpx:
    cpx #$00 ; overwritten above
    beq @finish
    swapXY_
    inx
    jmp @cpx
@finish:
    rts
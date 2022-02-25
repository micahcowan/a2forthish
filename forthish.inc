;; Forthish.inc
;;   minimal Forth-like stack operation macros for 6502
;;
;; Copyright © 2022  Micah J Cowan
;; All rights reserved
;;
;; Permission is hereby granted, free of charge, to any
;; person obtaining a copy of this software and associated
;; documentation files (the "Software"), to deal in the Software
;; without restriction, including without limitation the rights
;; to use, copy, modify, merge, publish, distribute, sublicense,
;; and/or sell copies of the Software, and to permit persons to
;; whom the Software is furnished to do so, subject to the
;; following conditions:
;;
;; The above copyright notice and this permission notice shall
;; be included in all copies or substantial portions of the
;; Software.
;;
;; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
;; KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
;; WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
;; PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
;; OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
;; OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
;; OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
;; SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


;; dup_
;;
;; duplicate the top byte of the stack
.macro dup_
    pla
    pha
    pha
.endmacro

;; swapXY_
;;
;; swaps the byte at stack position marked by register X
;; with the byte at stack position marked by register Y
.macro swapXY_
    lda $100,x
    sta @write+1
    lda $100,y
    sta $100,x
@write:
    lda #$00 ; overwritten above
    sta $100,y
.endmacro

;; roll_ N M
;;
;; roll the top N bytes of the stack, so that if the stack has
;; items numbered (going from bottom to top of stack):
;;   ... [N+1 N] N-1 N-2 ... 0
;; then after this operation, the items will be rearranged like:
;;   ... [N+1 N] M-1 M-2 ... 0 N-1 N-2 ... M+1 M
;; M is expected to be less than N, and N is expected to be
;; at least 1 or greater.
.macro roll_ N, M
.scope
    tsx
    stx @cpx+1
    .repeat M
        inx
    .endrepeat
    txa
    tay
    .repeat N-M
        iny
    .endrepeat
@lp:
    swapXY_
    dex
    dey
@cpx:
    cpx #$00 ; overwritten above
    bne @lp
    txs
.endscope
.endmacro

.macro copy_ N
.scope
    tsx
    stx @cpx+1
    .repeat N
        inx
    .endrepeat
@lp:
    lda $100,x
    pha
    dex
@cpx:
    cpx #$00 ; overwritten above
    bne @lp
.endscope
.endmacro


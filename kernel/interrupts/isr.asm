extern isr_handler


; Macros to instiante ISRs easily
%macro ISR_ERR 1
isr_%+%1:
    call isr_handler
    iret
%endmacro

%macro ISR_NO_ERR 1
isr_%+%1:
    call isr_handler
    iret
%endmacro

; Defining ISRs
ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR 8
ISR_NO_ERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NO_ERR 15
ISR_NO_ERR 16
ISR_ERR 17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_NO_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_ERR 30
ISR_NO_ERR 31

global isr_table
isr_table:
%assign i 0
%rep 32
    dd isr_%+i
%assign i i+1
%endrep



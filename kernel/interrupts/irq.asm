extern irq_handler

; Macros to instiante ISRs easily
%macro IRQ 1
irq_%+%1:
    push DWORD %1
    push DWORD %1
    call irq_handler
    add esp, 8
    iret
%endmacro

; Defining IRQs
IRQ 0 
IRQ 1 
IRQ 2 
IRQ 3 
IRQ 4 
IRQ 5 
IRQ 6 
IRQ 7 
IRQ 8 
IRQ 9 
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15

global irq_table
irq_table:
    %assign i 0
    %rep 16
        dd irq_%+i
    %assign i i+1
    %endrep

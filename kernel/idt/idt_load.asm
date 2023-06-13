extern idt_desc

global idt_load
idt_load:
    lidt [idt_desc]
    ret


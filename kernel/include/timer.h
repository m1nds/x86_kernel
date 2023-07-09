#ifndef TIME_H
#define TIME_H

#define PIT_COMMAND 0x43
#define PIT_REPEAT_MODE 0x36

#define PIT_DATA_CH0 0x40
#define PIT_DATA_CH1 0x41
#define PIT_DATA_CH2 0x42

void timer_interrupt_handler();
void timer_init();

#endif

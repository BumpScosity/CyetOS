#include "lib.h"

int timer_ticks = 0;

void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

void outw(unsigned short port, unsigned short value) {
    asm volatile ("outw %0, %1" : : "a" (value), "Nd" (port));
}

unsigned char inb(unsigned short port) {
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
    return value;
}

void sleep (int ticks){
    int startTicks = timer_ticks;
    while(timer_ticks < startTicks + ticks){}
    return;
}
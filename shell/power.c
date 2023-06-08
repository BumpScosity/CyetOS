#include "../lib/lib.h"
#include "../drivers/screen/vga.h"

#include "cmd.h"

/* keyboard interface IO port: data and control
   READ:   status port
   WRITE:  control register */
#define KBRD_INTRFC 0x64
 
/* keyboard interface bits */
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */
 
#define KBRD_IO 0x60 /* keyboard IO port */
#define KBRD_RESET 0xFE /* reset CPU command */
 
#define bit(n) (1<<(n)) /* Set bit n to 1 */
 
/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags) & bit(n))

/*NOTE: CODE TAKEN FROM https://wiki.osdev.org/Reboot,
    NOT MY CODE, I AIN'T GONNA WRITE IT MYSELF*/

void reboot()
{
    unsigned int temp;
 
    asm volatile ("cli"); /* disable all interrupts */
 
    /* Clear all keyboard buffers (output and command buffers) */
    do
    {
        temp = inb(KBRD_INTRFC); /* empty user data */
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
            inb(KBRD_IO); /* empty keyboard data */
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);
 
    outb(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */
loop:
    asm volatile ("hlt"); /* if that didn't work, halt the CPU */
    goto loop; /* if a NMI is received, halt again */
}

void shutdown(const char *emulator) {
    if (strncmp(emulator, "qemu2.00/bochs", 14) == 0) {
        outw(0xB004, 0x2000);
    }
    else if (strncmp(emulator, "qemu", 4) == 0) {
        outw(0x604, 0x2000);
    }
    else if (strncmp(emulator, "virtualbox", 10) == 0) {
        outw(0x4004, 0x3400);
    }
    else {
        kprintcol("Please specify a type of emulator to shutdown. Use man shutdown for more info.", 0x17);
    }
}
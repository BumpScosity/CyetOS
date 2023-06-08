#include "../core/prog.h"
#include "../drivers/screen/vga.h"

#include "cmd.h"

void help() {
    int *xy = (int*)0x99000;
    screen1("HELP");
    xy[0] = 2;
    kprint("Welcome to the help menu, here is a list of some commands!");
    kprint("use \"man\" for more info on them.");
    xy[0] = 5;
    kprint("help: \"prints a list of commands\"");
    kprint("clear: \"clears the screen\"");
    kprint("echo [text]: \"prints a message to the screen\"");
    screen2();
}
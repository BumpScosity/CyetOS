#include "../drivers/screen/vga.h"
#include "../memory/dynamic.h"
#include "../core/prog.h"

#include "cmd.h"

void help() {
    int *xy = kget("xy");
    screen1("HELP");
    xy[0] = 2;
    kprint("Welcome to the help menu, here is a list of some commands!");
    kprint("use \"man\" for more info on them.");
    xy[0] = 5;
    kprint("help: \"prints a list of commands\"");
    kprint("clear: \"clears the screen\"");
    kprint("echo [text]: \"prints a message to the screen\"");
    kprint("shutdown --options: \"Shuts down the computer\"");
    kprint("reboot: \"restarts the computer\"");

    screen2();
}
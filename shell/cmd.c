#include "../lib/lib.h"
#include "../drivers/screen/vga.h"
#include "../core/prog.h"

#include "cmd.h"

void parse(const char *line) {
    switch (line[0]) {
        case 'c':
            if (strncmp(line, "clear", strlen("clear")-1) == 0) {
                clear();
                break;
            }
        case 'e':
            if (strncmp(line, "echo", strlen("echo")-1) == 0) {
                echo(line);
                break;
            }
        case 'd':
            if (strncmp(line, "dir", strlen("dir")-1) == 0) {
                dir();
                break;
            }
        case 's':
            if (strncmp(line, "shutdown --qemu --old", strlen("shutdown --qemu --old")-1) == 0) {
                shutdown("qemu2.00/bochs");
                break;
            }
            else if (strncmp(line, "shutdown --bochs", strlen("shutdown --bochs")-1) == 0) {
                shutdown("qemu2.00/bochs");
                break;
            }
            else if (strncmp(line, "shutdown --qemu", strlen("shutdown --qemu")-1) == 0) {
                shutdown("qemu");
                break;
            }
            else if (strncmp(line, "shutdown --virtualbox", strlen("shutdown --virtualbox")-1) == 0) {
                shutdown("virtualbox");
                break;
            }
            else if (strncmp(line, "shutdown", strlen("shutdown")-1) == 0) {
                shutdown("none");
                break;
            }
        case 'r':
            if (strncmp(line, "restart", strlen("restart")-1) == 0) {
                reboot();
                break;
            }
            else if (strncmp(line, "reboot", strlen("reboot")-1) == 0) {
                reboot();
                break;
            }
        case 'h':
            if (strncmp(line, "help", strlen("help")-1) == 0) {
                help();
                break;
            }
        default:
            kprint("Unknown command, use \"help\" to get a list of commands...");
            break;
    }
}
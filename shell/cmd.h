#ifndef CMD_H
#define CMD_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef struct {
    int line_num;
    char line[VGA_WIDTH];
} cmds;

void parse(const char *line);

void clear();
void dir();
void help();
void echo(const char *s);
void shutdown(const char *emulator);
void reboot();


#endif // CMD_H
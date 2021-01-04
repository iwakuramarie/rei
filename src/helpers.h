#ifndef REI_HELPERS_H
#define REI_HELPERS_H

#define LENGTH(x)         (sizeof(x) / sizeof(*x))
#define MAXLEN            256

#ifdef DEBUG
#  define PUTS(x)         puts(x)
#  define PRINTF(x,...)   printf(x, __VA_ARGS__)
#else
#  define PUTS(x)         ((void)0)
#  define PRINTF(x,...)   ((void)0)
#endif

void warn(char *fmt, ...);
__attribute__((noreturn))
void err(char *fmt, ...);
void execute(char *cmd[]);
void spawn(char *cmd[], bool sync);
void run(char *command, bool sync);
char *lgraph(char *s);
char *rgraph(char *s);

#endif

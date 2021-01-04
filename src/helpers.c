#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "rei.h"

void warn(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}

__attribute__((noreturn))
void err(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void run(char *command, bool sync)
{
	char *cmd[] = {shell, "-c", command, NULL};
	spawn(cmd, sync);
}

void spawn(char *cmd[], bool sync)
{
	if (fork() == 0) {
		if (dpy != NULL)
			close(xcb_get_file_descriptor(dpy));
		if (sync) {
			execute(cmd);
		} else {
			if (fork() == 0) {
				execute(cmd);
			}
			exit(EXIT_SUCCESS);
		}
	}
	wait(NULL);
}

void execute(char *cmd[])
{
	setsid();
	if (redir_fd != -1) {
		dup2(redir_fd, STDOUT_FILENO);
		dup2(redir_fd, STDERR_FILENO);
	}
	execvp(cmd[0], cmd);
	err("Spawning failed.\n");
}

char *lgraph(char *s)
{
	size_t len = strlen(s);
	unsigned int i = 0;
	while (i < len && !isgraph(s[i]))
		i++;
	if (i < len)
		return (s + i);
	else
		return NULL;
}

char *rgraph(char *s)
{
	int i = strlen(s) - 1;
	while (i >= 0 && !isgraph(s[i]))
		i--;
	if (i >= 0)
		return (s + i);
	else
		return NULL;
}

#ifndef REI_REI_H
#define REI_REI_H

#include <xcb/xcb_keysyms.h>
#include <stdio.h>
#include <stdbool.h>
#include "types.h"
#include "helpers.h"

#define CONFIG_HOME_ENV     "XDG_CONFIG_HOME"
#define REI_SHELL_ENV       "REI_SHELL"
#define SHELL_ENV           "SHELL"
#define CONFIG_PATH         "rei/reirc"
#define HOTKEY_PREFIX       'H'
#define COMMAND_PREFIX      'C'
#define BEGIN_CHAIN_PREFIX  'B'
#define END_CHAIN_PREFIX    'E'
#define TIMEOUT_PREFIX      'T'
#define TIMEOUT              3

extern xcb_connection_t *dpy;
extern xcb_window_t root;
extern xcb_key_symbols_t *symbols;

extern char *shell;
extern char config_file[MAXLEN];
extern char *config_path;
extern char **extra_confs;
extern int num_extra_confs;
extern int redir_fd;
extern FILE *status_fifo;
extern char progress[3 * MAXLEN];
extern int mapping_count;
extern int timeout;

extern hotkey_t *hotkeys_head, *hotkeys_tail;
extern bool running, grabbed, toggle_grab, reload, bell, chained, locked;
extern xcb_keysym_t abort_keysym;
extern chord_t *abort_chord;

extern uint16_t num_lock;
extern uint16_t caps_lock;
extern uint16_t scroll_lock;

void key_button_event(xcb_generic_event_t *evt, uint8_t event_type);
void mapping_notify(xcb_generic_event_t *evt);
void setup(void);
void cleanup(void);
void reload_cmd(void);
void toggle_grab_cmd(void);
void hold(int sig);
void put_status(char c, const char *s);

#endif

#ifndef REI_TYPES_H
#define REI_TYPES_H

#include <xcb/xcb_keysyms.h>
#include <stdbool.h>
#include "helpers.h"

#define KEYSYMS_PER_KEYCODE  4
#define MOD_STATE_FIELD      255
#define ESCAPE_KEYSYM        0xff1b
#define SYNCHRONOUS_CHAR     ';'

extern xcb_keysym_t Mode_switch;

typedef struct chord_t chord_t;
struct chord_t {
	char repr[MAXLEN];
	xcb_keysym_t keysym;
	xcb_button_t button;
	uint16_t modfield;
	uint8_t event_type;
	bool replay_event;
	bool lock_chain;
	chord_t *next;
	chord_t *more;
};

typedef struct {
	chord_t *head;
	chord_t *tail;
	chord_t *state;
} chain_t;

typedef struct {
	int period;
	int delay;
} cycle_t;

typedef struct hotkey_t hotkey_t;
struct hotkey_t {
	chain_t *chain;
	char command[2 * MAXLEN];
	bool sync;
	cycle_t *cycle;
	hotkey_t *next;
	hotkey_t *prev;
};

typedef struct {
	char *name;
	xcb_keysym_t keysym;
} keysym_dict_t;

hotkey_t *find_hotkey(xcb_keysym_t keysym, xcb_button_t button, uint16_t modfield, uint8_t event_type, bool *replay_event);
bool match_chord(chord_t *chord, uint8_t event_type, xcb_keysym_t keysym, xcb_button_t button, uint16_t modfield);
chord_t *make_chord(xcb_keysym_t keysym, xcb_button_t button, uint16_t modfield, uint8_t event_type, bool replay_event, bool lock_chain);
void add_chord(chain_t *chain, chord_t *chord);
chain_t *make_chain(void);
cycle_t *make_cycle(int delay, int period);
hotkey_t *make_hotkey(chain_t *chain, char *command);
void add_hotkey(hotkey_t *hk);
void abort_chain(void);
void destroy_chain(chain_t *chain);
void destroy_chord(chord_t *chord);

#endif

#ifndef REI_PARSE_H
#define REI_PARSE_H

#include "rei.h"

#define RELEASE_PREFIX       '@'
#define REPLAY_PREFIX        '~'
#define START_COMMENT        '#'
#define MAGIC_INHIBIT        '\\'
#define PARTIAL_LINE         '\\'
#define GRP_SEP              ":"
#define LNK_SEP              ";" GRP_SEP
#define SYM_SEP              "+ "
#define SEQ_BEGIN            '{'
#define SEQ_END              '}'
#define SEQ_SEP              ","
#define SEQ_NONE             '_'

typedef struct chunk_t chunk_t;
struct chunk_t {
	char text[2 * MAXLEN];
	char item[2 * MAXLEN];
	char *advance;
	bool sequence;
	char range_cur;
	char range_max;
	chunk_t *next;
};

void load_config(const char *config_file);
void parse_event(xcb_generic_event_t *evt, uint8_t event_type, xcb_keysym_t *keysym, xcb_button_t *button, uint16_t *modfield);
void process_hotkey(char *hotkey_string, char *command_string);
char *get_token(char *dst, char *ign, char *src, char *sep);
void render_next(chunk_t *chunks, char *dest);
chunk_t *extract_chunks(char *s);
chunk_t *make_chunk(void);
void destroy_chunks(chunk_t *chunk);
bool parse_chain(char *string, chain_t *chain);
bool parse_keysym(char *name, xcb_keysym_t *keysym);
bool parse_button(char *name, xcb_button_t *butidx);
bool parse_modifier(char *name, uint16_t *modfield);
bool parse_fold(char *string, char *folded_string);
uint8_t key_to_button(uint8_t event_type);
void get_standard_keysyms(void);
void get_lock_fields(void);
int16_t modfield_from_keysym(xcb_keysym_t keysym);
int16_t modfield_from_keycode(xcb_keycode_t keycode);
xcb_keycode_t *keycodes_from_keysym(xcb_keysym_t keysym);

#endif

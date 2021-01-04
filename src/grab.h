#ifndef REI_GRAB_H
#define REI_GRAB_H

#include "rei.h"

void grab(void);
void grab_chord(chord_t *chord);
void grab_key_button(xcb_keycode_t keycode, xcb_button_t button, uint16_t modfield);
void grab_key_button_checked(xcb_keycode_t keycode, xcb_button_t button, uint16_t modfield);
void ungrab(void);

#endif

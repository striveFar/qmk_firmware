#include QMK_KEYBOARD_H
#include "thumbstick.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN     1
#define _NUMPAD 2
#define _BLANK  3

// Some basic macros
#define TASK    LCTL(LSFT(KC_ESC))
#define TAB_R   LCTL(KC_TAB)
#define TAB_L   LCTL(LSFT(KC_TAB))
#define TAB_RO  LCTL(LSFT(KC_T))

// TODO
#define JOY_MODE KC_FN0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_5x7(
  // left hand
   KC_ESC,    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,
   KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_LBRC,
   KC_LCTL,   KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   TAB_RO,
   OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,	KC_VOLU,   KC_MUTE,   KC_VOLD,
   KC_CAPS,   KC_LGUI, TAB_L,   TAB_R,
                               TT(_FN), KC_SPC,			      KC_2,
                               KC_END, KC_HOME,                 KC_1, KC_5, KC_3,
                               KC_PSCR, TASK,                         KC_4,
        // right hand
		                     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,
		                     KC_RBRC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
		                 TG(_NUMPAD), KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
   KC_VOLU,   KC_MUTE,   KC_VOLD,       KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT),
		                                       KC_LEFT, KC_UP,    KC_DOWN,  KC_RGHT,
         KC_2,	        KC_BSPC, KC_ENT,
   KC_1, KC_5, KC_2,	KC_PGUP, KC_PGDN,
         KC_4,	        KC_LCTL, KC_LALT),

[_FN] = LAYOUT_5x7(
  // left hand
   _______,   KC_F1,     KC_F2,      KC_F3,    KC_F4,     KC_F5,    KC_F6,
   _______,   _______,   _______,    KC_UP,    _______,   _______,  _______,
   _______,   _______,   KC_LEFT,    KC_DOWN,  KC_RGHT,   _______,  RESET,
   _______,   _______,   _______,   _______,   _______,   _______,	KC_VOLU,   KC_MUTE,   KC_VOLD,
   KC_MSTP,   KC_MPLY,   KC_MPRV,   KC_MNXT,
                               _______, _______,			      KC_2,
                               _______, _______,			KC_1, KC_5, KC_1,
                               _______, JOY_MODE,			      KC_4,
        // right hand
		                     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    _______,
		                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
		                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
    KC_VOLU,   KC_MUTE,   KC_VOLD,              _______,   _______,   _______,   _______,   _______,   _______,
		                                                      _______,   _______,   _______,   _______,
          KC_2,		        KC_DEL, _______,
    KC_1, KC_5, KC_2,	        _______, _______,
          KC_4,		        _______, _______),

[_NUMPAD] = LAYOUT_5x7(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,	 KC_VOLU,   KC_MUTE,   KC_VOLD,
   _______,   _______,   _______,   _______,
                               _______, _______,				      KC_2,
                               _______, _______,                                KC_1, KC_5, KC_4,
                               _______, _______,                                      KC_4,
        // right hand
		                     _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,   _______,
		                     _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
		                     _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
	KC_VOLU,   KC_MUTE,   KC_VOLD,	        _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
		                                                      KC_P0,     KC_PDOT,   _______,   _______,
	      KC_2,			        _______, KC_PENT,
	KC_1, KC_5, KC_2,		        _______, _______,
	      KC_4,			        _______, _______),


[_NUMPAD] = LAYOUT_5x7(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,       KC_VOLU,   KC_MUTE,   KC_VOLD,
   _______,   _______,   _______,   _______,
                               _______, _______,                                         KC_2,
                               _______, _______,                                   KC_1, KC_5, KC_5,
                               _______, _______,                                         KC_4,
        // right hand
		                     _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,   _______,
		                     _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
		                     _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
	KC_VOLU,   KC_MUTE,   KC_VOLD,	        _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
			                                              KC_P0,     KC_PDOT,   _______,   _______,
	      KC_2,				        _______, KC_PENT,
	KC_1, KC_5, KC_2,			        _______, _______,
	      KC_4,				        _______, _______),

[_BLANK] = LAYOUT_5x7(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,	      _______,   _______,   _______,
   _______,   _______,   _______,   _______,
                               _______, _______,					 _______,
                               _______, _______,				_______, _______, _______,
                               _______, _______,					 _______,
        // right hand
		                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
		                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
		                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
	KC_VOLU,   KC_MUTE,   KC_VOLD,          _______,   _______,   _______,   _______,   _______,   _______,
		                                                      _______,   _______,   _______,   _______,
		 _______,	        _______, _______,
        _______, _______, _______,      _______, _______,
		 _______,	        _______, _______),


};

enum fn_functions {
    JOY_CONTROL,
};

enum fn_keyboard_control {
    JOY_CONTROL_MODE
};

const uint16_t fn_actions[] = {
    ACTION_FUNCTION_OPT(JOY_CONTROL, JOY_CONTROL_MODE),
};

/* Function */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {

    if (record->event.pressed) {
        switch (id) {
        case JOY_CONTROL:
            switch (opt) {
            case JOY_CONTROL_MODE:
		thumbstick_mode_cycle(false);
                break;
            default:
                break;
            }

        default:
            break;
        }
    }
}

// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Tap dance states
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_EL,
    TD_TO1_TO2,
};

bool is_alt_tab_active = false;

enum custom_keycodes {
    QMKCBSN = SAFE_RANGE,
    QMKLBRCC,
    QMKRBRCC,
    QMKLBRCD,
    QMKRBRCD,
    QMKLBRCS,
    QMKRBRCS,
    QMKALTTAB,
    QMKCCEDIL,
    QMKCWPLUS,
    QMKCWMINUS,
    QMKCWLT,
    QMKCWGT,
};

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void el_released(tap_dance_state_t *state, void *user_data);
void el_finished(tap_dance_state_t *state, void *user_data);
void el_reset(tap_dance_state_t *state, void *user_data);

void l_finished(tap_dance_state_t *state, void *user_data);
void l_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_EL]      = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, el_released, el_finished, el_reset),
    [TD_TO1_TO2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_finished, l_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     * │Esc│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │Tab│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
     * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │   │
     * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
     *               ┌───┐                   ┌───┐
     *               │GUI├───┐           ┌───┤   │
     *               └───┤Ctl├───┐   ┌───┤Alt├───┘
     *                   └───┤Ent│   │Spc├───┘
     *                       └───┘   └───┘
     */

    // clang-format off
    [0] = LAYOUT_split_3x6_3(
        QK_GESC,       KC_Q, KC_W, KC_E, KC_R,    KC_T,                                 KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB,        KC_A, KC_S, KC_D, KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V,    KC_B,                                 KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, OSL(3),
                                         KC_LGUI, KC_LCTL, TD(TD_EL),           KC_SPC, KC_LALT, TD(TD_TO1_TO2)
    ),
    [1] = LAYOUT_split_3x6_3(
        KC_TRNS,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
        KC_TRNS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TRNS,  KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS, KC_LCBR,                           KC_RCBR, KC_COLN, KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS,
                                             KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, TG(1)
    ),
    [2] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_NO,   KC_NO,   QMKLBRCS,  QMKRBRCS,   KC_NO,                         KC_NO,   QMKLBRCC, QMKRBRCC, KC_NO,   KC_F12,  KC_TRNS,
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,     KC_F4,      KC_F5,                         KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_NO,   QMKCWLT, QMKCWPLUS, QMKCWMINUS, QMKCWGT,                       QMKCBSN, QMKLBRCD, QMKRBRCD, KC_NO,   KC_NO,   KC_F12,
                                              KC_TRNS,    KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, TG(2)
    ),
    [3] = LAYOUT_split_3x6_3(
        KC_GRV,    KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
        QMKCCEDIL, KC_1,    KC_2,    KC_3,     KC_4,     KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TRNS,   KC_EQL,  KC_PLUS, KC_MINS,  KC_UNDS,  KC_LCBR,                        KC_RCBR, KC_LBRC, KC_RBRC, KC_DOT,  KC_SLSH, KC_TRNS,
                                               KC_TRNS,  KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [4] = LAYOUT_split_3x6_3(
        KC_TILD,   KC_NO,   G(KC_7), G(KC_8), G(KC_9),  KC_NO,                             KC_APP,  KC_INS,  KC_HOME, KC_PGUP,  KC_PSCR, KC_TRNS,
        QMKALTTAB, KC_NO,   G(KC_4), G(KC_5), G(KC_6),  KC_NO,                             KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_SCRL, KC_ENT,
        KC_TRNS,   G(KC_0), G(KC_1), G(KC_2), G(KC_3),  KC_NO,                             KC_NO,   KC_DEL,  KC_END,  KC_PGDN,  KC_PAUS, KC_RALT,
                                              KC_TRNS,  KC_TRNS, KC_TRNS,       C(KC_ENT), KC_TRNS, KC_TRNS
    ),
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKCBSN:
            if (record->event.pressed) {
            } else {
                // Ctrl+backslash Ctrl+n
                SEND_STRING(SS_LCTL("\\n"));
            }
            break;
        case QMKLBRCC:
            if (record->event.pressed) {
            } else {
                SEND_STRING("[c");
            }
            break;
        case QMKRBRCC:
            if (record->event.pressed) {
            } else {
                SEND_STRING("]c");
            }
            break;
        case QMKLBRCD:
            if (record->event.pressed) {
            } else {
                SEND_STRING("[d");
            }
            break;
        case QMKRBRCD:
            if (record->event.pressed) {
            } else {
                SEND_STRING("]d");
            }
            break;
        case QMKLBRCS:
            if (record->event.pressed) {
            } else {
                SEND_STRING("[s");
            }
            break;
        case QMKRBRCS:
            if (record->event.pressed) {
            } else {
                SEND_STRING("]s");
            }
            break;
        case QMKALTTAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                    /* rdp workaround */
                    wait_ms(16);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case QMKCCEDIL:
            if (record->event.pressed) {
            } else {
                SEND_STRING(SS_DOWN(X_RALT) SS_DELAY(16) "," SS_UP(X_RALT));
            }
            break;
        case QMKCWLT:
            if (record->event.pressed) {
            } else {
                SEND_STRING(SS_LCTL("w") "<");
            }
            break;
        case QMKCWPLUS:
            if (record->event.pressed) {
            } else {
                SEND_STRING(SS_LCTL("w") "+");
            }
            break;
        case QMKCWMINUS:
            if (record->event.pressed) {
            } else {
                SEND_STRING(SS_LCTL("w") "-");
            }
            break;
        case QMKCWGT:
            if (record->event.pressed) {
            } else {
                SEND_STRING(SS_LCTL("w") ">");
            }
            break;
    }
    return true;
};

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            if (!state->pressed) {
                return TD_SINGLE_TAP;
            } else {
                return TD_SINGLE_HOLD;
            }
        case 2:
            return TD_DOUBLE_TAP;
        default:
            return TD_UNKNOWN;
    }
}

// Initialize tap structure associated with ENTER navigaton layer tap dance key
static td_tap_t el_tap_state = {
    .is_press_action = true,
    .state           = TD_NONE,
};

// Functions that control what our tap dance key does
void el_released(tap_dance_state_t *state, void *user_data) {
    if (is_alt_tab_active) {
        is_alt_tab_active = false;
        unregister_code(KC_LALT);
    }
}

void el_finished(tap_dance_state_t *state, void *user_data) {
    el_tap_state.state = cur_dance(state);
    switch (el_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_ENT);
        case TD_SINGLE_HOLD:
            layer_invert(4);
            break;
        default:
            break;
    }
}

void el_reset(tap_dance_state_t *state, void *user_data) {
    switch (el_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_ENT);
        case TD_SINGLE_HOLD:
            layer_invert(4);
            break;
        default:
            break;
    }
    el_tap_state.state = TD_NONE;
}

// Initialize tap structure associated with layer navigaton tap dance key
static td_tap_t l_tap_state = {
    .is_press_action = true,
    .state           = TD_NONE,
};

// Functions that control what our tap dance key does
void l_finished(tap_dance_state_t *state, void *user_data) {
    l_tap_state.state = cur_dance(state);
    switch (l_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_invert(1);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_TAP:
            layer_invert(2);
            break;
        default:
            break;
    }
}

void l_reset(tap_dance_state_t *state, void *user_data) {
    if (l_tap_state.state == TD_SINGLE_HOLD) {
        layer_invert(2);
    }
    l_tap_state.state = TD_NONE;
}

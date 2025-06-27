/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "action_tapping.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    WIN_HALF_QWERTY,
};

// ─────────────────────────── Keymaps ───────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [MAC_BASE] = LAYOUT_104_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  BL_STEP,  KC_DEL,   KC_F13,   KC_F14,   KC_F15,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,  KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,              KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,              KC_PDOT         ),

    [MAC_FN] = LAYOUT_104_ansi(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  BL_DOWN,  BL_UP,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  BL_TOGG,  _______,  _______,  _______,  _______,  BL_TOGG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,  _______,
        BL_TOGG,  BL_STEP,  BL_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,  _______,
        _______,  _______,  BL_DOWN,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,            _______,  _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,            _______         ),

    [WIN_BASE] = LAYOUT_104_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  BL_STEP,  KC_DEL,   KC_F13,   KC_F14,   KC_F15,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,  KC_P4,    KC_P5,    KC_P6,
        OSM(MOD_LSFT),      KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,          OSM(MOD_RSFT), KC_UP,             KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                LT(WIN_HALF_QWERTY, KC_SPC),            KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,              KC_PDOT         ),

    [WIN_FN] = LAYOUT_104_ansi(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  BL_DOWN,  BL_UP,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  BL_TOGG,  _______,  _______,  _______,  _______,  BL_TOGG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,  _______,
        BL_TOGG,  BL_STEP,  BL_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,  _______,
        _______,  _______,  BL_DOWN,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,            _______,  _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,            _______         ),

    [WIN_HALF_QWERTY] = LAYOUT_104_ansi(
        QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,    _______,  _______,            _______,  _______,  _______,  _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     _______,    _______,  _______,            _______,  _______,  _______,  _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                 _______,            KC_INS,   _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  KC_Z,     KC_X,     KC_C,     KC_V,                 _______,  _______,            _______,  _______,  _______, _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,            _______        ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(BL_DOWN, BL_UP)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(BL_DOWN, BL_UP)},
    [WIN_HALF_QWERTY] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif

// ─────────────── Sticky Modifier Handling ───────────────
#define MODIFIER_TIMEOUT    5000
#define IS_OSM_SHIFT(kc) ((kc) == OSM(MOD_RSFT) || (kc) == OSM(MOD_LSFT))

#define IS_REAL_MOD(kc) \
    ((kc) == KC_RCTL || (kc) == KC_LCTL || \
     (kc) == KC_RALT || (kc) == KC_LALT || \
     (kc) == KC_RSFT || (kc) == KC_LSFT || \
     (kc) == KC_CAPS || (kc) == KC_INS || \
     (kc) == KC_F14  || (kc) == KC_F15 || \
     IS_OSM_SHIFT(kc))

static uint16_t last_ctrl_tap = 0;
static bool sticky_ctrl_active = false;
static bool ctrl_waiting_for_release = false;

static uint16_t last_alt_tap = 0;
static bool sticky_alt_active = false;
static bool alt_waiting_for_release = false;

static uint16_t last_mod_activity = 0;

// ─────────────── One-shot Modifier Tracking ───────────────
static bool shift_was_active = false;
static bool caps_was_active = false;
static bool insert_was_active = false;

static uint16_t caps_press_timer = 0;   // 0 = not pressed
static bool     caps_hold_active  = false;  // true while physical key is held *after* TAPPING_TERM
static uint16_t insert_press_timer = 0;
static bool     insert_hold_active = false;

static void clear_all_modifiers(void) {
    unregister_mods(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT) | MOD_BIT(KC_RSFT));
    clear_oneshot_mods();
    unregister_code(KC_CAPS);
    unregister_code(KC_INS);

    sticky_ctrl_active = false;
    sticky_alt_active = false;
    ctrl_waiting_for_release = false;
    alt_waiting_for_release = false;
    shift_was_active = false;
    caps_was_active = false;
    insert_was_active = false;
    tap_code(KC_F14);
}

void matrix_scan_user(void) {
    uint8_t osm_mods = get_oneshot_mods();

    if (osm_mods & (MOD_BIT(KC_RSFT) | MOD_BIT(KC_LSFT))) {
        if (!shift_was_active) {
            /* 1 ─ take Shift out of the HID report for a moment */
            uint8_t saved = get_oneshot_mods();
            clear_oneshot_mods();

            /* 2 ─ tell AHK “Shift has begun” */
            tap_code(KC_F15);          // press + release F15

            /* 3 ─ put the one-shot Shift back so the next key is shifted */
            add_oneshot_mods(saved);

            shift_was_active  = true;
            last_mod_activity = timer_read();
        }
    } else if (shift_was_active) {
        shift_was_active = false;
        tap_code(KC_F14);
    }

    if ((sticky_ctrl_active || sticky_alt_active || shift_was_active || caps_was_active || insert_was_active) &&
        timer_elapsed(last_mod_activity) > MODIFIER_TIMEOUT) {
        clear_all_modifiers();
    }

    /* Promote Caps tap→hold once it’s been down for longer than TAPPING_TERM */
    if (caps_press_timer && !caps_hold_active &&
        timer_elapsed(caps_press_timer) >= TAPPING_TERM) {

        register_code(KC_CAPS);              // press Caps for real
        caps_hold_active  = true;
        caps_was_active   = false;           // not sticky, it’s a real hold
        last_mod_activity = timer_read();
    }

    /* Promote Insert tap→hold once TAPPING_TERM is reached */
    if (insert_press_timer && !insert_hold_active &&
        timer_elapsed(insert_press_timer) >= TAPPING_TERM) {

        register_code(KC_INS);
        insert_hold_active  = true;
        insert_was_active   = false;    // not sticky, it's real hold
        last_mod_activity   = timer_read();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t now = timer_read();

    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    if (IS_REAL_MOD(keycode)) {
        last_mod_activity = now;
    }

    /* ───────── CAPS TAP-vs-HOLD ───────── */
    if (keycode == KC_CAPS) {
        if (record->event.pressed) {
            /* key DOWN – start timer, decide later */
            caps_press_timer = now;
            return false;                    // swallow event for now
        } else {
            /* key UP – figure out what happened */
            uint16_t elapsed = timer_elapsed(caps_press_timer);
            caps_press_timer = 0;

            if (caps_hold_active) {
                /* was in real hold → release it */
                unregister_code(KC_CAPS);
                caps_hold_active = false;
                return false;
            }

            /* it was a tap → sticky one-shot */
            if (elapsed < TAPPING_TERM) {
                register_code(KC_CAPS);      // press and keep it down logically
                caps_was_active   = true;
                last_mod_activity = now;
            }
            return false;
        }
    }

    /* ───────── INSERT TAP-vs-HOLD ───────── */
    if (keycode == KC_INS) {
        if (record->event.pressed) {
            insert_press_timer = now;
            return false;
        } else {
            uint16_t elapsed = timer_elapsed(insert_press_timer);
            insert_press_timer = 0;

            if (insert_hold_active) {
                unregister_code(KC_INS);
                insert_hold_active = false;
                return false;
            }

            if (elapsed < TAPPING_TERM) {
                register_code(KC_INS);
                insert_was_active = true;
                last_mod_activity = now;
            }
            return false;
        }
    }

    // Sticky Ctrl
    if (keycode == KC_RCTL || keycode == KC_LCTL) {
        if (record->event.pressed) {
            if (timer_elapsed(last_ctrl_tap) < 500) {
                // Double tap: sticky mode -> send a real down event
                register_code(KC_RCTL);
                sticky_ctrl_active = true;
            } else {
                last_ctrl_tap = now;
                register_code(KC_RCTL);  // normal hold
            }
        } else {
            // Only release if not sticky
            if (!sticky_ctrl_active) {
                unregister_code(KC_RCTL);
            }
        }
        return false;
    }

    // Sticky Alt
    if (keycode == KC_RALT || keycode == KC_LALT) {
        if (record->event.pressed) {
            if (timer_elapsed(last_alt_tap) < 500) {
                register_code(KC_RALT);
                sticky_alt_active = true;
            } else {
                last_alt_tap = now;
                register_code(KC_RALT);  // normal hold
            }
        } else {
            if (!sticky_alt_active) {
                unregister_code(KC_RALT);
            }
        }
        return false;
    }


    // Track whether to release sticky mods after non-mod key
    if (record->event.pressed &&
        !IS_REAL_MOD(keycode) &&
        keycode != OSM(MOD_RSFT) && keycode != OSM(MOD_LSFT)) {
        if (sticky_ctrl_active) ctrl_waiting_for_release = true;
        if (sticky_alt_active) alt_waiting_for_release = true;
    }

    // Release all sticky mods (incl. SHIFT, CTRL, ALT, CAPS and INSERT) on next key release
    if (!record->event.pressed &&
        !IS_REAL_MOD(keycode) &&
        keycode != OSM(MOD_RSFT) && keycode != OSM(MOD_LSFT) &&
        !shift_was_active) {

        if (ctrl_waiting_for_release) {
            unregister_mods(MOD_BIT(KC_RCTL));
            sticky_ctrl_active = false;
            ctrl_waiting_for_release = false;
        }

        if (alt_waiting_for_release) {
            unregister_mods(MOD_BIT(KC_RALT));
            sticky_alt_active = false;
            alt_waiting_for_release = false;
        }

        if (caps_was_active) {
            unregister_code(KC_CAPS);
            caps_was_active = false;
        }

        if (insert_was_active) {
            unregister_code(KC_INS);
            insert_was_active = false;
        }
    }
    return true;
}

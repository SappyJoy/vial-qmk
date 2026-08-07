#include QMK_KEYBOARD_H

// NOTE: In Vial this file only supplies the *defaults* that get copied into
// EEPROM the first time the board boots (or after an EEPROM reset).
// Once flashed, edit everything from the Vial GUI instead.
//
// IMPORTANT: the number of layers defined here must equal
// DYNAMIC_KEYMAP_LAYER_COUNT in config.h (8), otherwise dynamic_keymap_reset()
// reads past the end of this array.

enum layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM,
    _FUN,
    _DOTA_BASE,
    _DOTA_FUN,
    _SPARE      // empty scratch layer, here to match DYNAMIC_KEYMAP_LAYER_COUNT
};

// SCGA: Pinky(Shift), Ring(Ctrl), Middle(Gui), Index(Alt)
#define HM_A LSFT_T(KC_A)
#define HM_S LCTL_T(KC_S)
#define HM_D LGUI_T(KC_D)
#define HM_F LALT_T(KC_F)

#define HM_J RALT_T(KC_J)
#define HM_K RGUI_T(KC_K)
#define HM_L RCTL_T(KC_L)
#define HM_SCLN RSFT_T(KC_SCLN)

#define OSM_CS OSM(MOD_LCTL | MOD_LSFT)

// Fires Alt+Shift, matching grp:alt_shift_toggle in your X11 config
#define RU_TOGG LALT(KC_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE LAYER
   * NOTE: right-hand top row is a faithful copy of your qmk_firmware keymap:
   * KC_P is missing (KC_QUOT sits in its place) and the outer column holds
   * KC_Q. If that was a typo, just fix it in the Vial GUI after flashing.
   */
  [_BASE] = LAYOUT_split_3x6_3(
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, HM_A,    HM_S,    HM_D,    HM_F,    KC_G,       KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,
    XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
                      KC_ESC,  LT(_NAV, KC_SPC), LT(_NUM, KC_TAB),   LT(_SYM, KC_ENT), LT(_FUN, KC_BSPC), KC_DEL
  ),

  /* NAV LAYER */
  [_NAV] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                               _______, _______, _______,    KC_ENT,  KC_BSPC, KC_DEL
  ),

  /* NUM LAYER */
  [_NUM] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, XXXXXXX,
    XXXXXXX, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,    KC_EQL,  KC_4,    KC_5,    KC_6,    KC_0,    XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_MINS, KC_1,    KC_2,    KC_3,    KC_DOT,  XXXXXXX,
                               _______, _______, _______,    _______, _______, _______
  ),

  /* SYM LAYER */
  [_SYM] = LAYOUT_split_3x6_3(
    XXXXXXX, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_P,    KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,    XXXXXXX, KC_RALT, KC_RGUI, KC_RCTL, KC_RSFT, XXXXXXX,
    XXXXXXX, KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               KC_LPRN, KC_RPRN, KC_UNDS,    _______, _______, _______
  ),

  /* FUN LAYER */
  [_FUN] = LAYOUT_split_3x6_3(
    TG(_DOTA_BASE), KC_F1, KC_F2,  KC_F3,   KC_F4,   KC_PSCR,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_DOTA_BASE),
    XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   RU_TOGG,       XXXXXXX, KC_RALT, KC_RGUI, KC_RCTL, KC_RSFT, XXXXXXX,
    XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  CW_TOGG,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______,    _______, _______, _______
  ),

  /* DOTA BASE */
  [_DOTA_BASE] = LAYOUT_split_3x6_3(
    KC_Y,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    OSM_CS,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                      MO(_DOTA_FUN), KC_H, KC_SPC,           KC_ENT,  KC_BSPC, TG(_DOTA_BASE)
  ),

  /* DOTA FUN */
  [_DOTA_FUN] = LAYOUT_split_3x6_3(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_2,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_1,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_ENT,
    KC_5,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_3,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                               _______, _______, _______,    _______, _______, _______
  ),

  /* SPARE - free layer to play with from the Vial GUI */
  [_SPARE] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;   // vertical, standard for Corne
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("LAYER\n\n"), false);
        switch (get_highest_layer(layer_state)) {
            case _BASE:      oled_write_P(PSTR("base "), false); break;
            case _NAV:       oled_write_P(PSTR("nav  "), false); break;
            case _NUM:       oled_write_P(PSTR("num  "), false); break;
            case _SYM:       oled_write_P(PSTR("sym  "), false); break;
            case _FUN:       oled_write_P(PSTR("fun  "), false); break;
            case _DOTA_BASE: oled_write_P(PSTR("dota "), false); break;
            case _DOTA_FUN:  oled_write_P(PSTR("dota+"), false); break;
            default:         oled_write_P(PSTR("?????"), false); break;
        }
    } else {
        oled_write_P(PSTR("corne\n"), false);
    }
    return false;
}
#endif

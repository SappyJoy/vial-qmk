#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM,
    _FUN,
    _DOTA_BASE,
    _DOTA_FUN,
    _SPARE
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
#define RU_TOGG LALT(KC_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE LAYER */
  [_BASE] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    HM_A,    HM_S,    HM_D,    HM_F,    KC_G,       KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                      KC_ESC,  LT(_NAV, KC_SPC), LT(_NUM, KC_TAB),   LT(_SYM, KC_ENT), LT(_FUN, KC_BSPC), KC_DEL
  ),

  /* NAV LAYER */
  [_NAV] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                               _______, _______, _______,    KC_ENT,  KC_BSPC, KC_DEL
  ),

  /* NUM LAYER */
  [_NUM] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,
    KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX,    KC_EQL,  KC_4,    KC_5,    KC_6,    KC_0,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_MINS, KC_1,    KC_2,    KC_3,    KC_DOT,
                               _______, _______, _______,    _______, _______, _______
  ),

  /* SYM LAYER
   * Russian characters (Ё, Х, Э, Ъ) emulated on the right-hand top row
   */
  [_SYM] = LAYOUT_split_3x5_3(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,    XXXXXXX, KC_GRV,  KC_LBRC, KC_QUOT, KC_RBRC,
    KC_P,    KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,    XXXXXXX, KC_RALT, KC_RGUI, KC_RCTL, KC_RSFT,
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      KC_LPRN, KC_RPRN, KC_UNDS,    _______, _______, _______
  ),

  /* FUN LAYER */
  [_FUN] = LAYOUT_split_3x5_3(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PSCR,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_DOTA_BASE),
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   RU_TOGG,    XXXXXXX, KC_RALT, KC_RGUI, KC_RCTL, KC_RSFT,
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  CW_TOGG,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______,    _______, _______, _______
  ),

  /* DOTA BASE */
  [_DOTA_BASE] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                      MO(_DOTA_FUN), KC_H, KC_SPC,           KC_ENT,  KC_BSPC, TG(_DOTA_BASE)
  ),

  /* DOTA FUN */
  [_DOTA_FUN] = LAYOUT_split_3x5_3(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_2,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_1,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_3,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______,    _______, _______, _______
  ),

  /* SPARE - free layer to play with from the Vial GUI */
  [_SPARE] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  )
};

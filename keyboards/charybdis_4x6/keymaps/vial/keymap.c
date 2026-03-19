#include QMK_KEYBOARD_H
#include "transactions.h"

const int SCRL_TABLE[12]        = {100, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 5000, 6000, 7000};
const int DPI_TABLE[12]         = {200, 400, 600, 800, 1000, 1200, 1600, 2000, 2500, 3200, 4000, 5000};
const int DPI_RGB_TABLE[12]     = {0, 4, 8, 12, 16, 20, 29, 33, 37, 41, 45, 49};
const int SNP_DPI_RGB_TABLE[12] = {1, 5, 9, 13, 17, 21, 30, 34, 38, 42, 46, 50};
const int DRGSCRL_RGB_TABLE[12] = {2, 6, 10, 14, 18, 22, 31, 35, 39, 43, 47, 51};

uint8_t layer_buffer  = 1;
uint8_t layer_now     = 0;
bool    set_scrolling = false;

enum blender_keycode {
    B_INDSWITCH = QK_KB_0,
    B_DPIUP,
    B_DPIDN,
    B_SNPUP,
    B_SNPDN,
    B_DRGSCRL,
    B_SCRLUP,
    B_SCRLDN,
    B_SCRLX,
    B_SCRLY,
    B_RCLK_SCRL
};

typedef union {
    uint32_t raw;
    struct {
        bool    indicator_mode; // off (0) or on (1)
        uint8_t dpi_value;
        uint8_t snp_value;
        uint8_t scroll_value;
        bool    drgscrl_reverse_x;
        bool    drgscrl_reverse_y;
    };
} user_config_t;

user_config_t user_config;

typedef union {
    uint32_t raw;
    struct {
        bool    indicator_mode; // off (0) or on (1)
        uint8_t dpi_value;
        uint8_t snp_value;
        uint8_t scroll_value;
        bool    drgscrl_reverse_x;
        bool    drgscrl_reverse_y;
    };
} user_runtime_config_t;

user_runtime_config_t user_state;

void user_sync_a_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    // if buffer length matches size of data structure (simple error checking)
    if (in_buflen == sizeof(user_state)) {
        // copy data from master into local data structure
        memcpy(&user_state, in_data, in_buflen);
    }
}

void eeconfig_init_user(void) { // Writing to EEPROM default settings
    user_config.raw               = 0;
    user_config.indicator_mode    = 1; // 0-off, 1-layer indicator
    user_config.dpi_value         = 4; // default trackball dpi
    user_config.snp_value         = 2; // default sniper dpi
    user_config.scroll_value      = 4; // default sniper dpi
    user_config.drgscrl_reverse_x = 0;
    user_config.drgscrl_reverse_y = 0;
    eeconfig_update_user(user_config.raw); // Write default config to EEPROM now
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
      QK_BOOT, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,         QK_BOOT,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      XXXXXXX, KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,        KC_Y,    KC_U,         KC_I,         KC_O,         KC_QUOT,         KC_LBRC,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      XXXXXXX, LSFT_T(KC_A), LCTL_T(KC_S), LGUI_T(KC_D), LALT_T(KC_F), KC_G,        KC_H,    RALT_T(KC_J), RGUI_T(KC_K), RCTL_T(KC_L), RSFT_T(KC_SCLN), KC_P,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      XXXXXXX, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,        KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_RBRC,
  // ╰───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                       LT(5, KC_ESC), LT(3, KC_SPC), LT(6, KC_TAB), KC_BTN1, B_RCLK_SCRL,
                                                      LT(4, KC_BSPC), LT(7, KC_ENT), KC_DEL
  //                                 ╰─────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [1] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
      _______, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, _______,      _______,      _______,      _______,      _______,     _______, KC_PSCR,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, _______,      _______,      _______,      _______,      _______,     KC_CAPS, KC_LEFT,      KC_DOWN,      KC_UP,        KC_RGHT,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, _______,      _______,      _______,      _______,      _______,     KC_INS,  KC_HOME,      KC_PGDN,      KC_PGUP,      KC_END,          _______,
  // ╰───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                       _______,       _______,       _______,       KC_ENT,       KC_BSPC,
                                                      _______,       _______,       KC_DEL
  //                                 ╰─────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [2] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
      _______, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, KC_LGUI,      KC_LALT,      KC_LCTL,      KC_LSFT,      _______,     _______, KC_RSFT,      KC_RCTL,      KC_RALT,      KC_RGUI,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, _______,      _______,      EE_CLR,       QK_BOOT,      _______,     QK_BOOT, EE_CLR,       _______,      _______,      _______,         _______,
  // ╰───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                       KC_BTN2,       KC_BTN1,       KC_BTN3,       KC_BTN2,       _______,
                                                      KC_BTN1,       KC_BTN3,       _______
  //                                 ╰─────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [3] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
      _______, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, _______,      B_SCRLUP,     B_SCRLDN,     _______,      _______,     _______, KC_PSCR,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, KC_LSFT,      KC_LCTL,      KC_LGUI,      KC_LALT,      _______,     KC_CAPS, KC_LEFT,      KC_DOWN,      KC_UP,        KC_RGHT,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, B_SNPUP,      B_DPIUP,      B_DPIDN,      B_SNPDN,      _______,     KC_INS,  KC_HOME,      KC_PGDN,      KC_PGUP,      KC_END,          _______,
  // ╰───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                       _______,       _______,       _______,       KC_BSPC,       KC_DEL,
                                                      _______,       _______,       KC_ENT
  //                                 ╰─────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [4] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
      _______, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, KC_F9,        KC_F10,       KC_F11,       KC_F12,       _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, KC_F5,        KC_F6,        KC_F7,        KC_F8,        _______,     _______, KC_RALT,      KC_RGUI,      KC_RCTL,      KC_RSFT,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, KC_F1,        KC_F2,        KC_F3,        KC_F4,        _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ╰───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                       _______,       _______,       _______,       _______,       _______,
                                                      _______,       _______,       _______
  //                                 ╰─────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [5] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
      _______, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      RGB_MOD, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      RGB_TOG, KC_LSFT,      KC_LCTL,      KC_LGUI,      KC_LALT,      _______,     _______, KC_RSFT,      KC_RCTL,      KC_RALT,      KC_RGUI,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      RGB_RMOD,_______,      _______,      _______,      _______,      _______,     _______, KC_MUTE,      KC_VOLD,      KC_VOLU,      _______,         _______,
  // ╰───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                       _______,       _______,       _______,       _______,       _______,
                                                      _______,       _______,       _______
  //                                 ╰─────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [6] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
      _______, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      RGB_MOD, _______,      _______,      _______,      _______,      _______,     KC_LBRC, KC_7,         KC_8,         KC_9,         KC_RBRC,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      RGB_TOG, KC_LSFT,      KC_LCTL,      KC_LGUI,      KC_LALT,      _______,     KC_P,    KC_4,         KC_5,         KC_6,         KC_GRV,          KC_EQL,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      RGB_RMOD,_______,      _______,      _______,      _______,      _______,     KC_PLUS, KC_1,         KC_2,         KC_3,         KC_SLSH,         KC_DOT,
  // ╰───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                       _______,       _______,       _______,       _______,          _______,
                                                      KC_0,       _______,       _______
  //                                 ╰─────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [7] = LAYOUT(
  // ╭───────────────────────────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────────────────────────────╮
      _______, _______,      _______,      _______,      _______,      _______,     _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, _______,      S(KC_7),      S(KC_8),      S(KC_9),      S(KC_EQL),   _______, _______,      _______,      _______,      _______,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, S(KC_GRV),    S(KC_4),      S(KC_5),      S(KC_6),      KC_P,        _______, KC_RALT,      KC_RGUI,      KC_RCTL,      KC_RSFT,         _______,
  // ├───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────┤
      _______, S(KC_GRV),    S(KC_1),      S(KC_2),      S(KC_3),      S(KC_P),     _______, _______,      _______,      _______,      _______,         _______,
  // ╰───────────────────────────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────────────────────────────╯
                                       _______,       _______,       S(KC_0),       S(KC_MINS),    S(KC_BSLS),
                                                      _______,    _______,       _______
  //                                 ╰─────────────────────────────────────────────╯ ╰────────────────────────────────╯
  ),

  [8] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [9] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [10] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [11] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [12] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [13] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [14] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  ),
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (user_config.indicator_mode==1) {
            for (uint8_t i = 0; i < 56; i++) {
                switch(get_highest_layer(layer_state|default_layer_state)) {
                    case 5:
                        {
			rgb_matrix_set_color(i, 0, 255*rgb_matrix_get_val()/256, 255*rgb_matrix_get_val()/256);
			break;
			}
                    case 6:
                        {
			rgb_matrix_set_color(i, 0,255*rgb_matrix_get_val()/256, 0);
                        break;
			}
                    case 4:
                        {
			rgb_matrix_set_color(i, 255*rgb_matrix_get_val()/256, 255*rgb_matrix_get_val()/256, 255*rgb_matrix_get_val()/256);
                        break;
			}
                    case 3:
                        {
			rgb_matrix_set_color(i, 255*rgb_matrix_get_val()/256, 0, 0);
			if (is_keyboard_left()) { //dpi indicator
				for (int i_pos = 0; i_pos<=user_config.dpi_value;i_pos++)
					rgb_matrix_set_color(DPI_RGB_TABLE[i_pos],255,255,255);
			}
			else
			{
				if (user_config.dpi_value>5)
				for (int i_pos = 6; i_pos<=user_config.dpi_value;i_pos++)
					rgb_matrix_set_color(DPI_RGB_TABLE[i_pos],255,255,255);
			}
			if (is_keyboard_left()) { //snp indicator
				for (int i_pos = 0; i_pos<=user_config.snp_value;i_pos++)
					rgb_matrix_set_color(SNP_DPI_RGB_TABLE[i_pos],0,255,0);
			}
			else
			{
				if (user_config.snp_value>5)
				for (int i_pos = 6; i_pos<=user_config.snp_value;i_pos++)
					rgb_matrix_set_color(SNP_DPI_RGB_TABLE[i_pos],0,255,0);
			}
			if (is_keyboard_left()) { //drgscrl indicator
				for (int i_pos = 0; i_pos<=user_config.scroll_value;i_pos++)
					rgb_matrix_set_color(DRGSCRL_RGB_TABLE[i_pos],0,0,255);
			}
			else
			{
				if (user_config.scroll_value>5)
				for (int i_pos = 6; i_pos<=user_config.scroll_value;i_pos++)
					rgb_matrix_set_color(DRGSCRL_RGB_TABLE[i_pos],0,0,255);
			}

                        break;
			}
                    case 2:
                        {
			rgb_matrix_set_color(i, 255*rgb_matrix_get_val()/256, 255*rgb_matrix_get_val()/256, 0);
                        break;
			}
                    case 1:
			{
			rgb_matrix_set_color(i, 0,255*rgb_matrix_get_val()/256, 0);
                        break;
			}
                    case 0:
			{
                        break;
			}
                }
            }
        }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t rmb_timer;
	switch (keycode) {
	case B_INDSWITCH:
            if (record->event.pressed) {
		user_config.indicator_mode=!user_config.indicator_mode;
                eeconfig_update_user(user_config.raw);
            }
            return 0;
        case B_DPIUP:
            if (record->event.pressed) {
                if (user_config.dpi_value<=10)
                    user_config.dpi_value+=1;
                else
                    user_config.dpi_value=11;
		pointing_device_set_cpi(DPI_TABLE[user_config.dpi_value]);
                eeconfig_update_user(user_config.raw);
            }
            return 0;
        case B_DPIDN:
            if (record->event.pressed) {
                if (user_config.dpi_value>=1)
                    user_config.dpi_value-=1;
                else
                    user_config.dpi_value=0;
		pointing_device_set_cpi(DPI_TABLE[user_config.dpi_value]);
                eeconfig_update_user(user_config.raw);
            }
            return 0;
	case B_SNPUP:
            if (record->event.pressed) {
                if (user_config.snp_value<=10)
                    user_config.snp_value+=1;
                else
                    user_config.snp_value=11;
		eeconfig_update_user(user_config.raw);
            }
            return 0;
	case B_SNPDN:
            if (record->event.pressed) {
                if (user_config.snp_value>=1)
                    user_config.snp_value-=1;
                else
                    user_config.snp_value=0;
		eeconfig_update_user(user_config.raw);
            }
            return 0;
	case B_DRGSCRL:{
            set_scrolling = record->event.pressed;
            break;
	    }
	case B_SCRLDN:
            if (record->event.pressed) {
                if (user_config.scroll_value>=1)
                    user_config.scroll_value-=1;
                else
                    user_config.scroll_value=0;
		eeconfig_update_user(user_config.raw);
            }
            return 0;
	case B_SCRLUP:
            if (record->event.pressed) {
                if (user_config.scroll_value<=10)
                    user_config.scroll_value+=1;
                else
                    user_config.scroll_value=11;
		eeconfig_update_user(user_config.raw);
            }
            return 0;
	case B_SCRLX:
            if (record->event.pressed) {
                user_config.drgscrl_reverse_x=!user_config.drgscrl_reverse_x;
		eeconfig_update_user(user_config.raw);
            }
            return 0;
	case B_SCRLY:
            if (record->event.pressed) {
                user_config.drgscrl_reverse_y=!user_config.drgscrl_reverse_y;
		eeconfig_update_user(user_config.raw);
            }
            return 0;
    case B_RCLK_SCRL:
        if (record->event.pressed) {
            rmb_timer = timer_read();
            set_scrolling = true;
        } else {
            set_scrolling = false;
            if (timer_elapsed(rmb_timer) < TAPPING_TERM) {
                tap_code16(KC_BTN2);
            }
        }
        return 0;
	}
return 1;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

void housekeeping_task_user(void) {
    if (set_scrolling)
	{
	if (layer_buffer!=16){
		pointing_device_set_cpi(SCRL_TABLE[user_config.scroll_value]);
		layer_buffer = 16;}
	}
    else{
    	layer_now=get_highest_layer(layer_state|default_layer_state);
    	if (layer_buffer!=layer_now)
		{
	   	if (layer_now==3)
			pointing_device_set_cpi(DPI_TABLE[user_config.snp_value]);
	   	else
	   		pointing_device_set_cpi(DPI_TABLE[user_config.dpi_value]);
	   	layer_buffer=layer_now;
		}
	}
    if (is_keyboard_master()) {

// update values
        // copy local variable to sync data structure
        user_state.dpi_value = user_config.dpi_value;
	user_state.snp_value = user_config.snp_value;
	user_state.indicator_mode = user_config.indicator_mode;
        user_state.scroll_value = user_config.scroll_value;
// sync values
        static uint32_t last_sync = 0;
        static user_runtime_config_t last_user_state;
        static bool needs_sync = false;

        // if value is different, then needs syncing
        if (memcmp(&user_state, &last_user_state, sizeof(user_state))) {
            needs_sync = true;
            // copy local user state to verify changes
            memcpy(&last_user_state, &user_state, sizeof(user_state));
        }
        // Send to slave every 250ms regardless of state change
        if (timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
        }

        // if it needs syncing:
        if (needs_sync) {
            // send user_data stuct over to slave
            if(transaction_rpc_send(USER_SYNC_A, sizeof(user_state), &user_state)) {
                // reset sync checks
                last_sync = timer_read32();
                needs_sync = false;
            }
        }

    } else { // not master:
        // copy value from data structure to local variable
        user_config.dpi_value = user_state.dpi_value;
	user_config.snp_value = user_state.snp_value;
	user_config.indicator_mode = user_state.indicator_mode;
	user_config.scroll_value = user_state.scroll_value;
    }
}

void keyboard_post_init_user(void) {
  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();
  transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}

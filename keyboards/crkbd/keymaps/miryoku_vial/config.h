/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

/* ---------------------------------------------------------------- Vial -- */

/* Generate your OWN uid, do not reuse the Charybdis one:
 *   python3 util/vial_generate_keyboard_uid.py
 */
#define VIAL_KEYBOARD_UID {0xDD, 0x00, 0x2B, 0x62, 0x14, 0xBF, 0xAB, 0x53}

/* Unlock combo = the two outer-column keys on the left half, rows 0 and 1
 * (matrix [0][0] and [1][0]). Both are XXXXXXX in your keymap, so holding
 * them types nothing. Vial reads the raw matrix, keycodes don't matter. */
#define VIAL_UNLOCK_COMBO_ROWS { 1, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }

/* ------------------------------------------------------- dynamic keymap -- */

/* Must match the number of layers defined in keymap.c */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define DYNAMIC_KEYMAP_MACRO_COUNT 16

/* ------------------------------------- EEPROM (RP2040 wear levelling) --- */

/* The promicro_rp2040 defaults are too small once Vial stores 8 layers plus
 * combos / tap-dance / macros / QMK settings. Backing must be a multiple of
 * the 4K flash sector and at least 2x the logical size. */
#undef WEAR_LEVELING_LOGICAL_SIZE
#define WEAR_LEVELING_LOGICAL_SIZE (4 * 1024)
#undef WEAR_LEVELING_BACKING_SIZE
#define WEAR_LEVELING_BACKING_SIZE (16 * 1024)

/* ------------------------------------------------------------ tap-hold -- */

/* Just the boot default now: with QMK_SETTINGS = yes, tapping term,
 * permissive hold, hold-on-other-key-press, quick tap etc. are all
 * adjustable at runtime from Vial's "QMK Settings" tab. */
#define TAPPING_TERM 200

#define SPLIT_LAYER_STATE_ENABLE
#define OLED_TIMEOUT 60000

/* IGNORE_MOD_TAP_INTERRUPT no longer exists in modern QMK. The closest
 * equivalents (Permissive Hold / Hold On Other Key Press) are toggles in
 * the Vial GUI, so leave them out of here and tune them live. */

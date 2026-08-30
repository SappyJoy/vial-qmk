/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

/* ---------------------------------------------------------------- Vial -- */
/* Generated a new UID specifically for your Cheapino */
#define VIAL_KEYBOARD_UID {0x4E, 0x1A, 0x98, 0xC3, 0x51, 0xDE, 0xF0, 0x77}

/* Unlock combo = left half, rows 0 and 1, column 0 */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }

/* ------------------------------------------------------- dynamic keymap -- */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define DYNAMIC_KEYMAP_MACRO_COUNT 16

/* ------------------------------------- EEPROM (RP2040 wear levelling) --- */
#undef WEAR_LEVELING_LOGICAL_SIZE
#define WEAR_LEVELING_LOGICAL_SIZE (4 * 1024)
#undef WEAR_LEVELING_BACKING_SIZE
#define WEAR_LEVELING_BACKING_SIZE (16 * 1024)

/* ------------------------------------------------------------ tap-hold -- */
#define TAPPING_TERM 200
#define SPLIT_LAYER_STATE_ENABLE

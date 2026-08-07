# --- Vial ---------------------------------------------------------------
VIA_ENABLE  = yes
VIAL_ENABLE = yes

# Runtime tuning of tapping term / permissive hold / auto shift in the GUI.
# This is the main reason you want Vial with home row mods.
QMK_SETTINGS     = yes

TAP_DANCE_ENABLE   = yes
COMBO_ENABLE       = yes
KEY_OVERRIDE_ENABLE = yes
CAPS_WORD_ENABLE   = yes

LTO_ENABLE = no

# --- Hardware -----------------------------------------------------------
# Replaces the old keymap.json {"converter": "promicro_rp2040"}.
CONVERT_TO = promicro_rp2040

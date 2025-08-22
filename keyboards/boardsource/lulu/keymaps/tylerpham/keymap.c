// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────────────────────
// Homerow mods with automatic OS-specific Control/GUI swapping
// ─────────────────────────────────────────────────────────────────────────────
// Windows/Linux (automatic): F=CTRL, J=CTRL, A=CMD, ;=CMD
// macOS/iOS (automatic):     F=CMD,  J=CMD,  A=CTRL, ;=CTRL
// 
// The keyboard automatically detects the OS and swaps the modifiers accordingly.
// Manual toggle available: Lower+Raise → Q key (CG_TOGG) for manual override.
//
// Caps Word: Press both shift keys simultaneously to activate Caps Word.
// While active, letters are capitalized and '-' becomes '_'. 
// Caps Word automatically turns off after typing a space or punctuation.
//
// Space Cadet Shifts: Left shift tapped = '[', Right shift tapped = ']'
// When held, they function as normal shift keys for homerow mods and shortcuts.
//
#define HM_A     LGUI_T(KC_A)
#define HM_S     LALT_T(KC_S)
#define HM_D     LSFT_T(KC_D)
#define HM_F     LCTL_T(KC_F)

#define HM_J     RCTL_T(KC_J)
#define HM_K     RSFT_T(KC_K)
#define HM_L     LALT_T(KC_L)
#define HM_SCLN  RGUI_T(KC_SCLN)

// ─────────────────────────────────────────────────────────────────────────────
// Layers
// ─────────────────────────────────────────────────────────────────────────────
enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
    // _RAISE2,
    // _LOWER2,
    _ADJUST
};

// ─────────────────────────────────────────────────────────────────────────────
// Combos
// ─────────────────────────────────────────────────────────────────────────────
enum combo_events {
    ZX_CUT,
    XC_COPY,
    CV_PASTE,
};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};

combo_t key_combos[] = {
    [ZX_CUT] = COMBO(zx_combo, C(KC_X)),
    [XC_COPY] = COMBO(xc_combo, C(KC_C)),
    [CV_PASTE] = COMBO(cv_combo, C(KC_V)),
};

uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);

// ─────────────────────────────────────────────────────────────────────────────
// Keymaps
// ─────────────────────────────────────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  =   |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |  E   |  R   |  T   |                    |  Y   |  U   |  I   |  O   |  P   |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |GUI/A |ALT/S |SFT/D |CTL/F |  G   |-------.    ,-------|  H   |CTL/J |SFT/K |ALT/L |GUI/; |  '   |
 * |------+------+------+------+------+------|  [    |    |   ]   |------+------+------+------+------+------|
 * |Sft/[ |  Z   |  X   |  C   |  V   |  B   |-------|    |-------|  N   |  M   |  ,   |  .   |  /   |Sft/] |
 * `-----------------------------------------/       /     \     \-----------------------------------------'
 *                  | LAlt |Lower/Esc|Bspc  | / Del  /        \Enter\  |Space |Raise/Tab| RGUI |
 *                  |      |         |      |/       /          \     \ |      |         |      |
 *                  `-----------------------'         '-------------------------'
 */
[_QWERTY] = LAYOUT(
    KC_EQUAL,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
    KC_ESC,   HM_A,    HM_S,    HM_D,    HM_F,    KC_G,                       KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,
    SC_LSPO,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
                               KC_LALT,  LT(_LOWER2, KC_ESC), KC_BSPC, KC_DEL,  KC_ENT, KC_SPC,  LT(_RAISE2, KC_TAB), KC_RGUI
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |  ^   |  {   |  }   |  $   |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|  #   |  (   |  )   |  ;   |  "   |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|  @   |  :   |  ,   |  .   |  '   |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                  |      |      |      | /       /        \      \ |      |      |      |
 *                  |      |      |      |/       /          \      \|      |      |      |
 *                  `----------------------------'            '--------------------'
 */
[_LOWER2] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQUO, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_AT,   KC_COLN, KC_COMM, KC_DOT,  KC_QUOT, XXXXXXX,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  `   |  <   |  >   |  -   |  |   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  !   |  *   |  /   |  =   |  &   |-------.    ,-------|      | LEFT | DOWN | UP   |RIGHT |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  ~   |  +   |  [   |  ]   |  %   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                  |      |      |      | /       /        \      \ |      |      |      |
 *                  |      |      |      |/       /          \      \|      |      |      |
 *                  `----------------------------'            '--------------------'
 */
[_RAISE2] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_GRV,  KC_LABK, KC_RABK, KC_MINS, KC_PIPE,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL,  KC_AMPR,                   KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | MAKE |BOOTLDR|   `   |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |CG_TOG|      |      |      |      |      |                    |      | PREV | PLAY | NEXT |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | VOL- | MUTE | VOL+ |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                  |      |      |      | /       /        \      \ |      |      |      |
 *                  |      |      |      |/       /          \      \|      |      |      |
 *                  `----------------------------'            '--------------------'
 */
[_ADJUST] = LAYOUT(
    QK_MAKE, QK_BOOTLOADER, KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* RAISE2 - Left side numbers and symbols for left-hand access
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  1   |  2   |  3   |  4   |  5   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  !   |  @   |  #   |  $   |  %   |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                  |      |      |      | /       /        \      \ |      |      |      |
 *                  |      |      |      |/       /          \      \|      |      |      |
 *                  `----------------------------'            '--------------------'
 */
[_RAISE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_EQUAL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* LOWER2 - Right side numbers and symbols for right-hand access
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |  6   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|  ^   |  &   |  *   |  (   |  )   |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                  |      |      |      | /       /        \      \ |      |      |      |
 *                  |      |      |      |/       /          \      \|      |      |      |
 *                  `----------------------------'            '--------------------
 */
[_LOWER] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_GRV,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

};

// ─────────────────────────────────────────────────────────────────────────────
// Tri-layer handling
// ─────────────────────────────────────────────────────────────────────────────
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// ─────────────────────────────────────────────────────────────────────────────
// OS Detection - Automatic Control/GUI swapping
// ─────────────────────────────────────────────────────────────────────────────
#ifdef OS_DETECTION_ENABLE
uint32_t check_os_and_swap_mods(uint32_t trigger_time, void *cb_arg) {
    os_variant_t detected_os = detected_host_os();
    
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            // macOS detected - swap Control/GUI so F=CMD, J=CMD, A=CTRL, ;=CTRL
            keymap_config.swap_lctl_lgui = true;
            keymap_config.swap_rctl_rgui = true;
            return 0; // Detection complete, don't retry
            
        case OS_WINDOWS:
        case OS_LINUX:
            // Windows/Linux detected - keep default F=CTRL, J=CTRL, A=CMD, ;=CMD
            keymap_config.swap_lctl_lgui = false;
            keymap_config.swap_rctl_rgui = false;
            return 0; // Detection complete, don't retry
            
        case OS_UNSURE:
            return 500; // OS not yet detected, retry in 500ms
    }
    
    return 0;
}

void keyboard_post_init_user(void) {
    // Start OS detection after 200ms to allow USB initialization
    defer_exec(200, check_os_and_swap_mods, NULL);
}
#endif

/* Custom RGB matrix effects for showing the selected BT host.
   Cycle to them via RGB_MOD (Fn+R on this keymap).

     HOST_SOLO - only the selected device's key (1/2/3) is lit in its color,
                 everything else off.
     HOST_ALL  - every LED on the keyboard is lit in the selected device's color.

   State is owned by keymap.c:
     current_bt_host  0 = none, 1..3 = selected BT host
     host_led_idx[]   RGB matrix indices for host LEDs (keys 1, 2, 3)
     host_rgb[][3]    per-host colors (red / blue / yellow) */

RGB_MATRIX_EFFECT(HOST_SOLO)
RGB_MATRIX_EFFECT(HOST_ALL)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern uint8_t       current_bt_host;
extern const uint8_t host_led_idx[3];
extern const uint8_t host_rgb[3][3];

static bool HOST_SOLO(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
    if (current_bt_host >= 1 && current_bt_host <= 3) {
        uint8_t h   = current_bt_host - 1;
        uint8_t idx = host_led_idx[h];
        if (idx >= led_min && idx < led_max) {
            rgb_matrix_set_color(idx, host_rgb[h][0], host_rgb[h][1], host_rgb[h][2]);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool HOST_ALL(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t r = 0, g = 0, b = 0;
    if (current_bt_host >= 1 && current_bt_host <= 3) {
        uint8_t h = current_bt_host - 1;
        r = host_rgb[h][0];
        g = host_rgb[h][1];
        b = host_rgb[h][2];
    }
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

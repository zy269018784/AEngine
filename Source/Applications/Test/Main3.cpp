#include "lvgl/lvgl.h"#include <lvgl/src/drivers/lv_drivers.h>
#include <lvgl/src/drivers/windows/lv_windows_display.h>

int main() {
    lv_init();
     lv_display_t * Display = lv_windows_create_display(
        L"Milkyway Keyboard",
        480,
        480,
        100,
        false,
        true);

    lv_obj_t* ActiveScreen = lv_screen_active();


    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        lv_delay_ms(time_till_next);
    }
}
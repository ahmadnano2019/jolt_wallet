#ifndef JOLT_GUI_MENUS_SETTINGS_SUBMENUS_H__
#define JOLT_GUI_MENUS_SETTINGS_SUBMENUS_H__

#include "lvgl/lvgl.h"

lv_res_t menu_wifi_create(lv_obj_t *btn);
lv_res_t menu_wifi_details_create(lv_obj_t *btn);

lv_res_t menu_screen_brightness_create();
lv_res_t menu_led_brightness_create();
lv_res_t menu_language_create(lv_obj_t *btn);
lv_res_t menu_factory_reset_create(lv_obj_t *btn);

lv_res_t menu_bluetooth_create(lv_obj_t *btn);
lv_res_t menu_bluetooth_pair_create(lv_obj_t *btn);
lv_res_t menu_bluetooth_temp_pair_create(lv_obj_t *btn);
lv_res_t menu_bluetooth_unbond_create(lv_obj_t *btn);

lv_res_t menu_storage_create( lv_obj_t *btn );

#endif

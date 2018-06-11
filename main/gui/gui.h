/* Jolt Wallet - Open Source Cryptocurrency Hardware Wallet
 Copyright (C) 2018  Brian Pugh, James Coxon, Michael Smaili
 https://www.joltwallet.com/
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software Foundation,
 Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */


#ifndef __JOLT_GUI_H__
#define __JOLT_GUI_H__

#include "../globals.h"
#include "u8g2.h"
#include "menu8g2.h"

void setup_screen(u8g2_t *u8g2);
void gui_task();

#define FULLSCREEN_ENTER(menu) \
    (menu)->post_draw = NULL; \
    bool statusbar_draw_original = statusbar_draw_enable; \
    statusbar_draw_enable = false;

#define FULLSCREEN_EXIT(menu) \
    statusbar_draw_enable = statusbar_draw_original;

#define SCREEN_SAVE \
    size_t disp_buffer_size = 8 * u8g2_GetBufferTileHeight(&u8g2) * \
            u8g2_GetBufferTileWidth((u8g2_t *)&u8g2);\
    uint8_t *old_disp_buffer = malloc(disp_buffer_size);\
    memcpy(old_disp_buffer, u8g2_GetBufferPtr((u8g2_t *)&u8g2), disp_buffer_size);

#define SCREEN_RESTORE \
    xSemaphoreTake(disp_mutex, portMAX_DELAY); \
    memcpy(u8g2_GetBufferPtr((u8g2_t *)&u8g2), old_disp_buffer, disp_buffer_size); \
    u8g2_SendBuffer((u8g2_t *)&u8g2); \
    xSemaphoreGive(disp_mutex); \
    free(old_disp_buffer);

#define SCREEN_MUTEX_TAKE \
    xSemaphoreTake(disp_mutex, portMAX_DELAY);
#define SCREEN_MUTEX_GIVE \
    xSemaphoreGive(disp_mutex);


#endif
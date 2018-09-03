/* Jolt Wallet - Open Source Cryptocurrency Hardware Wallet
 Copyright (C) 2018  Brian Pugh, James Coxon, Michael Smaili
 https://www.joltwallet.com/
 */

#ifndef __JOLT_GRAPHICS_H__
#define __JOLT_GRAPHICS_H__

#include "u8g2.h"

#define GRAPHIC_JOLT_H 48
#define GRAPHIC_JOLT_W 120
extern const unsigned char graphic_jolt[];

#define GRAPHIC_WIFI_H 7
#define GRAPHIC_WIFI_W 9
extern const unsigned char graphic_wifi_1[];
extern const unsigned char graphic_wifi_2[];
extern const unsigned char graphic_wifi_3[];

#define GRAPHIC_BLUETOOTH_H 9
#define GRAPHIC_BLUETOOTH_W 6
extern const unsigned char graphic_bluetooth[];

#define GRAPHIC_BATTERY_H 7
#define GRAPHIC_BATTERY_W 13
extern const unsigned char graphic_battery_0[];
extern const unsigned char graphic_battery_1[];
extern const unsigned char graphic_battery_2[];
extern const unsigned char graphic_battery_3[];

#define GRAPHIC_PENDING_H 7
#define GRAPHIC_PENDING_W 9
extern const unsigned char graphic_pending[];

#define GRAPHIC_NANO_LOAD_H 32
#define GRAPHIC_NANO_LOAD_W 70
#define GRAPHIC_NANO_LOAD_F 44
extern const unsigned char graphic_nano_load[GRAPHIC_NANO_LOAD_F][288];


void boot_splash();

#endif

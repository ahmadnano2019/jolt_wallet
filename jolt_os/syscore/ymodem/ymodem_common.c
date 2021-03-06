/*
 * ESP32 YModem driver
 *
 * Copyright (C) LoBo 2017
 *
 * Author: Boris Lovosevic (loboris@gmail.com)
 *
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaim all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.    In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 */

//#define LOG_LOCAL_LEVEL 4

#include "syscore/ymodem/ymodem_common.h"
#include <driver/uart.h>
#include <esp_timer.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/select.h>
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_dev.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/radio/bluetooth.h"
#include "jolt_helpers.h"
#include "syscore/ymodem.h"

#if CONFIG_JOLT_BT_YMODEM_PROFILING
uint64_t t_ble_read_timeout      = 0;
bool ymodem_transfer_in_progress = false;
#endif

unsigned short crc16( const unsigned char *buf, unsigned long count )
{
    unsigned short crc = 0;
    int i;

    while( count-- ) {
        crc = crc ^ *buf++ << 8;

        for( i = 0; i < 8; i++ ) {
            if( crc & 0x8000 )
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        }
    }
    return crc;
}

/***
 * @param[out] c Pointer to output buffer array.
 * @param[in] timeout Milliseconds to wait before returning.
 * @param[in] n number of bytes to read.
 * @return Amount of bytes actually read.
 */
int32_t receive_bytes( unsigned char *c, uint32_t timeout, uint32_t n )
{
    int return_code = 0;
    int amount_read = 0;
#if CONFIG_JOLT_BT_YMODEM_PROFILING
    uint64_t t_start = esp_timer_get_time();
#endif
    if( stdin == ble_stdin ) {
        /* Temporary hack in lieu of writing proper bluetooth select drivers */
#if CONFIG_JOLT_BT_YMODEM_PROFILING
        if( ymodem_transfer_in_progress ) t_ble_read_timeout -= esp_timer_get_time();
#endif
        amount_read = ble_read_timeout( 0, c, n, timeout / portTICK_PERIOD_MS );
#if CONFIG_JOLT_BT_YMODEM_PROFILING
        if( ymodem_transfer_in_progress ) t_ble_read_timeout += esp_timer_get_time();
#endif

        if( amount_read > 0 ) {
            BLE_UART_LOGD( "Read in %d bytes: \"", amount_read );
            BLE_UART_LOGD_BUF( (char *)c, amount_read );
            BLE_UART_LOGD_STR( "\"" );
            if( 1 == amount_read ) BLE_UART_LOGD( " Ascii: 0x%02x", (int)c[0] );
            BLE_UART_LOGD_STR( "\n" );
        }
        if( amount_read != n ) {
            BLE_UART_LOGD( "Only read %d/%d bytes\n", amount_read, n );
            EXIT( -1 );
        }
    }
    else {
        do {
            int s;
            fd_set rfds;
            struct timeval tv = {
                    .tv_sec  = timeout / 1000,
                    .tv_usec = ( timeout % 1000 ) * 1000,
            };

            FD_ZERO( &rfds );
            FD_SET( fileno( stdin ), &rfds );

            s = select( fileno( stdin ) + 1, &rfds, NULL, NULL, &tv );

            if( s < 0 ) {
                // Select Failure
                EXIT( -1 );
            }
            else if( s == 0 ) {
                // timed out
                EXIT( -1 );
            }
            else {
                amount_read += fread( c, 1, n - amount_read, stdin );
            }
        } while( amount_read < n );
    }
    return amount_read;

exit:
#if CONFIG_JOLT_BT_YMODEM_PROFILING
    t_ymodem_receive += esp_timer_get_time() - t_start;
#endif
    return return_code;
}

void rx_consume()
{
    if( stdin == ble_stdin ) {
        /* Temporary hack in lieu of writing proper bluetooth select drivers */
        BLE_UART_LOGD( "%d) CONSUMING{", __LINE__ );
        char c;
        int amount_read = 0;
        do {
            amount_read = ble_read_timeout( 0, &c, 1, 10 / portTICK_PERIOD_MS );
        } while( amount_read > 0 );
        BLE_UART_LOGD( "%d) }CONSUMED", __LINE__ );
    }
    else {
        fflush( stdin );
    }
}

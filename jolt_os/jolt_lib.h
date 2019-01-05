#ifndef __JOLT_LIB_H__
#define __JOLT_LIB_H__

/* All of the functions available to an app */

#include "jelfloader.h"

#include "bipmnemonic.h"
#include "cJSON.h"
#include "driver/uart.h"
#include "esp_console.h"
#include "esp_log.h"
#include "esp_vfs_dev.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "linenoise/linenoise.h"
#include "math.h"
#include "mbedtls/bignum.h"
#include "nano_rest.h"
#include "qrcode.h"
#include "sodium.h"
#include "sodium/crypto_verify_32.h"
#include "sodium/private/curve25519_ref10.h"

#include "console.h"
#include "hal/storage/storage.h"
#include "hal/display.h"
#include "jolt_helpers.h"
#include "jolt_gui/jolt_gui.h"
#include "syscore/filesystem.h"
#include "vault.h"
#include "syscore/console_helpers.h"


#include "esp_http_client.h" // todo: replace with less open functions

typedef enum release_type_t {
    JOLT_VERSION_RELEASE = 0,
    JOLT_VERSION_DEV = 1,
} release_type_t;

typedef struct jolt_version_t {
    union {
        struct {
            uint8_t major;
            uint8_t minor;
            uint8_t patch;
        };
        uint32_t version; // For easy comparison
    };
    release_type_t release;
} jolt_version_t;

extern const jolt_version_t JOLT_VERSION;

//extern const jolt_version_t JOLT_VERSION;

#if JOLT_OS

extern void *__floatsidf;
extern void *__gtdf2;
extern void *__ltdf2;
extern void *__muldf3;
extern void *__stack_chk_fail;
extern void *__stack_chk_guard;

#define EXPORT_SYMBOL(x) &x

/* This order is very important; only *append* fuctions */
static const void *exports[] = {
    EXPORT_SYMBOL( __floatsidf ),
    EXPORT_SYMBOL( __gtdf2 ),
    EXPORT_SYMBOL( __ltdf2 ),
    EXPORT_SYMBOL( __muldf3 ),
    EXPORT_SYMBOL( __stack_chk_fail ),
    EXPORT_SYMBOL( __stack_chk_guard ),
    EXPORT_SYMBOL( _esp_error_check_failed ),
    EXPORT_SYMBOL( atoi ),
    EXPORT_SYMBOL( atol ),
    EXPORT_SYMBOL( bm_entropy256 ),
    EXPORT_SYMBOL( cJSON_Delete ),
    EXPORT_SYMBOL( cJSON_GetObjectItemCaseSensitive ),
    EXPORT_SYMBOL( cJSON_IsString ),
    EXPORT_SYMBOL( cJSON_Parse ),
    EXPORT_SYMBOL( cJSON_Print ),
    EXPORT_SYMBOL( console_check_equal_argc ),
    EXPORT_SYMBOL( console_check_range_argc ),
    EXPORT_SYMBOL( crypto_core_curve25519_ref10_ge_double_scalarmult_vartime ),
    EXPORT_SYMBOL( crypto_core_curve25519_ref10_ge_frombytes_negate_vartime ),
    EXPORT_SYMBOL( crypto_core_curve25519_ref10_ge_p3_tobytes ),
    EXPORT_SYMBOL( crypto_core_curve25519_ref10_ge_p3_tobytes ),
    EXPORT_SYMBOL( crypto_core_curve25519_ref10_ge_scalarmult_base ),
    EXPORT_SYMBOL( crypto_core_curve25519_ref10_ge_tobytes ),
    EXPORT_SYMBOL( crypto_core_curve25519_ref10_sc_muladd ),
    EXPORT_SYMBOL( crypto_core_curve25519_ref10_sc_reduce ),
    EXPORT_SYMBOL( crypto_generichash ),
    EXPORT_SYMBOL( crypto_generichash_blake2b ),
    EXPORT_SYMBOL( crypto_generichash_blake2b_final ),
    EXPORT_SYMBOL( crypto_generichash_blake2b_init ),
    EXPORT_SYMBOL( crypto_generichash_blake2b_update ),
    EXPORT_SYMBOL( crypto_generichash_final ),
    EXPORT_SYMBOL( crypto_generichash_init ),
    EXPORT_SYMBOL( crypto_generichash_update ),
    EXPORT_SYMBOL( crypto_hash_sha512_final ),
    EXPORT_SYMBOL( crypto_hash_sha512_init ),
    EXPORT_SYMBOL( crypto_hash_sha512_update ),
    EXPORT_SYMBOL( crypto_verify_32 ),
    EXPORT_SYMBOL( esp_console_deinit ),
    EXPORT_SYMBOL( esp_console_init ),
    EXPORT_SYMBOL( esp_err_to_name ),
    EXPORT_SYMBOL( esp_http_client_cleanup ),
    EXPORT_SYMBOL( esp_http_client_get_content_length ),
    EXPORT_SYMBOL( esp_http_client_get_status_code ),
    EXPORT_SYMBOL( esp_http_client_init ),
    EXPORT_SYMBOL( esp_http_client_perform ),
    EXPORT_SYMBOL( esp_http_client_set_method ),
    EXPORT_SYMBOL( esp_http_client_set_post_field ),
    EXPORT_SYMBOL( esp_log_timestamp ),
    EXPORT_SYMBOL( esp_log_write ),
    EXPORT_SYMBOL( esp_restart ),
    EXPORT_SYMBOL( free ),
    EXPORT_SYMBOL( get_display_brightness ),
    EXPORT_SYMBOL( hd_node_copy ),
    EXPORT_SYMBOL( hd_node_iterate ),
    EXPORT_SYMBOL( heap_caps_calloc ),
    EXPORT_SYMBOL( jolt_gui_debug_obj_print ),
    EXPORT_SYMBOL( jolt_gui_num_create ),
    EXPORT_SYMBOL( jolt_gui_num_get_arr ),
    EXPORT_SYMBOL( jolt_gui_num_set_back_action ),
    EXPORT_SYMBOL( jolt_gui_num_set_decimal ),
    EXPORT_SYMBOL( jolt_gui_num_set_enter_action ),
    EXPORT_SYMBOL( jolt_gui_num_set_len ),
    EXPORT_SYMBOL( jolt_gui_obj_title_create ),
    EXPORT_SYMBOL( jolt_gui_parent_create ),
    EXPORT_SYMBOL( jolt_gui_scr_del ),
    EXPORT_SYMBOL( jolt_gui_scr_loading_create ),
    EXPORT_SYMBOL( jolt_gui_scr_loading_update ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_add ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_create ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_get_list ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_set_btn_selected ),
    EXPORT_SYMBOL( jolt_gui_scr_num_create ),
    EXPORT_SYMBOL( jolt_gui_scr_num_get ),
    EXPORT_SYMBOL( jolt_gui_scr_qr_create ),
    EXPORT_SYMBOL( jolt_gui_scr_set_back_action ),
    EXPORT_SYMBOL( jolt_gui_scr_set_enter_action ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_create ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_get_slider ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_get_value ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_set_range ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_set_value ),
    EXPORT_SYMBOL( jolt_gui_scr_text_create ),
    EXPORT_SYMBOL( jolt_gui_sem_give ),
    EXPORT_SYMBOL( jolt_gui_sem_take ),
    EXPORT_SYMBOL( jolt_gui_send_enter_main ),
    EXPORT_SYMBOL( jolt_gui_send_left_main ),
    EXPORT_SYMBOL( linenoise ),
    EXPORT_SYMBOL( lv_btn_create ),
    EXPORT_SYMBOL( lv_btn_get_action ),
    EXPORT_SYMBOL( lv_btn_get_hor_fit ),
    EXPORT_SYMBOL( lv_btn_get_layout ),
    EXPORT_SYMBOL( lv_btn_get_state ),
    EXPORT_SYMBOL( lv_btn_get_style ),
    EXPORT_SYMBOL( lv_btn_get_toggle ),
    EXPORT_SYMBOL( lv_btn_get_ver_fit ),
    EXPORT_SYMBOL( lv_btn_set_action ),
    EXPORT_SYMBOL( lv_btn_set_fit ),
    EXPORT_SYMBOL( lv_btn_set_layout ),
    EXPORT_SYMBOL( lv_btn_set_state ),
    EXPORT_SYMBOL( lv_btn_set_style ),
    EXPORT_SYMBOL( lv_btn_set_toggle ),
    EXPORT_SYMBOL( lv_btn_toggle ),
    EXPORT_SYMBOL( lv_cont_create ),
    EXPORT_SYMBOL( lv_cont_get_hor_fit ),
    EXPORT_SYMBOL( lv_cont_get_layout ),
    EXPORT_SYMBOL( lv_cont_get_style ),
    EXPORT_SYMBOL( lv_cont_get_ver_fit ),
    EXPORT_SYMBOL( lv_cont_set_fit ),
    EXPORT_SYMBOL( lv_cont_set_layout ),
    EXPORT_SYMBOL( lv_cont_set_style ),
    EXPORT_SYMBOL( lv_label_create ),
    EXPORT_SYMBOL( lv_label_cut_text ),
    EXPORT_SYMBOL( lv_label_get_align ),
    EXPORT_SYMBOL( lv_label_get_anim_speed ),
    EXPORT_SYMBOL( lv_label_get_body_draw ),
    EXPORT_SYMBOL( lv_label_get_letter_on ),
    EXPORT_SYMBOL( lv_label_get_letter_pos ),
    EXPORT_SYMBOL( lv_label_get_long_mode ),
    EXPORT_SYMBOL( lv_label_get_style ),
    EXPORT_SYMBOL( lv_label_get_text ),
    EXPORT_SYMBOL( lv_label_ins_text ),
    EXPORT_SYMBOL( lv_label_set_align ),
    EXPORT_SYMBOL( lv_label_set_anim_speed ),
    EXPORT_SYMBOL( lv_label_set_array_text ),
    EXPORT_SYMBOL( lv_label_set_body_draw ),
    EXPORT_SYMBOL( lv_label_set_long_mode ),
    EXPORT_SYMBOL( lv_label_set_static_text ),
    EXPORT_SYMBOL( lv_label_set_style ),
    EXPORT_SYMBOL( lv_label_set_text ),
    EXPORT_SYMBOL( lv_list_add ),
    EXPORT_SYMBOL( lv_list_create ),
    EXPORT_SYMBOL( lv_list_down ),
    EXPORT_SYMBOL( lv_list_focus ),
    EXPORT_SYMBOL( lv_list_get_anim_time ),
    EXPORT_SYMBOL( lv_list_get_btn_img ),
    EXPORT_SYMBOL( lv_list_get_btn_index ),
    EXPORT_SYMBOL( lv_list_get_btn_label ),
    EXPORT_SYMBOL( lv_list_get_btn_text ),
    EXPORT_SYMBOL( lv_list_get_next_btn ),
    EXPORT_SYMBOL( lv_list_get_prev_btn ),
    EXPORT_SYMBOL( lv_list_get_size ),
    EXPORT_SYMBOL( lv_list_get_sb_mode ),
    EXPORT_SYMBOL( lv_list_get_style ),
    EXPORT_SYMBOL( lv_list_remove ),
    EXPORT_SYMBOL( lv_list_set_anim_time ),
    EXPORT_SYMBOL( lv_list_set_btn_selected ),
    EXPORT_SYMBOL( lv_list_set_sb_mode ),
    EXPORT_SYMBOL( lv_list_set_style ),
    EXPORT_SYMBOL( lv_list_up ),
    EXPORT_SYMBOL( lv_obj_align ),
    EXPORT_SYMBOL( lv_obj_clean ),
    EXPORT_SYMBOL( lv_obj_count_children ),
    EXPORT_SYMBOL( lv_obj_create ),
    EXPORT_SYMBOL( lv_obj_del ),
    EXPORT_SYMBOL( lv_obj_get_child ),
    EXPORT_SYMBOL( lv_obj_get_child_back ),
    EXPORT_SYMBOL( lv_obj_get_coords ),
    EXPORT_SYMBOL( lv_obj_get_ext_attr ),
    EXPORT_SYMBOL( lv_obj_get_ext_size ),
    EXPORT_SYMBOL( lv_obj_get_free_num ),
    EXPORT_SYMBOL( lv_obj_get_free_ptr ),
    EXPORT_SYMBOL( lv_obj_get_group ),
    EXPORT_SYMBOL( lv_obj_get_height ),
    EXPORT_SYMBOL( lv_obj_get_parent ),
    EXPORT_SYMBOL( lv_obj_get_style ),
    EXPORT_SYMBOL( lv_obj_get_type ),
    EXPORT_SYMBOL( lv_obj_get_width ),
    EXPORT_SYMBOL( lv_obj_get_x ),
    EXPORT_SYMBOL( lv_obj_get_y ),
    EXPORT_SYMBOL( lv_obj_invalidate ),
    EXPORT_SYMBOL( lv_obj_set_height ),
    EXPORT_SYMBOL( lv_obj_set_hidden ),
    EXPORT_SYMBOL( lv_obj_set_parent ),
    EXPORT_SYMBOL( lv_obj_set_pos ),
    EXPORT_SYMBOL( lv_obj_set_size ),
    EXPORT_SYMBOL( lv_obj_set_top ),
    EXPORT_SYMBOL( lv_obj_set_width ),
    EXPORT_SYMBOL( lv_obj_set_x ),
    EXPORT_SYMBOL( lv_obj_set_y ),
    EXPORT_SYMBOL( lv_roller_create ),
    EXPORT_SYMBOL( lv_roller_get_action ),
    EXPORT_SYMBOL( lv_roller_get_anim_time ),
    EXPORT_SYMBOL( lv_roller_get_hor_fit ),
    EXPORT_SYMBOL( lv_roller_get_options ),
    EXPORT_SYMBOL( lv_roller_get_selected ),
    EXPORT_SYMBOL( lv_roller_get_selected_str ),
    EXPORT_SYMBOL( lv_roller_get_style ),
    EXPORT_SYMBOL( lv_roller_set_action ),
    EXPORT_SYMBOL( lv_roller_set_anim_time ),
    EXPORT_SYMBOL( lv_roller_set_hor_fit ),
    EXPORT_SYMBOL( lv_roller_set_options ),
    EXPORT_SYMBOL( lv_roller_set_selected ),
    EXPORT_SYMBOL( lv_roller_set_style ),
    EXPORT_SYMBOL( lv_roller_set_visible_row_count ),
    EXPORT_SYMBOL( lv_scr_act ),
    EXPORT_SYMBOL( malloc ),
    EXPORT_SYMBOL( mbedtls_mpi_add_abs ),
    EXPORT_SYMBOL( mbedtls_mpi_add_mpi ),
    EXPORT_SYMBOL( mbedtls_mpi_cmp_mpi ),
    EXPORT_SYMBOL( mbedtls_mpi_copy ),
    EXPORT_SYMBOL( mbedtls_mpi_free ),
    EXPORT_SYMBOL( mbedtls_mpi_init ),
    EXPORT_SYMBOL( mbedtls_mpi_lset ),
    EXPORT_SYMBOL( mbedtls_mpi_read_string ),
    EXPORT_SYMBOL( mbedtls_mpi_sub_abs ),
    EXPORT_SYMBOL( mbedtls_mpi_sub_mpi ),
    EXPORT_SYMBOL( mbedtls_mpi_write_binary ),
    EXPORT_SYMBOL( mbedtls_mpi_write_string ),
    EXPORT_SYMBOL( memchr ),
    EXPORT_SYMBOL( memcmp ),
    EXPORT_SYMBOL( memcpy ),
    EXPORT_SYMBOL( memmove ),
    EXPORT_SYMBOL( memset ),
    EXPORT_SYMBOL( network_get_data ),
    EXPORT_SYMBOL( printf ),
    EXPORT_SYMBOL( puts ),
    EXPORT_SYMBOL( qrcode_getBufferSize ),
    EXPORT_SYMBOL( qrcode_initText ),
    EXPORT_SYMBOL( randombytes_random ),
    EXPORT_SYMBOL( snprintf ),
    EXPORT_SYMBOL( sodium_bin2hex ),
    EXPORT_SYMBOL( sodium_hex2bin ),
    EXPORT_SYMBOL( sodium_malloc ),
    EXPORT_SYMBOL( sodium_memcmp ),
    EXPORT_SYMBOL( sodium_memzero ),
    EXPORT_SYMBOL( sscanf ),
    EXPORT_SYMBOL( storage_erase_key ),
    EXPORT_SYMBOL( storage_get_blob ),
    EXPORT_SYMBOL( storage_get_str ),
    EXPORT_SYMBOL( storage_get_u16 ),
    EXPORT_SYMBOL( storage_get_u32 ),
    EXPORT_SYMBOL( storage_get_u8 ),
    EXPORT_SYMBOL( storage_set_blob ),
    EXPORT_SYMBOL( storage_set_str ),
    EXPORT_SYMBOL( storage_set_u16 ),
    EXPORT_SYMBOL( storage_set_u32 ),
    EXPORT_SYMBOL( storage_set_u8 ),
    EXPORT_SYMBOL( strcasecmp ),
    EXPORT_SYMBOL( strcat ),
    EXPORT_SYMBOL( strchr ),
    EXPORT_SYMBOL( strcmp ),
    EXPORT_SYMBOL( strcpy ),
    EXPORT_SYMBOL( strcspn ),
    EXPORT_SYMBOL( strdup ),
    EXPORT_SYMBOL( strftime ),
    EXPORT_SYMBOL( strlcat ),
    EXPORT_SYMBOL( strlcpy ),
    EXPORT_SYMBOL( strlen ),
    EXPORT_SYMBOL( strlwr ),
    EXPORT_SYMBOL( strncasecmp ),
    EXPORT_SYMBOL( strncat ),
    EXPORT_SYMBOL( strncmp ),
    EXPORT_SYMBOL( strncpy ),
    EXPORT_SYMBOL( strndup ),
    EXPORT_SYMBOL( strnlen ),
    EXPORT_SYMBOL( strrchr ),
    EXPORT_SYMBOL( strstr ),
    EXPORT_SYMBOL( strtod ),
    EXPORT_SYMBOL( strtof ),
    EXPORT_SYMBOL( strtol ),
    EXPORT_SYMBOL( strupr ),
    EXPORT_SYMBOL( subconsole_cmd_free ),
    EXPORT_SYMBOL( subconsole_cmd_init ),
    EXPORT_SYMBOL( subconsole_cmd_register ),
    EXPORT_SYMBOL( subconsole_cmd_run ),
    EXPORT_SYMBOL( vTaskDelete ),
    EXPORT_SYMBOL( vault_get_node ),
    EXPORT_SYMBOL( vault_get_valid ),
    EXPORT_SYMBOL( vault_is_valid ),
    EXPORT_SYMBOL( vault_refresh ),
    EXPORT_SYMBOL( vault_sem_give ),
    EXPORT_SYMBOL( vault_sem_take ),
    EXPORT_SYMBOL( xQueueCreateCountingSemaphore ),
    EXPORT_SYMBOL( xQueueCreateMutex ),
    EXPORT_SYMBOL( xQueueGenericCreate ),
    EXPORT_SYMBOL( xQueueGenericReceive ),
    EXPORT_SYMBOL( xQueueGenericReset ),
    EXPORT_SYMBOL( xQueueGenericSend ),
    EXPORT_SYMBOL( xQueueGenericSendFromISR ),
    EXPORT_SYMBOL( xQueueGetMutexHolder ),
    EXPORT_SYMBOL( xQueueGiveFromISR ),
    EXPORT_SYMBOL( xQueueGiveMutexRecursive ),
    EXPORT_SYMBOL( xQueueReceiveFromISR ),
    EXPORT_SYMBOL( xQueueTakeMutexRecursive ),
    EXPORT_SYMBOL( xTaskCreatePinnedToCore ),
};

static const jelfLoaderEnv_t env = {
    .exported = exports,
    .exported_size = sizeof(exports) / sizeof(*exports)
};

#else

// Dummy place holder
static const jelfLoaderEnv_t env;

#endif

#endif

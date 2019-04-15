/* All of the functions available to an app.
 *
 * DO NOT CHANGE THIS FILE (jolt_lib.h) directly, either change:
 *     * elf2jelf/jolt_lib_template.h
 *     * elf2jelf/export_list.txt 
 *
 * jolt_lib.h will automatically be updated upon make
 * */

#include "jolt_lib.h"
#include "sdkconfig.h"

#if JOLT_OS

const jolt_version_t JOLT_JELF_VERSION = {
    .major = 0,
    .minor = 1,
    .patch = 0,
    .release = JOLT_VERSION_DEV,
};

const char *JOLT_OS_COMMIT = "db312a7e3d544d55b854cfe4a5368cbb2d15406b";

extern void *__fixunsdfsi;
extern void *__floatunsidf;
extern void *__floatsidf;
extern void *__gtdf2;
extern void *__ltdf2;
extern void *__muldf3;

#if CONFIG_STACK_CHECK
extern void *__stack_chk_fail;
extern void *__stack_chk_guard;
#else
static inline void __stack_chk_fail (void) { return; }
void *__stack_chk_guard = NULL;
#endif

#define EXPORT_SYMBOL(x) &x

/**
 * @brief Export functions to be used in applications.
 *
 * This order is very important; only *append* fuctions
 */
static const void *exports[] = {
    EXPORT_SYMBOL( __assert_func ),
    EXPORT_SYMBOL( __fixunsdfsi ),
    EXPORT_SYMBOL( __floatsidf ),
    EXPORT_SYMBOL( __floatunsidf ),
    EXPORT_SYMBOL( __gtdf2 ),
    EXPORT_SYMBOL( __ltdf2 ),
    EXPORT_SYMBOL( __muldf3 ),
    EXPORT_SYMBOL( __stack_chk_fail ),
    EXPORT_SYMBOL( __stack_chk_guard ),
    EXPORT_SYMBOL( _esp_error_check_failed ),
    EXPORT_SYMBOL( abort ),
    EXPORT_SYMBOL( atoi ),
    EXPORT_SYMBOL( atol ),
    EXPORT_SYMBOL( bm_entropy256 ),
    EXPORT_SYMBOL( cJSON_AddArrayToObject ),
    EXPORT_SYMBOL( cJSON_AddBoolToObject ),
    EXPORT_SYMBOL( cJSON_AddFalseToObject ),
    EXPORT_SYMBOL( cJSON_AddItemReferenceToArray ),
    EXPORT_SYMBOL( cJSON_AddItemReferenceToObject ),
    EXPORT_SYMBOL( cJSON_AddItemToArray ),
    EXPORT_SYMBOL( cJSON_AddItemToObject ),
    EXPORT_SYMBOL( cJSON_AddItemToObjectCS ),
    EXPORT_SYMBOL( cJSON_AddNullToObject ),
    EXPORT_SYMBOL( cJSON_AddNumberToObject ),
    EXPORT_SYMBOL( cJSON_AddObjectToObject ),
    EXPORT_SYMBOL( cJSON_AddRawToObject ),
    EXPORT_SYMBOL( cJSON_AddStringToObject ),
    EXPORT_SYMBOL( cJSON_AddTrueToObject ),
    EXPORT_SYMBOL( cJSON_CreateArray ),
    EXPORT_SYMBOL( cJSON_CreateArrayReference ),
    EXPORT_SYMBOL( cJSON_CreateBool ),
    EXPORT_SYMBOL( cJSON_CreateDoubleArray ),
    EXPORT_SYMBOL( cJSON_CreateFalse ),
    EXPORT_SYMBOL( cJSON_CreateFloatArray ),
    EXPORT_SYMBOL( cJSON_CreateIntArray ),
    EXPORT_SYMBOL( cJSON_CreateNull ),
    EXPORT_SYMBOL( cJSON_CreateNumber ),
    EXPORT_SYMBOL( cJSON_CreateObject ),
    EXPORT_SYMBOL( cJSON_CreateObjectReference ),
    EXPORT_SYMBOL( cJSON_CreateRaw ),
    EXPORT_SYMBOL( cJSON_CreateString ),
    EXPORT_SYMBOL( cJSON_CreateStringArray ),
    EXPORT_SYMBOL( cJSON_CreateStringReference ),
    EXPORT_SYMBOL( cJSON_CreateTrue ),
    EXPORT_SYMBOL( cJSON_Delete ),
    EXPORT_SYMBOL( cJSON_DeleteItemFromArray ),
    EXPORT_SYMBOL( cJSON_DeleteItemFromObject ),
    EXPORT_SYMBOL( cJSON_DeleteItemFromObjectCaseSensitive ),
    EXPORT_SYMBOL( cJSON_DetachItemFromArray ),
    EXPORT_SYMBOL( cJSON_DetachItemFromObject ),
    EXPORT_SYMBOL( cJSON_DetachItemFromObjectCaseSensitive ),
    EXPORT_SYMBOL( cJSON_DetachItemViaPointer ),
    EXPORT_SYMBOL( cJSON_GetArrayItem ),
    EXPORT_SYMBOL( cJSON_GetArraySize ),
    EXPORT_SYMBOL( cJSON_GetObjectItem ),
    EXPORT_SYMBOL( cJSON_GetObjectItemCaseSensitive ),
    EXPORT_SYMBOL( cJSON_GetStringValue ),
    EXPORT_SYMBOL( cJSON_InsertItemInArray ),
    EXPORT_SYMBOL( cJSON_IsArray ),
    EXPORT_SYMBOL( cJSON_IsBool ),
    EXPORT_SYMBOL( cJSON_IsFalse ),
    EXPORT_SYMBOL( cJSON_IsInvalid ),
    EXPORT_SYMBOL( cJSON_IsNull ),
    EXPORT_SYMBOL( cJSON_IsNumber ),
    EXPORT_SYMBOL( cJSON_IsObject ),
    EXPORT_SYMBOL( cJSON_IsRaw ),
    EXPORT_SYMBOL( cJSON_IsString ),
    EXPORT_SYMBOL( cJSON_IsTrue ),
    EXPORT_SYMBOL( cJSON_Parse ),
    EXPORT_SYMBOL( cJSON_Print ),
    EXPORT_SYMBOL( cJSON_PrintUnformatted ),
    EXPORT_SYMBOL( cJSON_ReplaceItemInArray ),
    EXPORT_SYMBOL( cJSON_ReplaceItemInObject ),
    EXPORT_SYMBOL( cJSON_ReplaceItemInObjectCaseSensitive ),
    EXPORT_SYMBOL( cJSON_ReplaceItemViaPointer ),
    EXPORT_SYMBOL( cJSON_SetNumberHelper ),
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
    EXPORT_SYMBOL( heap_caps_check_integrity_all ),
    EXPORT_SYMBOL( jolt_cmd_return ),
    EXPORT_SYMBOL( jolt_gui_debug_obj_print ),
    EXPORT_SYMBOL( jolt_gui_err_to_str ),
    EXPORT_SYMBOL( jolt_gui_find ),
    EXPORT_SYMBOL( jolt_gui_group_add ),
    EXPORT_SYMBOL( jolt_gui_obj_cont_body_create ),
    EXPORT_SYMBOL( jolt_gui_obj_del ),
    EXPORT_SYMBOL( jolt_gui_obj_get_param ),
    EXPORT_SYMBOL( jolt_gui_obj_set_param ),
    EXPORT_SYMBOL( jolt_gui_scr_set_active_param ),
    EXPORT_SYMBOL( jolt_gui_obj_id_get ),
    EXPORT_SYMBOL( jolt_gui_obj_parent_create ),
    EXPORT_SYMBOL( jolt_gui_obj_title_create ),
    EXPORT_SYMBOL( jolt_gui_scr_bignum_create ),
    EXPORT_SYMBOL( jolt_gui_scr_del ),
    EXPORT_SYMBOL( jolt_gui_scr_digit_entry_create ),
    EXPORT_SYMBOL( jolt_gui_scr_digit_entry_get_arr ),
    EXPORT_SYMBOL( jolt_gui_scr_digit_entry_get_double ),
    EXPORT_SYMBOL( jolt_gui_scr_digit_entry_get_hash ),
    EXPORT_SYMBOL( jolt_gui_scr_digit_entry_get_int ),
    EXPORT_SYMBOL( jolt_gui_scr_digit_entry_set_pos ),
    EXPORT_SYMBOL( jolt_gui_scr_err_create ),
    EXPORT_SYMBOL( jolt_gui_scr_id_get ),
    EXPORT_SYMBOL( jolt_gui_scr_loadingbar_autoupdate ),
    EXPORT_SYMBOL( jolt_gui_scr_loadingbar_create ),
    EXPORT_SYMBOL( jolt_gui_scr_loadingbar_update ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_add ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_add_sw ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_create ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_get_list ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_get_scr ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_remove ),
    EXPORT_SYMBOL( jolt_gui_scr_menu_set_btn_selected ),
    EXPORT_SYMBOL( jolt_gui_scr_preloading_create ),
    EXPORT_SYMBOL( jolt_gui_scr_preloading_update ),
    EXPORT_SYMBOL( jolt_gui_scr_qr_create ),
    EXPORT_SYMBOL( jolt_gui_scr_scroll_add_monospace_text ),
    EXPORT_SYMBOL( jolt_gui_scr_scroll_add_qr ),
    EXPORT_SYMBOL( jolt_gui_scr_scroll_add_text ),
    EXPORT_SYMBOL( jolt_gui_scr_scroll_create ),
    EXPORT_SYMBOL( jolt_gui_scr_scroll_get_page ),
    EXPORT_SYMBOL( jolt_gui_scr_set_event_cb ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_create ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_get_slider ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_get_value ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_set_label ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_set_range ),
    EXPORT_SYMBOL( jolt_gui_scr_slider_set_value ),
    EXPORT_SYMBOL( jolt_gui_scr_text_create ),
    EXPORT_SYMBOL( jolt_gui_sem_give ),
    EXPORT_SYMBOL( jolt_gui_sem_give ),
    EXPORT_SYMBOL( jolt_gui_sem_take ),
    EXPORT_SYMBOL( jolt_gui_sem_take ),
    EXPORT_SYMBOL( jolt_json_read_app ),
    EXPORT_SYMBOL( jolt_json_write_app ),
    EXPORT_SYMBOL( jolt_network_post ),
    EXPORT_SYMBOL( linenoise ),
    EXPORT_SYMBOL( lv_btn_create ),
    EXPORT_SYMBOL( lv_btn_get_fit_bottom ),
    EXPORT_SYMBOL( lv_btn_get_fit_left ),
    EXPORT_SYMBOL( lv_btn_get_fit_right ),
    EXPORT_SYMBOL( lv_btn_get_fit_top ),
    EXPORT_SYMBOL( lv_btn_get_layout ),
    EXPORT_SYMBOL( lv_btn_get_state ),
    EXPORT_SYMBOL( lv_btn_get_style ),
    EXPORT_SYMBOL( lv_btn_get_toggle ),
    EXPORT_SYMBOL( lv_btn_set_fit ),
    EXPORT_SYMBOL( lv_btn_set_fit2 ),
    EXPORT_SYMBOL( lv_btn_set_fit4 ),
    EXPORT_SYMBOL( lv_btn_set_layout ),
    EXPORT_SYMBOL( lv_btn_set_state ),
    EXPORT_SYMBOL( lv_btn_set_style ),
    EXPORT_SYMBOL( lv_btn_set_toggle ),
    EXPORT_SYMBOL( lv_btn_toggle ),
    EXPORT_SYMBOL( lv_cont_create ),
    EXPORT_SYMBOL( lv_cont_get_fit_bottom ),
    EXPORT_SYMBOL( lv_cont_get_fit_left ),
    EXPORT_SYMBOL( lv_cont_get_fit_right ),
    EXPORT_SYMBOL( lv_cont_get_fit_top ),
    EXPORT_SYMBOL( lv_cont_get_layout ),
    EXPORT_SYMBOL( lv_cont_get_style ),
    EXPORT_SYMBOL( lv_cont_set_fit ),
    EXPORT_SYMBOL( lv_cont_set_fit2 ),
    EXPORT_SYMBOL( lv_cont_set_fit4 ),
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
    EXPORT_SYMBOL( lv_list_get_sb_mode ),
    EXPORT_SYMBOL( lv_list_get_size ),
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
    EXPORT_SYMBOL( lv_obj_get_group ),
    EXPORT_SYMBOL( lv_obj_get_height ),
    EXPORT_SYMBOL( lv_obj_get_parent ),
    EXPORT_SYMBOL( lv_obj_get_style ),
    EXPORT_SYMBOL( lv_obj_get_type ),
    EXPORT_SYMBOL( lv_obj_get_width ),
    EXPORT_SYMBOL( lv_obj_get_x ),
    EXPORT_SYMBOL( lv_obj_get_y ),
    EXPORT_SYMBOL( lv_obj_invalidate ),
    EXPORT_SYMBOL( lv_obj_set_event_cb ),
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
    EXPORT_SYMBOL( lv_roller_get_anim_time ),
    EXPORT_SYMBOL( lv_roller_get_hor_fit ),
    EXPORT_SYMBOL( lv_roller_get_options ),
    EXPORT_SYMBOL( lv_roller_get_selected ),
    EXPORT_SYMBOL( lv_roller_get_selected_str ),
    EXPORT_SYMBOL( lv_roller_get_style ),
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
    EXPORT_SYMBOL( printf ),
    EXPORT_SYMBOL( putchar ),
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
    EXPORT_SYMBOL( vault_get_node ),
    EXPORT_SYMBOL( vault_get_valid ),
    EXPORT_SYMBOL( vault_refresh ),
    EXPORT_SYMBOL( vault_sem_give ),
    EXPORT_SYMBOL( vault_sem_take ),

};

#else

const jolt_version_t JOLT_JELF_VERSION = { 0 };

const char *JOLT_OS_COMMIT = NULL;

/* Dummy place holder */
static const void *exports[349] = { 0 };

#endif

const jelfLoaderEnv_t jelf_loader_env = {
    .exported = exports,
    .exported_size = sizeof(exports) / sizeof(*exports)
};

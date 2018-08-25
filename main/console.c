/* Jolt Wallet - Open Source Cryptocurrency Hardware Wallet
 Copyright (C) 2018  Brian Pugh, James Coxon, Michael Smaili
 https://www.joltwallet.com/
 */

#include "menu8g2.h"
#include "sodium.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "esp_console.h"
#include "driver/uart.h"
#include "esp_vfs_dev.h"
#include "esp_log.h"
#include "linenoise/linenoise.h"

#include "globals.h"
#include "console.h"
#include "vault.h"
#include "helpers.h"
#include "gui/gui.h"
#include "gui/loading.h"
#include "gui/statusbar.h"
#include "gui/confirmation.h"

#include "syscore/console.h"
#include "syscore/launcher.h"

static const char* TAG = "console";

volatile TaskHandle_t console_h = NULL;


void console_task() {
    /* Prompt to be printed before each line.
     * This can be customized, made dynamic, etc.
     */
    const char* prompt = "jolt> ";

    #if CONFIG_JOLT_CONSOLE_OVERRIDE_LOGGING
    esp_log_level_set("*", ESP_LOG_NONE);
    #endif

    printf("\n"
           "Welcome to the Jolt Console.\n"
           "Type 'help' to get the list of commands.\n"
           "\n");

    /* Figure out if the terminal supports escape sequences */
    int probe_status = linenoiseProbe();
    if (probe_status) { /* zero indicates success */
        printf("\n"
               "Your terminal application does not support escape sequences.\n"
               "Line editing and history features are disabled.\n"
               "On Windows, try using Putty instead.\n");
        linenoiseSetDumbMode(1);
    }
    
    /* Main loop */
    for(;;) {
        /* Get a line using linenoise.
         * The line is returned when ENTER is pressed.
         */
        char* line = linenoise(prompt);
        if (line == NULL) { /* Ignore empty lines */
            continue;
        }
        if (strcmp(line, "exit") == 0){
            printf("Exiting Console\n");
            break;
        }
        /* Add the command to the history */
        linenoiseHistoryAdd(line);
        
        /* Try to run the command */
        int ret;
        esp_err_t err = esp_console_run(line, &ret);
        if (err == ESP_ERR_NOT_FOUND) {
            // The command could be an app to run console commands from
            char *argv[CONFIG_JOLT_CONSOLE_MAX_ARGS + 1];
            // split_argv modifies line with NULL-terminators
            size_t argc = esp_console_split_argv(line, argv, sizeof(argv));
            printf("Line: %s\n", line);
            if( launch_file(argv[0], "console", argc-1, argv+1) ) {
                printf("Unsuccessful command\n");
            }
        } else if (err == ESP_ERR_INVALID_ARG) {
            // command was empty
        } else if (err == ESP_OK && ret != ESP_OK) {
            printf("Command returned non-zero error code: 0x%x\n", ret);
        } else if (err != ESP_OK) {
            printf("Internal error: 0x%x\n", err);
        }
        /* linenoise allocates line buffer on the heap, so need to free it */
        linenoiseFree(line);
    }
    
    #if CONFIG_JOLT_CONSOLE_OVERRIDE_LOGGING
    esp_log_level_set("*", CONFIG_LOG_DEFAULT_LEVEL);
    #endif

    console_h = NULL;
    vTaskDelete( NULL );
}

volatile TaskHandle_t *start_console(){
    xTaskCreate(console_task,
                "ConsoleTask", 28000,
                NULL, 19,
                (TaskHandle_t *) &console_h);
    return  &console_h;
}

void menu_console(menu8g2_t *prev){
    /* On-Device GUI for Starting Console */
    menu8g2_t menu;
    menu8g2_copy(&menu, prev);

    if(console_h){
        ESP_LOGI(TAG, "Console already running.");
        menu8g2_display_text_title(&menu,
                "Console is already running.",
                "Console");
    }
    else{
        ESP_LOGI(TAG, "Starting console.");
        start_console();
        menu8g2_display_text_title(&menu,
                "Console Started.",
                "Console");
    }
}

static void console_register_commands(){

    esp_console_register_help_command();
    
    console_syscore_register();

    /* Register app names */
    // TODO

    /* Register Coin Specific Commands */
    // TODO deprecate this
}

void initialize_console() {
    /* Disable buffering on stdin and stdout */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    
    /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
    esp_vfs_dev_uart_set_rx_line_endings(ESP_LINE_ENDINGS_CR);
    /* Move the caret to the beginning of the next line on '\n' */
    esp_vfs_dev_uart_set_tx_line_endings(ESP_LINE_ENDINGS_CRLF);
    
    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(CONFIG_CONSOLE_UART_NUM,
            CONFIG_JOLT_CONSOLE_UART_RX_BUF_LEN,
            CONFIG_JOLT_CONSOLE_UART_TX_BUF_LEN,
            0, NULL, 0) );
    
    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(CONFIG_CONSOLE_UART_NUM);
    
    /* Initialize the console */
    esp_console_config_t console_config = {
        .max_cmdline_args = CONFIG_JOLT_CONSOLE_MAX_ARGS,
        .max_cmdline_length = CONFIG_JOLT_CONSOLE_MAX_CMD_LEN,
    };
    ESP_ERROR_CHECK( esp_console_init(&console_config) );
    
    /* Configure linenoise line completion library */
    /* Enable multiline editing. */
    linenoiseSetMultiLine(1);

    /* Clear the screen */
#if( JOLT_CONFIG_CONSOLE_STARTUP_CLEAR )
        linenoiseClearScreen();
#endif
    
    /* Tell linenoise where to get command completions and hints */
    linenoiseSetCompletionCallback(&esp_console_get_completion);
    linenoiseSetHintsCallback((linenoiseHintsCallback*) &esp_console_get_hint);
    
    /* Set command history size */
    linenoiseHistorySetMaxLen(CONFIG_JOLT_CONSOLE_HISTORY);

    /* Register commands */
    console_register_commands();
}

bool console_check_range_argc(uint8_t argc, uint8_t min, uint8_t max){
    if ( argc > max) {
        printf("Too many input arguments; max %d args, got %d\n",
                max, argc);
        return false;
    }
    if ( argc < min) {
        printf("Too few input arguments; min %d args, got %d\n",
                min, argc);
        return false;
    }

    return true;
}

bool console_check_equal_argc(uint8_t argc, uint8_t expected){
    if ( argc != expected) {
        printf("Incorrect number of input arguments; expected %d args, got %d\n",
                expected, argc);
        return false;
    }
    return true;
}

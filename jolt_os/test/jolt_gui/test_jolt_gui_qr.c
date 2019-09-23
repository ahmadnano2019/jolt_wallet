#include "hal/display.h"
#include "jolt_gui/jolt_gui.h"
#include "unity.h"

static const char MODULE_NAME[] = "[jolt_gui_qr]";

TEST_CASE( "jolt_gui_qr", MODULE_NAME )
{
    jolt_gui_obj_t *scr;
    jolt_display_t actual = {
            .encoding = JOLT_ENCODING_JRLE,
    };
    const char test_data_1[] = "test data";

    /* Common use-case 1 */
    {
        jolt_display_t expected = {
                .type     = JOLT_DISPLAY_TYPE_SSD1306,
                .encoding = JOLT_ENCODING_JRLE,
                .len      = 463,
                .data = ( uint8_t[] ) {0x0B, 0xF0, 0x08, 0x88, 0x08, 0xF0, 0x00, 0xF8, 0x48, 0xC8, 0x48, 0x30, 0x83,
                                       0x00, 0x82, 0x08, 0x01, 0xF8, 0x82, 0x08, 0x02, 0x00, 0xC0, 0x83, 0xA0, 0x03,
                                       0xC0, 0x00, 0x40, 0x83, 0xA0, 0x05, 0x20, 0x00, 0x20, 0xF8, 0x20, 0xDD, 0x00,
                                       0x01, 0x09, 0x82, 0x0A, 0x04, 0x09, 0x0A, 0x08, 0x0B, 0x82, 0x08, 0x02, 0x09,
                                       0x0A, 0x85, 0x08, 0x01, 0x0B, 0x83, 0x08, 0x01, 0x09, 0x84, 0x0A, 0x01, 0x08,
                                       0x84, 0x0A, 0x01, 0x09, 0x82, 0x08, 0x02, 0x09, 0x0A, 0x85, 0x08, 0x01, 0xC8,
                                       0x85, 0x48, 0x03, 0xC8, 0x08, 0xC8, 0x82, 0x88, 0x84, 0xC8, 0x17, 0x48, 0xC8,
                                       0x08, 0xC8, 0x88, 0x08, 0x88, 0x08, 0x48, 0xC8, 0x48, 0xC8, 0x48, 0x08, 0x88,
                                       0xC8, 0x88, 0xC8, 0x88, 0x08, 0x48, 0xC8, 0x48, 0x82, 0x88, 0x03, 0xC8, 0x08,
                                       0xC8, 0x85, 0x48, 0x01, 0xC8, 0xA6, 0x08, 0x01, 0xF8, 0xA8, 0x00, 0x31, 0xDF,
                                       0x50, 0x17, 0x97, 0x57, 0x50, 0x5F, 0x80, 0x1B, 0xE5, 0x70, 0xC1, 0x14, 0x69,
                                       0xDC, 0x46, 0x1E, 0x86, 0xDC, 0xA9, 0xF1, 0xAE, 0xFC, 0xC6, 0xD4, 0xC6, 0xFC,
                                       0x69, 0xFD, 0x89, 0x3C, 0x86, 0x12, 0x89, 0xD3, 0x69, 0x12, 0x64, 0x38, 0x63,
                                       0x31, 0x00, 0x9F, 0x50, 0x97, 0xD7, 0x57, 0x50, 0xDF, 0xA6, 0x00, 0x01, 0xFF,
                                       0xA8, 0x00, 0x31, 0xA7, 0x48, 0xAB, 0xB4, 0x94, 0xF1, 0x55, 0x37, 0x95, 0x54,
                                       0x8F, 0x83, 0x5B, 0x99, 0xBB, 0xA6, 0xB3, 0x66, 0xBB, 0x59, 0x4C, 0x61, 0x30,
                                       0x67, 0x10, 0x67, 0x22, 0x98, 0x32, 0x79, 0xC2, 0x67, 0xCD, 0x79, 0x3D, 0x98,
                                       0xCD, 0x86, 0xC2, 0x9A, 0x8B, 0x86, 0x2C, 0x98, 0x10, 0x63, 0x37, 0x8E, 0xE3,
                                       0xA6, 0x00, 0x01, 0xFF, 0xA8, 0x00, 0x31, 0x58, 0x6D, 0x7B, 0xEC, 0xF9, 0x1F,
                                       0x55, 0x12, 0xF7, 0x77, 0xCF, 0x86, 0x5D, 0x66, 0xCC, 0x59, 0x08, 0x99, 0xCC,
                                       0xA6, 0xF7, 0xEE, 0xFB, 0x18, 0x5D, 0x18, 0xFC, 0x67, 0xEF, 0x86, 0x2C, 0x98,
                                       0x10, 0x86, 0xD3, 0x67, 0x10, 0x79, 0x2C, 0x25, 0xF0, 0x19, 0x52, 0x17, 0xFD,
                                       0x99, 0x0F, 0x49, 0xC4, 0xA6, 0x00, 0x01, 0xFF, 0xA8, 0x00, 0x16, 0x33, 0x7F,
                                       0x0B, 0x90, 0x25, 0x6B, 0x55, 0x85, 0xDB, 0x55, 0x1B, 0xE2, 0xD7, 0x99, 0xBB,
                                       0xA6, 0xB3, 0x66, 0xBB, 0x59, 0x4C, 0x3D, 0x82, 0xA7, 0x19, 0x4D, 0xA7, 0x0D,
                                       0x98, 0x32, 0x79, 0xC2, 0x67, 0xCD, 0x79, 0x3D, 0x98, 0xCD, 0x86, 0xC2, 0xF2,
                                       0x97, 0x9B, 0xCD, 0x59, 0x4D, 0x61, 0x37, 0xE6, 0xC3, 0xA6, 0x00, 0x01, 0xFF,
                                       0xA8, 0x00, 0x31, 0x40, 0x7B, 0x6F, 0x21, 0x0E, 0x1E, 0x55, 0x31, 0xD7, 0xB4,
                                       0x5C, 0x5A, 0xF5, 0x66, 0xCC, 0x59, 0x08, 0x99, 0xCC, 0xA6, 0xF7, 0xD3, 0xD9,
                                       0x59, 0x77, 0x59, 0xD1, 0x67, 0xEF, 0x86, 0x2C, 0x98, 0x10, 0x86, 0xD3, 0x67,
                                       0x10, 0x79, 0x2C, 0xAE, 0xE9, 0x65, 0x50, 0x66, 0xF7, 0x9C, 0x0F, 0x09, 0x84,
                                       0xA6, 0x00, 0x01, 0xFF, 0xA8, 0x00, 0x02, 0x7F, 0x41, 0x83, 0x5D, 0x2C, 0x41,
                                       0x7F, 0x00, 0x66, 0x33, 0x57, 0x26, 0x4C, 0x19, 0x3B, 0x26, 0x33, 0x66, 0x3B,
                                       0x59, 0x4C, 0x65, 0x47, 0x1C, 0x4D, 0x1C, 0x4F, 0x18, 0x32, 0x79, 0x42, 0x67,
                                       0x4D, 0x79, 0x3D, 0x18, 0x4D, 0x06, 0x42, 0x1B, 0x37, 0x1C, 0x75, 0x6C, 0x4F,
                                       0x61, 0x37, 0x76, 0x4B, 0xA6, 0x00, 0x01, 0x1F},
        };
        scr = jolt_gui_scr_qr_create( "QR Test", test_data_1, strlen( test_data_1 ) );
        TEST_ASSERT_TRUE( jolt_display_copy( &actual ) );
        TEST_ASSERT_DISPLAY( &expected, &actual );
        jolt_display_free( &actual );
        jolt_gui_scr_del( scr );
    }
}

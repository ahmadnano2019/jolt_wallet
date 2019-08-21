#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 40 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef MODENINE_40
#define MODENINE_40 1
#endif

#if MODENINE_40

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+30 "0" */
    0x3, 0xfc, 0x0, 0xff, 0xf0, 0x1f, 0xff, 0x83,
    0xff, 0xfc, 0x7c, 0x3, 0xef, 0x80, 0x1e, 0xf0,
    0x0, 0xff, 0x0, 0xf, 0xf0, 0x0, 0xff, 0x0,
    0xf, 0xf0, 0x0, 0xff, 0x0, 0xf, 0xf0, 0x0,
    0xff, 0x0, 0xf, 0xf0, 0x0, 0xff, 0x0, 0xf,
    0xf0, 0x0, 0xff, 0x0, 0xf, 0xf0, 0x0, 0xff,
    0x0, 0xf, 0xf0, 0x0, 0xff, 0x0, 0xf, 0xf8,
    0x1, 0xe7, 0xc0, 0x3e, 0x3f, 0xff, 0xc1, 0xff,
    0xf8, 0xf, 0xff, 0x0, 0x7f, 0xc0,

    /* U+31 "1" */
    0xf, 0x0, 0xf0, 0x1f, 0x3, 0xf0, 0xff, 0xf,
    0xf0, 0xff, 0xe, 0xf0, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0,
    0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0,
    0xf0, 0xf, 0x0, 0xf0, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff,

    /* U+32 "2" */
    0x3, 0xfc, 0x0, 0xff, 0xf0, 0x1f, 0xff, 0x83,
    0xff, 0xfc, 0x7c, 0x3, 0xef, 0x80, 0x1e, 0xf0,
    0x0, 0xff, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0,
    0xf, 0x0, 0x1, 0xe0, 0x0, 0x3e, 0x3, 0xff,
    0xc0, 0xff, 0xf8, 0x1f, 0xff, 0x3, 0xff, 0xc0,
    0x7c, 0x0, 0xf, 0x80, 0x0, 0xf0, 0x0, 0xf,
    0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x0, 0xf0,
    0x0, 0xf, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+33 "3" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x0, 0x0, 0xf0, 0x0, 0x1f, 0x0,
    0x3, 0xf0, 0x0, 0x7e, 0x0, 0xf, 0xc0, 0x1,
    0xf8, 0x0, 0x3f, 0x0, 0x7, 0xe0, 0x0, 0xfc,
    0x0, 0x1f, 0xf0, 0x3, 0xff, 0x80, 0x7f, 0xfc,
    0x0, 0x3, 0xe0, 0x0, 0x1e, 0x0, 0x0, 0xf0,
    0x0, 0xf, 0xf0, 0x0, 0xff, 0x0, 0xf, 0xf8,
    0x1, 0xe7, 0xc0, 0x3e, 0x3f, 0xff, 0xc1, 0xff,
    0xf8, 0xf, 0xff, 0x0, 0x7f, 0xc0,

    /* U+34 "4" */
    0x0, 0xf, 0x0, 0x1, 0xf0, 0x0, 0x3f, 0x0,
    0x7, 0xf0, 0x0, 0xff, 0x0, 0x1f, 0xf0, 0x3,
    0xff, 0x0, 0x7e, 0xf0, 0xf, 0xcf, 0x1, 0xf8,
    0xf0, 0x3f, 0xf, 0x7, 0xe0, 0xf0, 0xfc, 0xf,
    0xf, 0x80, 0xf0, 0xf0, 0xf, 0xf, 0x0, 0xf0,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0,
    0xf, 0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x0,
    0xf0, 0x0, 0xf, 0x0, 0x0, 0xf0,

    /* U+35 "5" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf0, 0x0, 0xf, 0x0, 0x0, 0xf0,
    0x0, 0xf, 0x0, 0x0, 0xff, 0xfc, 0xf, 0xff,
    0xf0, 0xff, 0xff, 0x8f, 0xff, 0xfc, 0x0, 0x3,
    0xe0, 0x0, 0x1e, 0x0, 0x0, 0xf0, 0x0, 0xf,
    0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x0, 0xf0,
    0x0, 0xf, 0xf0, 0x0, 0xff, 0x0, 0xf, 0xf8,
    0x1, 0xe7, 0xc0, 0x3e, 0x3f, 0xff, 0xc1, 0xff,
    0xf8, 0xf, 0xff, 0x0, 0x7f, 0xc0,

    /* U+36 "6" */
    0x0, 0x7f, 0x0, 0x1f, 0xf0, 0x7, 0xff, 0x0,
    0xff, 0xf0, 0x1f, 0xc0, 0x3, 0xf0, 0x0, 0x3e,
    0x0, 0x7, 0xc0, 0x0, 0x78, 0x0, 0xf, 0x80,
    0x0, 0xf0, 0x0, 0xf, 0x0, 0x0, 0xff, 0xfc,
    0xf, 0xff, 0xf0, 0xff, 0xff, 0x8f, 0xff, 0xfc,
    0xf0, 0x3, 0xef, 0x0, 0x1e, 0xf0, 0x0, 0xff,
    0x0, 0xf, 0xf0, 0x0, 0xff, 0x0, 0xf, 0xf8,
    0x1, 0xe7, 0xc0, 0x3e, 0x3f, 0xff, 0xc1, 0xff,
    0xf8, 0xf, 0xff, 0x0, 0x7f, 0xc0,

    /* U+37 "7" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x0, 0x0, 0xf0, 0x0, 0x1f, 0x0,
    0x1, 0xe0, 0x0, 0x3e, 0x0, 0xf, 0xc0, 0x1,
    0xf8, 0x0, 0x3f, 0x0, 0x7, 0xe0, 0x0, 0xf8,
    0x0, 0x1f, 0x0, 0x3, 0xe0, 0x0, 0x7c, 0x0,
    0x7, 0xc0, 0x0, 0x78, 0x0, 0xf, 0x0, 0x0,
    0xf0, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0xf,
    0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x0, 0xf0,
    0x0, 0xf, 0x0, 0x0, 0xf0, 0x0,

    /* U+38 "8" */
    0x3, 0xfc, 0x0, 0xff, 0xf0, 0x1f, 0xff, 0x83,
    0xff, 0xfc, 0x7c, 0x3, 0xef, 0x80, 0x1e, 0xf0,
    0x0, 0xff, 0x0, 0xf, 0xf0, 0x0, 0xff, 0x0,
    0xf, 0x78, 0x1, 0xe7, 0xc0, 0x3e, 0x3f, 0xff,
    0xc1, 0xff, 0xf8, 0x1f, 0xff, 0x83, 0xff, 0xfc,
    0x7c, 0x3, 0xe7, 0x80, 0x1e, 0xf0, 0x0, 0xff,
    0x0, 0xf, 0xf0, 0x0, 0xff, 0x0, 0xf, 0xf8,
    0x1, 0xe7, 0xc0, 0x3e, 0x3f, 0xff, 0xc1, 0xff,
    0xf8, 0xf, 0xff, 0x0, 0x7f, 0xc0,

    /* U+39 "9" */
    0x3, 0xfc, 0x0, 0xff, 0xf0, 0x1f, 0xff, 0x83,
    0xff, 0xfc, 0x7c, 0x3, 0xef, 0x80, 0x1e, 0xf0,
    0x0, 0xff, 0x0, 0xf, 0xf0, 0x0, 0xff, 0x0,
    0xf, 0xf8, 0x0, 0xf7, 0xc0, 0xf, 0x3f, 0xff,
    0xf1, 0xff, 0xff, 0xf, 0xff, 0xf0, 0x7f, 0xff,
    0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x1, 0xf0,
    0x0, 0x1e, 0x0, 0x3, 0xe0, 0x0, 0x7c, 0x0,
    0xf, 0xc0, 0x3, 0xf8, 0xf, 0xff, 0x0, 0xff,
    0xe0, 0xf, 0xf8, 0x0, 0xfe, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_h = 0, .box_w = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 192, .box_h = 28, .box_w = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 320, .box_h = 28, .box_w = 20, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 10, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY,
        .glyph_id_start = 1, .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .cmap_num = 1,
    .bpp = 1,

    .kern_scale = 0,
    .kern_dsc = NULL,
    .kern_classes = 0,
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t modenine_40 = {
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .line_height = 28,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
};

#endif /*#if MODENINE_40*/


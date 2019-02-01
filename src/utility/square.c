
#include "lvgl.h"

/***********************************************************************************
 * Lato-Regular.ttf 10 px Font in U+0030 (0) .. U+0031 (1)  range with 1 bpp
 * Sparse font with only these characters: 01
***********************************************************************************/

/*Store the image of the letters (glyph)*/
static const uint8_t square_glyph_bitmap[] =
{
  /*Unicode: U+0030 (0) , Width: 5 */
  0x00,  0x00,  0x00,  0x00,  0x00, 0x00,  0x00,  0x00,  0x00,  0x00,
  /*Unicode: U+0031 (1) , Width: 5 */
  0xFF,  0xFF,  0xFF,  0xFF,  0xFF, 0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
};

#define OFFSET 10
/*Store the glyph descriptions*/
static const lv_font_glyph_dsc_t square8_glyph_dsc[] =
{
  {.w_px = 8,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 8,	.glyph_index = OFFSET},	/*Unicode: U+0031 (1)*/
};
static const lv_font_glyph_dsc_t square7_glyph_dsc[] =
{
  {.w_px = 7,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 7,	.glyph_index = OFFSET},	/*Unicode: U+0031 (1)*/
};
static const lv_font_glyph_dsc_t square6_glyph_dsc[] =
{
  {.w_px = 6,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 6,	.glyph_index = OFFSET},	/*Unicode: U+0031 (1)*/
};
static const lv_font_glyph_dsc_t square5_glyph_dsc[] =
{
  {.w_px = 5,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 5,	.glyph_index = OFFSET},	/*Unicode: U+0031 (1)*/
};

static const lv_font_glyph_dsc_t square4_glyph_dsc[] =
{
  {.w_px = 4,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 4,	.glyph_index = OFFSET},	/*Unicode: U+0031 (1)*/
};

static const lv_font_glyph_dsc_t square3_glyph_dsc[] =
{
  {.w_px = 3,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 3,	.glyph_index = OFFSET},	/*Unicode: U+0031 (1)*/
};

static const lv_font_glyph_dsc_t square2_glyph_dsc[] =
{
  {.w_px = 2,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 2,	.glyph_index = OFFSET},	/*Unicode: U+0031 (1)*/
};

static const lv_font_glyph_dsc_t square1_glyph_dsc[] =
{
  {.w_px = 1,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 1,	.glyph_index = OFFSET},	/*Unicode: U+0031 (1)*/
};

/*List of unicode characters*/
static const uint32_t square_unicode_list[] = {
  48,	/*Unicode: U+0030 (0)*/
  49,	/*Unicode: U+0031 (1)*/
  0,    /*End indicator*/
};

lv_font_t square8 =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 49,	/*Last Unicode letter in this font*/
    .h_px = 8,				/*Font height in pixels*/
    .glyph_bitmap = square_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = square8_glyph_dsc,		/*Description of glyphs*/
    .glyph_cnt = 2,			/*Number of glyphs in the font*/
    .unicode_list = square_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .monospace = 8,		/*Fix width (0: if not used)*/
    .next_page = NULL,		/*Pointer to a font extension*/
};

lv_font_t square7 =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 49,	/*Last Unicode letter in this font*/
    .h_px = 7,				/*Font height in pixels*/
    .glyph_bitmap = square_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = square7_glyph_dsc,		/*Description of glyphs*/
    .glyph_cnt = 2,			/*Number of glyphs in the font*/
    .unicode_list = square_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .monospace = 7,		/*Fix width (0: if not used)*/
    .next_page = NULL,		/*Pointer to a font extension*/
};

lv_font_t square6 =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 49,	/*Last Unicode letter in this font*/
    .h_px = 6,				/*Font height in pixels*/
    .glyph_bitmap = square_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = square6_glyph_dsc,		/*Description of glyphs*/
    .glyph_cnt = 2,			/*Number of glyphs in the font*/
    .unicode_list = square_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .monospace = 6,		/*Fix width (0: if not used)*/
    .next_page = NULL,		/*Pointer to a font extension*/
};

lv_font_t square5 =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 49,	/*Last Unicode letter in this font*/
    .h_px = 5,				/*Font height in pixels*/
    .glyph_bitmap = square_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = square5_glyph_dsc,		/*Description of glyphs*/
    .glyph_cnt = 2,			/*Number of glyphs in the font*/
    .unicode_list = square_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .monospace = 5,		/*Fix width (0: if not used)*/
    .next_page = NULL,		/*Pointer to a font extension*/
};

lv_font_t square4 =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 49,	/*Last Unicode letter in this font*/
    .h_px = 4,				/*Font height in pixels*/
    .glyph_bitmap = square_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = square4_glyph_dsc,		/*Description of glyphs*/
    .glyph_cnt = 2,			/*Number of glyphs in the font*/
    .unicode_list = square_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .monospace = 4,		/*Fix width (0: if not used)*/
    .next_page = NULL,		/*Pointer to a font extension*/
};

lv_font_t square3 =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 49,	/*Last Unicode letter in this font*/
    .h_px = 3,				/*Font height in pixels*/
    .glyph_bitmap = square_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = square3_glyph_dsc,		/*Description of glyphs*/
    .glyph_cnt = 2,			/*Number of glyphs in the font*/
    .unicode_list = square_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .monospace = 3,		/*Fix width (0: if not used)*/
    .next_page = NULL,		/*Pointer to a font extension*/
};

lv_font_t square2 =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 49,	/*Last Unicode letter in this font*/
    .h_px = 2,				/*Font height in pixels*/
    .glyph_bitmap = square_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = square2_glyph_dsc,		/*Description of glyphs*/
    .glyph_cnt = 2,			/*Number of glyphs in the font*/
    .unicode_list = square_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .monospace = 2,		/*Fix width (0: if not used)*/
    .next_page = NULL,		/*Pointer to a font extension*/
};

lv_font_t square1 =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 49,	/*Last Unicode letter in this font*/
    .h_px = 1,				/*Font height in pixels*/
    .glyph_bitmap = square_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = square1_glyph_dsc,		/*Description of glyphs*/
    .glyph_cnt = 2,			/*Number of glyphs in the font*/
    .unicode_list = square_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .monospace = 1,		/*Fix width (0: if not used)*/
    .next_page = NULL,		/*Pointer to a font extension*/
};

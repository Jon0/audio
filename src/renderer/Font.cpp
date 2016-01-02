extern "C" {
#define FT_CONFIG_OPTION_SUBPIXEL_RENDERING
#include <ft2build.h>
#include FT_FREETYPE_H
}

#include "Font.h"

namespace renderer {

Font::Font(const std::string &file_path) {
	FT_Library library = 0;
	FT_Face face = 0;
	FT_Init_FreeType(&library);
	//FT_Library_SetLcdFilter(library, FT_LCD_FILTER_LIGHT);
	FT_New_Face(library, file_path.c_str(), 0, &face);
	FT_Set_Char_Size(face, 0, 24 * 64, 300, 300);
	FT_ULong charcode = 0x003f;
	FT_UInt glyph_index = 0;
	glyph_index = FT_Get_Char_Index(face, charcode);
	FT_Load_Glyph(face, glyph_index, FT_LOAD_TARGET_NORMAL);
	FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LCD);
	FT_Bitmap bitmap = face->glyph->bitmap;
	FT_Glyph_Metrics metrics = face->glyph->metrics;
	int colStartPos = metrics.horiBearingX / 64;
	int rowStartPos = metrics.horiBearingY / 64;

	for (int y = 0; y < bitmap.rows; y++) {
		int row = rowStartPos + y;
		for (int x = 0; x < bitmap.width; x++) {
			int col = colStartPos + x;
			uint8_t r = bitmap.buffer[y * bitmap.pitch + x * 3];
			uint8_t g = bitmap.buffer[y * bitmap.pitch + x * 3 + 1];
			uint8_t b = bitmap.buffer[y * bitmap.pitch + x * 3 + 2];
			//imgView(col, row) = boost::gil::rgba8_pixel_t{r, g, b, 255};
		}
	}
}

}

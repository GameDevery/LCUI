﻿#include <stdio.h>
#include <LCUI.h>
#include <ctest-custom.h>

#define GetSegoeUIFont(S, W) pd_font_library_get_font_id("Segoe UI", S, W)
#define GetArialFont(S, W) pd_font_library_get_font_id("Arial", S, W)

void test_segoe_ui_font_load(void)
{
	pd_font_t *font;
	int id;
	if (pd_font_library_load_file("C:/windows/fonts/segoeui.ttf") != 0) {
		return;
	}
	ctest_euqal_int("load segoeui.ttf",
	     pd_font_library_load_file("C:/windows/fonts/segoeui.ttf"), 0);
	ctest_euqal_int("load segoeuib.ttf",
	     pd_font_library_load_file("C:/windows/fonts/segoeuib.ttf"), 0);
	ctest_euqal_int("load segoeuii.ttf",
	     pd_font_library_load_file("C:/windows/fonts/segoeuii.ttf"), 0);
	ctest_euqal_int("load segoeuil.ttf",
	     pd_font_library_load_file("C:/windows/fonts/segoeuil.ttf"), 0);
	ctest_euqal_int("load segoeuisl.ttf",
	     pd_font_library_load_file("C:/windows/fonts/segoeuisl.ttf"), 0);
	ctest_euqal_int("load segoeuiz.ttf",
	     pd_font_library_load_file("C:/windows/fonts/segoeuiz.ttf"), 0);
	ctest_euqal_int("load seguibl.ttf",
	     pd_font_library_load_file("C:/windows/fonts/seguibl.ttf"), 0);
	ctest_euqal_int("load seguili.ttf",
	     pd_font_library_load_file("C:/windows/fonts/seguili.ttf"), 0);
	ctest_euqal_bool("check get font (style: normal, weight: normal)",
	     id = GetSegoeUIFont(PD_FONT_STYLE_NORMAL, PD_FONT_WEIGHT_NORMAL),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_NORMAL);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_NORMAL);
	}
	ctest_euqal_bool("check get font (style: italic, weight: normal)",
	     id = GetSegoeUIFont(PD_FONT_STYLE_ITALIC, PD_FONT_WEIGHT_NORMAL),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_ITALIC);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_NORMAL);
	}
	ctest_euqal_bool("check get font (style: normal, weight: bold)",
	     id = GetSegoeUIFont(PD_FONT_STYLE_NORMAL, PD_FONT_WEIGHT_BOLD),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_NORMAL);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_BOLD);
	}
	ctest_euqal_bool("check get font (style: normal, weight: light)",
	     id = GetSegoeUIFont(PD_FONT_STYLE_NORMAL, PD_FONT_WEIGHT_LIGHT),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_NORMAL);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_LIGHT);
	}
	ctest_euqal_bool("check get font (style: italic, weight: extra light)",
	     id = GetSegoeUIFont(PD_FONT_STYLE_ITALIC,
				 PD_FONT_WEIGHT_EXTRA_LIGHT),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_ITALIC);
		ctest_euqal_int("check font weight", font->weight,
		     PD_FONT_WEIGHT_EXTRA_LIGHT);
	}
}

void test_arial_font_load(void)
{
	int id;
	pd_font_t *font;
	if (pd_font_library_load_file("C:/windows/fonts/arial.ttf") != 0) {
		return;
	}
	ctest_euqal_int("load arialbd.ttf",
	     pd_font_library_load_file("C:/windows/fonts/arialbd.ttf"), 0);
	ctest_euqal_int("load arialblk.ttf",
	     pd_font_library_load_file("C:/windows/fonts/ariblk.ttf"), 0);
	ctest_euqal_int("load arialbi.ttf",
	     pd_font_library_load_file("C:/windows/fonts/arialbi.ttf"), 0);
	ctest_euqal_int("load ariali.ttf",
	     pd_font_library_load_file("C:/windows/fonts/ariali.ttf"), 0);
	ctest_euqal_bool("check get font (style: normal, weight: normal)",
	     id = GetArialFont(PD_FONT_STYLE_NORMAL, PD_FONT_WEIGHT_NORMAL),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_NORMAL);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_NORMAL);
	}
	ctest_euqal_bool("check get font (style: italic, weight: normal)",
	     id = GetArialFont(PD_FONT_STYLE_ITALIC, PD_FONT_WEIGHT_NORMAL),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_ITALIC);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_NORMAL);
	}
	ctest_euqal_bool("check get font (style: normal, weight: bold)",
	     id = GetArialFont(PD_FONT_STYLE_NORMAL, PD_FONT_WEIGHT_BOLD),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_NORMAL);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_BOLD);
	}
	ctest_euqal_bool("check get font (style: normal, weight: black)",
	     id = GetArialFont(PD_FONT_STYLE_NORMAL, PD_FONT_WEIGHT_BLACK),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_NORMAL);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_BLACK);
	}
	ctest_euqal_bool("check get font (style: italic, weight: bold)",
	     id = GetSegoeUIFont(PD_FONT_STYLE_ITALIC, PD_FONT_WEIGHT_BOLD),
	     TRUE);
	if (id > 0) {
		font = pd_font_library_get_font(id);
		ctest_euqal_int("check font style", font->style, PD_FONT_STYLE_ITALIC);
		ctest_euqal_int("check font weight", font->weight, PD_FONT_WEIGHT_BOLD);
	}
}

void test_font_load(void)
{
	pd_font_library_init();
	/* 测试是否能够从字体文件中载入字体 */
	ctest_euqal_int("check pd_font_library_load_file success",
	     pd_font_library_load_file("test_font_load.ttf"), 0);
#ifdef LIBPLAT_WIN32
	ctest_describe("test segoe ui font load", test_segoe_ui_font_load);
	ctest_describe("test arial font load", test_arial_font_load);
#endif
	pd_font_library_destroy();

	ui_init();
	/* 测试是否能够根据 CSS 文件中定义的 @font-face 规则来载入字体 */
	ctest_euqal_int("check LCUIFont_LoadCSSFile success",
	     ui_load_css_file("test_font_load.css"), 0);
	ctest_euqal_bool("check pd_font_library_get_font_id success",
	     pd_font_library_get_font_id("icomoon", 0, 0) > 0, TRUE);
	ui_destroy();
}
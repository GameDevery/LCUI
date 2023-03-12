#include <stdio.h>
#include "test.h"
#include "ctest.h"
#include "../include/css.h"

static void check_length(const char *str, css_numeric_value_t actual,
			 css_numeric_value_t expected)
{
	it_i(str, (int)actual, (int)expected);
}

void test_css_computed(void)
{
	size_t n;
	FILE *fp;
	char buff[512];
	css_parser_t *parser;

	css_selector_t *selector;
	css_style_decl_t *result;
	css_computed_style_t computed;

	fp = fopen("test_css_computed.css", "r");
	if (!fp) {
		return;
	}
	css_init();
	parser = css_parser_create(512, __FILE__);
	n = fread(buff, 1, 511, fp);
	while (n > 0) {
		buff[n] = 0;
		css_parser_parse(parser, buff);
		n = fread(buff, 1, 511, fp);
	}
	css_parser_destroy(parser);
	fclose(fp);

	selector = css_selector_create(".primary.button:focus");
	result = css_select_style(selector);
	css_cascade_style(result, &computed);

	it_s("content", computed.content, "submit");
	check_length("font-size", computed.font_size, 16);
	check_length("min-width", computed.min_width, 80);
	it_i("box-sizing", computed.type_bits.box_sizing,
	     CSS_BOX_SIZING_BORDER_BOX);

	check_length("padding-left", computed.padding_left, 8);
	check_length("padding-right", computed.padding_right, 8);
	check_length("padding-top", computed.padding_top, 4);
	check_length("padding-bottom", computed.padding_bottom, 4);

	check_length("border-top-width", computed.border_top_width, 1);
	check_length("border-right-width", computed.border_right_width, 1);
	check_length("border-bottom-width", computed.border_bottom_width, 1);
	check_length("border-left-width", computed.border_left_width, 1);

	it_i("border-top-style", computed.type_bits.border_top_style,
	     CSS_BORDER_STYLE_SOLID);
	it_i("border-right-style", computed.type_bits.border_right_style,
	     CSS_BORDER_STYLE_SOLID);
	it_i("border-bottom-style", computed.type_bits.border_bottom_style,
	     CSS_BORDER_STYLE_SOLID);
	it_i("border-left-style", computed.type_bits.border_left_style,
	     CSS_BORDER_STYLE_SOLID);
	it_u("background-color", computed.background_color, css_color(255, 0, 0x50, 0xc9));

	check_length("border-top-left-radius", computed.border_top_left_radius,
		     4);
	check_length("border-top-right-radius",
		     computed.border_top_right_radius, 4);
	check_length("border-bottom-left-radius",
		     computed.border_bottom_left_radius, 4);
	check_length("border-bottom-right-radius",
		     computed.border_bottom_right_radius, 4);
	check_length("box-shadow-x", computed.box_shadow_x, 0);
	check_length("box-shadow-y", computed.box_shadow_y, 0);
	check_length("box-shadow-blur", computed.box_shadow_blur, 0);
	check_length("box-shadow-spread", computed.box_shadow_spread, 2);
	it_u("box-shadow-color", computed.box_shadow_color,
	     css_color(127, 0, 0, 200));

	css_style_decl_destroy(result);
	css_selector_destroy(selector);
	css_computed_style_destroy(&computed);

	selector = css_selector_create(".container");
	result = css_select_style(selector);
	css_cascade_style(result, &computed);

	check_length("margin-top", computed.margin_top, 24);
	check_length("margin-bottom", computed.margin_top, 24);
	it_i("margin-left", computed.type_bits.margin_left, CSS_MARGIN_AUTO);
	it_i("margin-right", computed.type_bits.margin_right, CSS_MARGIN_AUTO);

	css_style_decl_destroy(result);
	css_selector_destroy(selector);
	css_computed_style_destroy(&computed);

	css_destroy();
}

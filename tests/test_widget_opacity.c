﻿/*
 * tests/test_widget_opacity.c
 *
 * Copyright (c) 2023, Liu Chao <i@lc-soft.io> All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * This file is part of LCUI, distributed under the MIT License found in the
 * LICENSE.TXT file in the root directory of this source tree.
 */

#define PREVIEW_MODE
#include <ptk/main.h>
#include "./cases/test_widget_opacity.c"

static void on_opacity_minus(ui_widget_t *w, ui_event_t *e, void *arg)
{
	wchar_t str[32];
	float opacity = self.parent->computed_style.opacity - 0.1f;

	if (opacity < 0.1f) {
		opacity = 0.1f;
	}
	swprintf(str, 32, L"%.1f", opacity);
	ui_widget_set_style_numeric_value(self.parent, css_prop_opacity,
					  opacity);
	ui_text_set_content_w(self.text, str);
}

static void on_opacity_plus(ui_widget_t *w, ui_event_t *e, void *arg)
{
	wchar_t str[32];
	float opacity = self.parent->computed_style.opacity + 0.1f;

	if (opacity > 1.0f) {
		opacity = 1.0f;
	}
	swprintf(str, 32, L"%.1f", opacity);
	ui_widget_set_style_numeric_value(self.parent, css_prop_opacity,
					  opacity);
	ui_text_set_content_w(self.text, str);
}

int main(int argc, char **argv)
{
	ui_widget_t *btn_plus, *btn_minus;

	lcui_init();
	build();
	btn_plus = ui_get_widget("btn-plus");
	btn_minus = ui_get_widget("btn-minus");
	ui_widget_on(btn_plus, "click", on_opacity_plus, NULL);
	ui_widget_on(btn_minus, "click", on_opacity_minus, NULL);
	return lcui_main();
}

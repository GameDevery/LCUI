﻿/*
 * lib/ui/src/ui_widget_background.c
 *
 * Copyright (c) 2023-2024, Liu Chao <i@lc-soft.io> All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * This file is part of LCUI, distributed under the MIT License found in the
 * LICENSE.TXT file in the root directory of this source tree.
 */

#include <pandagl.h>
#include <css/style_value.h>
#include <ui/base.h>
#include <ui/image.h>
#include <ui/metrics.h>
#include "ui_widget_background.h"

void ui_widget_paint_background(ui_widget_t *w, pd_context_t *ctx,
                                ui_widget_actual_style_t *style)
{
        pd_rect_t box;
        pd_background_t bg;
        css_computed_style_t *s = &w->computed_style;

        if (!s->background_image && css_color_alpha(s->background_color) < 1) {
                return;
        }
        bg.color.value = s->background_color;
        if (s->background_image) {
                bg.image = (pd_canvas_t *)ui_get_image(s->background_image);
        } else {
                bg.image = NULL;
        }
        bg.x = ui_compute(s->background_position_x);
        bg.y = ui_compute(s->background_position_y);
        bg.width = ui_compute(s->background_width);
        bg.height = ui_compute(s->background_height);
        bg.repeat_x =
            s->type_bits.background_repeat == CSS_BACKGROUND_REPEAT_REPEAT ||
            s->type_bits.background_repeat == CSS_BACKGROUND_REPEAT_REPEAT_X;
        bg.repeat_y =
            s->type_bits.background_repeat == CSS_BACKGROUND_REPEAT_REPEAT ||
            s->type_bits.background_repeat == CSS_BACKGROUND_REPEAT_REPEAT_Y;

        box.x = style->padding_box.x - style->canvas_box.x;
        box.y = style->padding_box.y - style->canvas_box.y;
        box.width = style->padding_box.width;
        box.height = style->padding_box.height;
        pd_paint_background(ctx, &bg, &box);
}

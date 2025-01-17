﻿/*
 * tests/test_image_scaling_bench.c
 *
 * Copyright (c) 2023, Liu Chao <i@lc-soft.io> All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * This file is part of LCUI, distributed under the MIT License found in the
 * LICENSE.TXT file in the root directory of this source tree.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <LCUI.h>
#include <ui.h>
#include <ui_xml.h>
#include <pandagl.h>

int main(int argc, char **argv)
{
	int i;
	int64_t t0, t1, t2;
	int resx[] = { 480, 960, 1280, 1366, 1920, 2560, 3840 }, resy;
	char s_res[32], s_t0[32], s_t1[32];

	pd_canvas_t g_src, g_dst;
	pd_color_t t_color;

	pd_canvas_init(&g_src);
	g_src.color_type = PD_COLOR_TYPE_ARGB;
	if (pd_canvas_create(&g_src, 960, 540) < 0) {
		return -2;
	}
	t_color.value = 0xffaa5500;
	pd_canvas_fill(&g_src, t_color);
	logger_info("%-20s%-20s%s\n", "image size\\method", "Graph_Zoom()",
		    "Graph_ZoomBilinear()");
	for (i = 0; i < sizeof(resx) / sizeof(int); i++) {
		resy = resx[i] * 9 / 16;
		t0 = get_time_ms();
		pd_canvas_init(&g_dst);
		pd_canvas_zoom(&g_src, &g_dst, false, resx[i], resy);
		pd_canvas_destroy(&g_dst);
		t1 = get_time_ms();
		pd_canvas_init(&g_dst);
		pd_canvas_zoom_bilinear(&g_src, &g_dst, false, resx[i], resy);
		pd_canvas_destroy(&g_dst);
		t2 = get_time_ms();
		sprintf(s_res, "%dx%d", resx[i], resy);
		sprintf(s_t0, "%ldms", (int)(t1 - t0));
		sprintf(s_t1, "%ldms", (int)(t2 - t1));
		logger_info("%-20s%-20s%-20s\n", s_res, s_t0, s_t1);
	}
	pd_canvas_destroy(&g_src);
	return 0;
}
